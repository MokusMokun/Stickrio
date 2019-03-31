#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <stickman.h>
#include <background.h>
#include <config.h>
#include "button.h"
#include "mymediaplayer.h"

class Game: public QGraphicsView{
    Q_OBJECT
public:
    Game();

public slots:
    void start();
    void resize();
    void displayMainMenu();

private:
    QGraphicsScene* scene;
    Config* config;
    Button* pauseButton;
    Button* exitButton;
    Button* saveButton;
    Button* sizeButton;
    Button* clothesButton;
    Button* bgButton;
};

#endif // GAME_H
