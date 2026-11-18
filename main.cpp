#include <QCoreApplication>

#include "src/console/ConsoleGame.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    ConsoleGame game;
    return game.run();
}
