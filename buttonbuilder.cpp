#include "buttonbuilder.h"


void ButtonBuilder::setName(QString name)
{
    button = new Button(name);
}

int ButtonBuilder::setXcoordinate(float x){
    int x_coord = window_width*x - button->boundingRect().width()/2;
    return x_coord;
}

int ButtonBuilder::setYcoordinate(float y){
    int y_coord = window_height*y - button->boundingRect().height()/2;
    return y_coord;
}

void ButtonBuilder::setWindowWidth(int value)
{
    window_width = value;
}

void ButtonBuilder::setWindowHeight(int value)
{
    window_height = value;
}
