#include "mymediaplayer.h"

MyMediaPlayer::MyMediaPlayer():
    isPlaying(true)
{
}

void MyMediaPlayer::pause_resume(){
    if(!isPlaying){
        this->play();
        isPlaying = true;
    }
    else {
        this->pause();
        isPlaying = false;
    }
}
