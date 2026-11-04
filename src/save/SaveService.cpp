#include "SaveService.h"
#include "../shop/ShopService.h"
#include <QDir>
#include <QFile>
#include <QSaveFile>
#include <QStandardPaths>

namespace {
    constexpr auto PLAYER_FILE = "player.dat";
    constexpr auto PROGRESS_FILE = "progress.dat";

    QString filePath(const QString& fileName) {
        const QString dir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
        static_cast<void>(QDir().mkpath(dir));
        return dir + "/" + fileName;
    }

    bool writeFile(const QString& fileName, const QByteArray& data) {
        QSaveFile file(filePath(fileName));
        if (!file.open(QIODevice::WriteOnly)) {
            return false;
        }
        file.write(qCompress(data));
        return file.commit();
    }

    std::optional<QByteArray> readFile(const QString& fileName) {
        QFile file(filePath(fileName));
        if (!file.open(QIODevice::ReadOnly)) {
            return std::nullopt;
        }
        QByteArray data = qUncompress(file.readAll());
        if (data.isEmpty()) {
            return std::nullopt;
        }
        return data;
    }
}

bool SaveService::savePlayer(const Gladiator& player) {
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_0);

    out << player.getName()
        << player.getLevel()
        << player.getExperience()
        << player.getGold()
        << player.getFreePoints()
        << player.getStrength()
        << player.getAgility()
        << player.getIntuition()
        << player.getEndurance();

    const QList<Item> inventory = player.getInventory();
    out << static_cast<qint32>(inventory.size());
    for (const Item& item : inventory) {
        out << static_cast<qint32>(item.getId());
    }

    return writeFile(PLAYER_FILE, data);
}

std::optional<Gladiator> SaveService::loadPlayer() {
    const auto data = readFile(PLAYER_FILE);
    if (!data) {
        return std::nullopt;
    }

    QDataStream in(*data);
    in.setVersion(QDataStream::Qt_6_0);

    QString name;
    int level, experience, gold, freePoints;
    int strength, agility, intuition, endurance;
    qint32 inventorySize;

    in >> name >> level >> experience >> gold >> freePoints
       >> strength >> agility >> intuition >> endurance
       >> inventorySize;

    if (in.status() != QDataStream::Ok || inventorySize < 0) {
        return std::nullopt;
    }

    Gladiator player(name, level, experience, gold, freePoints,
                     strength, agility, intuition, endurance, false);

    for (qint32 i = 0; i < inventorySize; ++i) {
        qint32 id;
        in >> id;
        if (in.status() != QDataStream::Ok) {
            return std::nullopt;
        }
        player.addItem(ShopService::findItem(static_cast<ItemId>(id)));
    }

    return player;
}

bool SaveService::saveProgress(const int defeatedCount) {
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_0);
    out << defeatedCount;
    return writeFile(PROGRESS_FILE, data);
}

int SaveService::loadProgress() {
    const auto data = readFile(PROGRESS_FILE);
    if (!data) {
        return 0;
    }

    QDataStream in(*data);
    in.setVersion(QDataStream::Qt_6_0);

    int defeatedCount;
    in >> defeatedCount;

    if (in.status() != QDataStream::Ok || defeatedCount < 0) {
        return 0;
    }
    return defeatedCount;
}