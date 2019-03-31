#include "stickman.h"
#include <QPainter>
#include <QTimer>

StickMan::StickMan(int starting_pos,
                   float stickman_size,
                   int back_h,
                   QString stickman_clothes):
    starting_pos(starting_pos),
    stickman_size(stickman_size),
    back_h(back_h),
    stickman_pic_str(stickman_clothes),
    current_frame(0),
    pause(false)
{
    stickman_pic = QPixmap(stickman_clothes);

    base_stick_h = stickman_pic.height();
    base_stick_w = stickman_pic.width();
    start();
}

void StickMan::start(){
    qDebug() << "start called, size is " << stickman_size;
    //The height needs to be constrainted.
    int stickman_h = int(base_stick_h * stickman_size);
    int stickman_w =int(base_stick_w * stickman_size);
    this->stickman_pic = stickman_pic.scaled(stickman_w, stickman_h, Qt::KeepAspectRatio);

    QTimer* timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
    timer->start(40);
    qDebug() << "start ended";
}

void StickMan::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    int stickman_h = int(base_stick_h * stickman_size);
    if (current_frame >= int(1191 * stickman_size)){
        current_frame = 0;
    }
    painter->drawPixmap(starting_pos,back_h-stickman_h, stickman_pic, current_frame, 0,
                        int(45 * stickman_size), int(73 * stickman_size));
    Q_UNUSED(widget);
    Q_UNUSED(option);
    if(!pause){
        current_frame += int(57 * stickman_size);
    }

}

void StickMan::bgChange(){
    if (back_h == 720){
        back_h = 750;
    }
    else if (back_h == 750) {
        back_h = 619;
    }
    else if (back_h == 619) {
        back_h = 720;
    }
}

void StickMan::clothesChange(){
    if (stickman_pic_str == ":/Images/firemario.png"){
        stickman_pic_str = QString(":/Images/mario.png");
    }
    else if (stickman_pic_str == ":/Images/mario.png") {
        stickman_pic_str = QString(":/Images/firemario.png");
    }
    stickman_pic = QPixmap(stickman_pic_str);
    base_stick_h = stickman_pic.height();
    base_stick_w = stickman_pic.width();
    int stickman_h = int(base_stick_h * stickman_size);
    int stickman_w = int(base_stick_w * stickman_size);
    stickman_pic = stickman_pic.scaled(stickman_w, stickman_h, Qt::KeepAspectRatio);
    current_frame = 0;
    qDebug() << "the stickman's clothes has changed to " << stickman_pic_str;
}

void StickMan::sizeChange(){
    float tmp_size = stickman_size - 0.25;
    setStickman_size(tmp_size);
    if(stickman_size < 0.75){
        setStickman_size(1.5);
    }
    int stickman_h = int(base_stick_h * stickman_size);
    int stickman_w = int(base_stick_w * stickman_size);
    stickman_pic = stickman_pic.scaled(stickman_w, stickman_h, Qt::KeepAspectRatio);
    current_frame = 0;
    qDebug() << "size has been changed to " << stickman_size;
}

int StickMan::getStarting_pos() const
{
    return starting_pos;
}

void StickMan::setStarting_pos(int value)
{
    starting_pos = value;
}

float StickMan::getStickman_size() const
{
    return stickman_size;
}

void StickMan::setStickman_size(float value)
{
    stickman_size = value;
}
