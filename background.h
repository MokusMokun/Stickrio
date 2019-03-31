#ifndef BACKGOUND_H
#define BACKGOUND_H
#include <config.h>
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <QTimer>

class Background: public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Background(QString back_pic_str, Config* config);
    ~Background(){ delete config; }

    void moveX(int setoff);

public slots:
    void scrolling();
    void swap();
    void restart1();
    void restart2();
    void freeze(){
        if(!pause){
            pause = true;
        }
        else {
            pause = false;
        }
    }

private:
    QString back_pic_str;
    QPixmap background_pic;
    Config* config;
    bool pause;
};

#endif // BACKGOUND_H
