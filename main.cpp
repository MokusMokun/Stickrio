#include <QApplication>
#include <game.h>

static Game* game;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    game = new Game();
    game->displayMainMenu();
    game->show();
    return a.exec();
}
