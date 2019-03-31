#ifndef MYMEDIAPLAYER_H
#define MYMEDIAPLAYER_H

#include <QMediaPlayer>

class MyMediaPlayer: public QMediaPlayer{
    Q_OBJECT
public:
    MyMediaPlayer();

public slots:
    void pause_resume();

private:
    bool isPlaying;
};

#endif // MYMEDIAPLAYER_H
