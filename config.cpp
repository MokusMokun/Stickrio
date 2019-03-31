#include "config.h"
#include <fstream>
#include <QDebug>
#include <QFile>
#include <QJsonObject>
#include <QIODevice>
#include <QDir>

Config::Config(std::string fileName):
    save_count(0)
{
    QString str = QString::fromUtf8(fileName.c_str());
    QString json_content;
    QFile file;
    file.setFileName(str);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "The specified file is missing";
        exit(1);
    }
    json_content = file.readAll();
    file.close();

    json_document = QJsonDocument::fromJson(json_content.toUtf8());
    QJsonObject json_object = json_document.object();
    QJsonValue stickman_val = json_object.value(QString("stickman"));
    QJsonObject stickman_obj = stickman_val.toObject();
    QJsonValue background_val = json_object.value(QString("background"));
    QJsonObject background_obj = background_val.toObject();

    back_image = background_obj["image_name"].toString();

    stickman_size_str = stickman_obj["size"].toString();
    setStickman_size(stickman_size_str);
    starting_pos = stickman_obj["initial_position"].toInt();
    starting_velocity = stickman_obj["speed"].toInt();
    stickman_clothes = stickman_obj["sequence"].toString();

    qDebug() << "size: " <<  getStickman_size()
             << ";pos: " << starting_pos
             << ";speed: " << starting_velocity;
}


void Config::save()
{
    setStarting_pos(20);
    QString filename = QString("%1/config.json").arg(QDir::currentPath(), save_count);
    QFile saveFile(filename);
    saveFile.open(QFile::WriteOnly);
    QJsonObject RootObject = json_document.object();
    QJsonValueRef stick_ref = RootObject.find("stickman").value();
    QJsonObject stick_obj = stick_ref.toObject();
    QJsonValueRef back_ref = RootObject.find("background").value();
    QJsonObject back_obj = back_ref.toObject();

    stick_obj.insert("size",stickman_size_str);//set the value you want to modify
    stick_obj.insert("initial_position", starting_pos);
    stick_obj.insert("speed",starting_velocity);
    stick_obj.insert("sequence", stickman_clothes);
    stick_ref = stick_obj; //assign the modified object to reference

    back_obj.insert("image_name",back_image);
    back_ref = back_obj;

    json_document.setObject(RootObject); // set to json document
    saveFile.write(json_document.toJson());
    saveFile.close();
    save_count++;
    qDebug() << "save file created in " << QDir::currentPath();
}

void Config::modify_bg(){
    if (back_image == ":/Images/back_1.png"){
        back_image = QString(":/Images/back_2.jpg");
    }
    else if (back_image == ":/Images/back_2.jpg"){
        back_image = QString(":/Images/back_3.jpg");
    }
    else if (back_image == ":/Images/back_3.jpg") {
        back_image = QString(":/Images/back_1.png");
    }
}

void Config::modify_clothes(){
    if (stickman_clothes == ":/Images/firemario.png"){
        stickman_clothes = QString(":/Images/mario.png");
    }
    else if (stickman_clothes == ":/Images/mario.png") {
        stickman_clothes = QString(":/Images/firemario.png");
    }
}

void Config::modify_size(){
    if(stickman_size_str == "tiny"){
        stickman_size_str = QString("giant");
    }
    else if (stickman_size_str == "normal") {
        stickman_size_str = QString("tiny");
    }
    else if (stickman_size_str == "large") {
        stickman_size_str = QString("normal");
    }
    else if (stickman_size_str == "giant") {
        stickman_size_str = QString("large");
    }
    qDebug() << "size modified, now is '" << stickman_size_str << "'";
}

float Config::getStickman_size() const
{
    return stickman_size;
}

void Config::setStickman_size(QString value)
{
    if(value == "tiny"){
        stickman_size = 0.75;
    }
    else if(value == "normal"){
        stickman_size = 1;
    }
    else if(value == "large"){
        stickman_size = 1.25;
    }
    else if(value == "giant"){
        stickman_size = 1.5;
    }
    else{
        qDebug() << "Please specify a valid stickman size in the config "
                    "file (tiny/normal/large/giant)";
        exit(1);
    }
}

QString Config::getBack_image() {
    return back_image;
}

void Config::setBack_image(QString value)
{
    back_image = value;
}

int Config::getStarting_pos() const{
    return starting_pos;
}

void Config::setStarting_pos(int value)
{
    starting_pos = value;
}

int Config::getStarting_velocity() const
{
    return starting_velocity;
}

void Config::setStarting_velocity(int value)
{
    starting_velocity = value;
}

QString Config::getStickman_pic() const
{
    return stickman_clothes;
}

