#ifndef BUTTONBUILDER_H
#define BUTTONBUILDER_H
#include "button.h"


class ButtonBuilder
{
public:
    ButtonBuilder(Button* button):
        button(button)
    {}
    ~ButtonBuilder(){ delete button; }

    void setName(QString name);

    // set a relative position to the game window
    int setXcoordinate(float x);
    int setYcoordinate(float y);

    // get the current window size to the builder
    void setWindowWidth(int value);
    void setWindowHeight(int value);

    void reset(Button* button){
        this->button = button;
    }
    Button* getButton(){
        return button;
    }
private:
    Button* button;
    int window_width;
    int window_height;
};

#endif // BUTTONBUILDER_H
