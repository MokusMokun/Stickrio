#ifndef CONFIG_H
#define CONFIG_H

#include <iostream>
#include <QPixmap>
#include <QJsonDocument>

class Config: public QObject
{
    Q_OBJECT
public:
    Config(std::string fileName);

    ~Config(){}


    float getStickman_size() const;
    void setStickman_size(QString value);

    QString getBack_image();
    void setBack_image(QString value);

    void setStarting_pos(int value);
    int getStarting_pos() const;

    int getStarting_velocity() const;
    void setStarting_velocity(int value);

    QString getStickman_pic() const;

public slots:
    void save();
    void modify_size();
    void modify_clothes();
    void modify_bg();

private:
    float stickman_size;
    QString stickman_size_str;
    int starting_pos;
    int starting_velocity;
    QString stickman_clothes;
    QString back_image;
    int save_count;
    QJsonDocument json_document;
};

#endif // CONFIG_H
