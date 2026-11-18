#include "ConsoleGame.h"
#include "../battle/BattleService.h"
#include "../character/CharacterService.h"
#include "../inventory/InventoryService.h"
#include "../save/SaveService.h"
#include "../shop/ShopService.h"
#include <QTextStream>
#include <optional>

#ifdef Q_OS_WIN
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#endif

namespace {
    constexpr int ZONE_COUNT = static_cast<int>(GladiatorZone::COUNT);
    constexpr int AUTO_FIGHT_COMMAND = ZONE_COUNT + 1;
    constexpr int MAX_AUTO_TURNS = 1000;

    void setupConsole() {
#ifdef Q_OS_WIN
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
#endif
    }

    QTextStream& output() {
        static QTextStream stream(stdout);
        return stream;
    }

    void print(const QString& text = {}) {
        output() << text << Qt::endl;
    }

    void prompt(const QString& text) {
        output() << text << Qt::flush;
    }

    // В консоли Windows кириллицу через stdin не прочитать, поэтому там ReadConsoleW
    std::optional<QString> readLine() {
#ifdef Q_OS_WIN
        const HANDLE input = GetStdHandle(STD_INPUT_HANDLE);
        DWORD mode;
        if (GetConsoleMode(input, &mode)) {
            wchar_t buffer[512];
            DWORD length = 0;
            if (!ReadConsoleW(input, buffer, 512, &length, nullptr) || length == 0) {
                return std::nullopt;
            }
            return QString::fromWCharArray(buffer, static_cast<int>(length)).trimmed();
        }
#endif
        static QTextStream stream(stdin);
        QString line;
        if (!stream.readLineInto(&line)) {
            return std::nullopt;
        }
        return line.trimmed();
    }

    // nullopt значит, что ввод закончился и пора выходить
    std::optional<int> readChoice(const int min, const int max) {
        while (true) {
            prompt("> ");
            const auto line = readLine();
            if (!line) return std::nullopt;

            bool isNumber = false;
            const int choice = line->toInt(&isNumber);
            if (isNumber && choice >= min && choice <= max) return choice;

            print(QString("Введи число от %1 до %2").arg(min).arg(max));
        }
    }

    QString zoneName(const GladiatorZone zone) {
        switch (zone) {
            case GladiatorZone::HEAD: return "Голова";
            case GladiatorZone::CHEST: return "Грудь";
            case GladiatorZone::BELLY: return "Живот";
            case GladiatorZone::LEGS: return "Ноги";
            case GladiatorZone::COUNT: break;
        }
        return {};
    }

    QString itemTypeName(const ItemType type) {
        switch (type) {
            case ItemType::WEAPON: return "оружие";
            case ItemType::ARMOR: return "броня";
            case ItemType::HELMET: return "шлем";
            case ItemType::SHIELD: return "щит";
        }
        return {};
    }

    QString describeItem(const Item& item) {
        return QString("%1 (%2, урон %3, защита %4)")
                .arg(item.getName(), itemTypeName(item.getType()))
                .arg(item.getDamage())
                .arg(item.getArmor());
    }

    int percent(const float chance) {
        return qRound(chance * 100);
    }

    struct TurnCommand {
        bool surrender = false;
        bool autoFight = false;
        GladiatorZone attack = GladiatorZone::HEAD;
        GladiatorZone block = GladiatorZone::HEAD;
    };

    void printZones() {
        for (int i = 0; i < ZONE_COUNT; i++) {
            print(QString("%1. %2").arg(i + 1).arg(zoneName(static_cast<GladiatorZone>(i))));
        }
    }

    std::optional<TurnCommand> readTurnCommand(const bool hasShield) {
        print("Куда бьёшь?");
        printZones();
        print(QString("%1. Автобой").arg(AUTO_FIGHT_COMMAND));
        print("0. Сдаться");

        const auto attack = readChoice(0, AUTO_FIGHT_COMMAND);
        if (!attack) return std::nullopt;

        TurnCommand command;
        if (*attack == 0) {
            command.surrender = true;
            return command;
        }
        if (*attack == AUTO_FIGHT_COMMAND) {
            command.autoFight = true;
            return command;
        }

        command.attack = static_cast<GladiatorZone>(*attack - 1);
        if (!hasShield) return command;

        print("Что закрываешь?");
        printZones();

        const auto block = readChoice(1, ZONE_COUNT);
        if (!block) return std::nullopt;

        command.block = static_cast<GladiatorZone>(*block - 1);
        return command;
    }
}

ConsoleGame::ConsoleGame()
    : m_player(QString()), m_defeatedCount(0) {
}

int ConsoleGame::run() {
    setupConsole();
    print("=== ГЛАДИАТОРЫ ===");

    if (!loadOrCreatePlayer()) return 0;

    while (true) {
        print();
        showStatus();
        print("1. Арена");
        print("2. Магазин");
        print("3. Инвентарь");
        print("4. Характеристики");
        print("0. Выход");

        const auto choice = readChoice(0, 4);
        if (!choice || *choice == 0) break;

        switch (*choice) {
            case 1: fight();
                break;
            case 2: shop();
                break;
            case 3: inventory();
                break;
            case 4: stats();
                break;
            default: break;
        }
        save();
    }

    save();
    print("До встречи на арене!");
    return 0;
}

bool ConsoleGame::loadOrCreatePlayer() {
    if (const auto player = SaveService::loadPlayer()) {
        m_player = *player;
        m_defeatedCount = SaveService::loadProgress();
        print("С возвращением, " + m_player.getName() + "!");
        return true;
    }

    prompt("Как зовут твоего гладиатора? ");
    const auto name = readLine();
    if (!name) return false;

    m_player = Gladiator(name->isEmpty() ? "Безымянный" : *name);
    m_defeatedCount = 0;
    save();
    return true;
}

void ConsoleGame::save() {
    if (!SaveService::savePlayer(m_player) || !SaveService::saveProgress(m_defeatedCount)) {
        print("Не удалось сохранить игру!");
    }
}

void ConsoleGame::showStatus() {
    print(QString("%1 | уровень %2 | золото %3 | свободные очки %4 | побеждено %5 из %6")
            .arg(m_player.getName())
            .arg(m_player.getLevel())
            .arg(m_player.getGold())
            .arg(m_player.getFreePoints())
            .arg(m_defeatedCount)
            .arg(m_arena.getFights().size()));
}

void ConsoleGame::fight() {
    const QList<Fight> fights = m_arena.getFights();
    if (m_defeatedCount >= fights.size()) {
        print("Ты победил всех гладиаторов арены!");
        return;
    }

    Fight fight = fights[m_defeatedCount];
    ArenaService::joinFight(fight, m_player);
    m_arena.start(fight);
    m_player.setMaxHp();

    Gladiator* bot = fight.getParticipants().first();

    print();
    print(QString("Противник: %1, уровень %2, здоровье %3")
            .arg(bot->getName()).arg(bot->getLevel()).arg(bot->getHp()));
    if (m_player.getDamage() == 0) {
        print("У тебя 0 урона: купи и надень оружие, иначе победить не получится.");
    }

    const bool hasShield = m_player.getShieldArmor() > 0;
    const int goldBefore = m_player.getGold();
    bool autoFight = false;
    int autoTurns = 0;

    while (!fight.isFinished()) {
        TurnCommand command;

        if (!autoFight) {
            print();
            print(QString("Ты: %1/%2 | %3: %4/%5")
                    .arg(qMax(0, m_player.getHp())).arg(m_player.getMaxHp())
                    .arg(bot->getName())
                    .arg(qMax(0, bot->getHp())).arg(bot->getMaxHp()));

            const auto input = readTurnCommand(hasShield);
            if (!input || input->surrender) {
                print("Ты покинул арену.");
                m_player.setMaxHp();
                return;
            }
            command = *input;
            autoFight = command.autoFight;
        }

        const Turn playerTurn = autoFight
                                    ? BattleService::makeBotTurn(m_player)
                                    : BattleService::makeTurn(m_player, command.attack, command.block);
        const Turn botTurn = BattleService::makeBotTurn(*bot);

        const int playerHpBefore = m_player.getHp();
        const int botHpBefore = bot->getHp();

        const int damageToBot = BattleService::calculateDamage(m_player, *bot, playerTurn, botTurn);
        const int damageToPlayer = BattleService::calculateDamage(*bot, m_player, botTurn, playerTurn);
        bot->subHp(damageToBot);
        m_player.subHp(damageToPlayer);

        if (!autoFight) {
            print(QString("Ты бьёшь: %1, %2 закрывает: %3. Урон: %4")
                    .arg(zoneName(playerTurn.getAttackZone()), bot->getName(),
                         zoneName(botTurn.getBlockZone()))
                    .arg(botHpBefore - bot->getHp()));
            if (hasShield) {
                print(QString("%1 бьёт: %2, ты закрываешь: %3. Урон: %4")
                        .arg(bot->getName(), zoneName(botTurn.getAttackZone()),
                             zoneName(playerTurn.getBlockZone()))
                        .arg(playerHpBefore - m_player.getHp()));
            } else {
                print(QString("%1 бьёт: %2. Урон: %3")
                        .arg(bot->getName(), zoneName(botTurn.getAttackZone()))
                        .arg(playerHpBefore - m_player.getHp()));
            }
        }

        BattleService::finishFight(fight);

        if (autoFight && !fight.isFinished() && ++autoTurns >= MAX_AUTO_TURNS) {
            print(QString("За %1 ходов бой не закончился, продолжай вручную или сдавайся.")
                    .arg(MAX_AUTO_TURNS));
            autoFight = false;
            autoTurns = 0;
        }
    }

    const auto winner = fight.resolveWinner();
    print();
    if (winner && *winner == &m_player) {
        m_defeatedCount++;
        print(QString("Победа! Теперь у тебя уровень %1, золото %2, свободные очки %3")
                .arg(m_player.getLevel()).arg(m_player.getGold()).arg(m_player.getFreePoints()));
        if (m_defeatedCount == fights.size()) {
            print("Ты победил всех гладиаторов арены!");
        }
    } else if (winner) {
        print(QString("Поражение. %1 оказался сильнее. Получено золота: %2")
                .arg(bot->getName()).arg(m_player.getGold() - goldBefore));
    } else {
        print(QString("Ничья: оба гладиатора пали. Получено золота: %1")
                .arg(m_player.getGold() - goldBefore));
    }

    m_player.setMaxHp();
}

void ConsoleGame::shop() {
    const QList<Item> items = ShopService::getItems();

    while (true) {
        print();
        print(QString("Магазин. Золото: %1").arg(m_player.getGold()));
        for (int i = 0; i < items.size(); i++) {
            const Item& item = items[i];
            print(QString("%1. %2, цена %3, нужен уровень %4")
                    .arg(i + 1).arg(describeItem(item))
                    .arg(item.getPrice()).arg(item.getRequiredLevel()));
        }
        print("0. Назад");

        const auto choice = readChoice(0, static_cast<int>(items.size()));
        if (!choice || *choice == 0) return;

        const Item& item = items[*choice - 1];
        if (item.getRequiredLevel() > m_player.getLevel()) {
            print("Твой уровень слишком низкий.");
        } else if (!ShopService::buy(m_player, item)) {
            print("Не хватает золота.");
        } else {
            print("Куплено: " + item.getName() + ". Надень предмет в инвентаре.");
        }
    }
}

void ConsoleGame::inventory() {
    while (true) {
        const QList<Item> items = m_player.getInventory();

        print();
        print("Инвентарь (выбери предмет, чтобы надеть или снять):");
        if (items.isEmpty()) print("Пусто.");
        for (int i = 0; i < items.size(); i++) {
            print(QString("%1. %2%3")
                    .arg(i + 1).arg(describeItem(items[i]))
                    .arg(items[i].isEquipped() ? " [надето]" : ""));
        }
        print("0. Назад");

        const auto choice = readChoice(0, static_cast<int>(items.size()));
        if (!choice || *choice == 0) return;

        const Item& item = items[*choice - 1];
        if (item.isEquipped()) {
            InventoryService::unequip(m_player, item);
        } else {
            InventoryService::equip(m_player, item);
        }
    }
}

void ConsoleGame::stats() {
    while (true) {
        print();
        print(QString("Здоровье %1 | урон %2 | защита %3 | щит %4 | крит %5% | уворот %6%")
                .arg(m_player.getMaxHp())
                .arg(m_player.getDamage())
                .arg(m_player.getArmor())
                .arg(m_player.getShieldArmor())
                .arg(percent(m_player.getCritChance()))
                .arg(percent(m_player.getDodgeChance())));
        print(QString("Свободные очки: %1").arg(m_player.getFreePoints()));
        print(QString("1. Сила: %1").arg(m_player.getStrength()));
        print(QString("2. Ловкость: %1").arg(m_player.getAgility()));
        print(QString("3. Интуиция: %1").arg(m_player.getIntuition()));
        print(QString("4. Выносливость: %1").arg(m_player.getEndurance()));
        print("0. Назад");

        const auto choice = readChoice(0, 4);
        if (!choice || *choice == 0) return;

        const StatType stat = static_cast<StatType>(*choice - 1);
        if (!CharacterService::addStatPoint(m_player, stat)) {
            print("Нет свободных очков.");
        }
    }
}
