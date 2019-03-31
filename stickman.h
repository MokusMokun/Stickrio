#ifndef STICKMAN_H
#define STICKMAN_H

#include <QGraphicsObject>
#include <QDebug>
#include <config.h>
#include <QPainter>


class StickMan:public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    StickMan(int starting_pos,
             float stickman_size,
             int back_height,
             QString stickman_clothes);
    ~StickMan(){}

    void start();

    int getStarting_pos() const;
    void setStarting_pos(int value);

    float getStickman_size() const;
    void setStickman_size(float value);

    // QGraphicsItem interface
    QRectF boundingRect() const{
        return QRectF(0,0,45,73);
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public slots:
    void nextFrame(){
        update();
    }
    void bgChange();
    void sizeChange();
    void clothesChange();
    void freeze(){
        if(!pause){
            pause = true;
        }
        else {
            pause = false;
        }
    }


private:
    int starting_pos;
    float stickman_size;
    int base_stick_h;
    int base_stick_w;
    int back_h;
    QPixmap stickman_pic;
    QString stickman_pic_str;
    int current_frame;
    bool pause;
};

#endif // STICKMAN_H
