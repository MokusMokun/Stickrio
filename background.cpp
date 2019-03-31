#include "background.h"

Background::Background(QString back_pic_str, Config* config):
    back_pic_str(back_pic_str), config(config)
{
    background_pic = QPixmap(back_pic_str);
    setPixmap(background_pic);

    pause = false;
    QTimer* timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(scrolling()));

    timer->start(30);
}

void Background::swap(){
    if(back_pic_str == ":/Images/back_1.png"){
        back_pic_str = ":/Images/back_2.jpg";
    }
    else if (back_pic_str == ":/Images/back_2.jpg") {
        back_pic_str = ":/Images/back_3.jpg";
    }
    else if (back_pic_str == ":/Images/back_3.jpg") {
        back_pic_str = ":/Images/back_1.png";
    }
    background_pic = QPixmap(back_pic_str);
    setPixmap(background_pic);
    qDebug() << "background has been switched to " << back_pic_str;
}

void Background::restart1(){
    setPos(0,0);
}

void Background::restart2(){
    setPos(- background_pic.width(),0);
}

void Background::scrolling(){
//     scrolling backwards
    int width = this->background_pic.width();
    int velocity = this->config->getStarting_velocity() * 5;
    if(!pause){
        if(pos().x() <= (-width)){
            setPos(x()+width*2,y());
        }
        setPos(x()-velocity,y());
    }


}

void Background::moveX(int setoff){
    setPos(x()+setoff,y());
}
