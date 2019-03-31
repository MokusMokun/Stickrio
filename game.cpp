#include "game.h"
#include <QMediaPlaylist>
#include "buttonbuilder.h"

Game::Game()
{
    config = new Config(":/config.json");
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1024,768);

    // set up the scene
    scene = new QGraphicsScene();
    scene->setBackgroundBrush(Qt::black);
    setScene(scene);
}

void Game::start()
{
    scene->clear();

    // Get the configrations from the config.json
    QString back_image_str = config->getBack_image();
    QPixmap back_image = QPixmap(back_image_str);
    QString stickman_image = config ->getStickman_pic();
    int start_pos = config->getStarting_pos() * 10;
    float stickman_size = config->getStickman_size();

    int back_height = back_image.height();
    int back_width = back_image.width();
    int view_width = back_height * 4/3;

    // Set the screen size
    setFixedSize(view_width,back_height);
    scene->setSceneRect(0,0,view_width,back_height);
    qDebug() << "The width is " << back_width << ", height is " << back_height;

    // Create scrolling background
    Background* background1 =
            new Background(back_image_str, config);
    Background* background2 =
            new Background(back_image_str, config);
    scene->addItem(background1);
    scene->addItem(background2);
    background2->moveX(back_width);

    // Create the still stickman
    StickMan* stickMan =
            new StickMan(start_pos, stickman_size, back_height, stickman_image);
    scene->addItem(stickMan);

    // Play background music in a loop
    QMediaPlaylist *playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/Music/sans.flac"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    MyMediaPlayer* B_player = new MyMediaPlayer();
    B_player->setPlaylist(playlist);
    B_player->setVolume(30);
    B_player->play();


    // Create all the buttons via the button builder
    ButtonBuilder* buttonBuilder = new ButtonBuilder(pauseButton);
    buttonBuilder->setWindowWidth(this->width());
    buttonBuilder->setWindowHeight(this->height());

    buttonBuilder->setName("Pause/Resume");
    int pause_x = buttonBuilder->setXcoordinate(float(0.5));
    int pause_y = buttonBuilder->setYcoordinate(float(0.1));
    pauseButton = buttonBuilder->getButton();
    pauseButton->setPos(pause_x,pause_y);
    connect(pauseButton,SIGNAL(clicked()),background1,SLOT(freeze()));
    connect(pauseButton,SIGNAL(clicked()),background2,SLOT(freeze()));
    connect(pauseButton,SIGNAL(clicked()),B_player,SLOT(pause_resume()));
    connect(pauseButton,SIGNAL(clicked()),stickMan,SLOT(freeze()));
    scene->addItem(pauseButton);

    buttonBuilder->reset(exitButton);
    buttonBuilder->setName("Exit");
    int resume_x = buttonBuilder->setXcoordinate(float(0.85));
    int resume_y = buttonBuilder->setYcoordinate(float(0.1));
    exitButton = buttonBuilder->getButton();
    exitButton->setPos(resume_x,resume_y);
    connect(exitButton,SIGNAL(clicked()),this,SLOT(close()));
    scene->addItem(exitButton);

    buttonBuilder->reset(saveButton);
    buttonBuilder->setName("Save");
    int save_x = buttonBuilder->setXcoordinate(float(0.15));
    int save_y = buttonBuilder->setYcoordinate(float(0.1));
    saveButton = buttonBuilder->getButton();
    saveButton->setPos(save_x,save_y);
    connect(saveButton,SIGNAL(clicked()),config,SLOT(save()));
    scene->addItem(saveButton);

    buttonBuilder->reset(sizeButton);
    buttonBuilder->setName("Change Size");
    int size_x = buttonBuilder->setXcoordinate(float(0.15));
    int size_y = buttonBuilder->setYcoordinate(float(0.2));
    sizeButton = buttonBuilder->getButton();
    sizeButton->setPos(size_x,size_y);
    connect(sizeButton,SIGNAL(clicked()),stickMan,SLOT(sizeChange()));
    connect(sizeButton,SIGNAL(clicked()),config,SLOT(modify_size()));
    scene->addItem(sizeButton);

    buttonBuilder->reset(clothesButton);
    buttonBuilder->setName("Clothes");
    int clo_x = buttonBuilder->setXcoordinate(float(0.5));
    int clo_y = buttonBuilder->setYcoordinate(float(0.2));
    clothesButton = buttonBuilder->getButton();
    clothesButton->setPos(clo_x,clo_y);
    connect(clothesButton,SIGNAL(clicked()),stickMan,SLOT(clothesChange()));
    connect(clothesButton,SIGNAL(clicked()),config,SLOT(modify_clothes()));
    scene->addItem(clothesButton);

    buttonBuilder->reset(bgButton);
    buttonBuilder->setName("Background");
    int back_x = buttonBuilder->setXcoordinate(float(0.85));
    int back_y = buttonBuilder->setYcoordinate(float(0.2));
    bgButton = buttonBuilder->getButton();
    bgButton->setPos(back_x,back_y);
    connect(bgButton,SIGNAL(clicked()),stickMan,SLOT(bgChange()));
    connect(bgButton,SIGNAL(clicked()),background1,SLOT(swap()));
    connect(bgButton,SIGNAL(clicked()),background2,SLOT(swap()));
    connect(bgButton,SIGNAL(clicked()),background1,SLOT(restart1()));
    connect(bgButton,SIGNAL(clicked()),background2,SLOT(restart2()));
    connect(bgButton,SIGNAL(clicked()),config,SLOT(modify_bg()));
    connect(bgButton,SIGNAL(clicked()),this,SLOT(resize()));
    scene->addItem(bgButton);

}



void Game::resize(){
    QString back_image_str = config->getBack_image();
    QPixmap back_image = QPixmap(back_image_str);
    QString stickman_image = config ->getStickman_pic();

    int back_height = back_image.height();
    int back_width = back_image.width();
    int view_width = back_height * 4/3;

    // Reset the screen size
    setFixedSize(view_width,back_height);
    scene->setSceneRect(0,0,view_width,back_height);
    qDebug() << "The window size now has been reseted to: " << back_width << "x" << back_height;

    int pause_x = this->width()*0.5 - pauseButton->boundingRect().width()/2;
    int pause_y = this->height()*0.1 - pauseButton->boundingRect().height()/2;
    pauseButton->setPos(pause_x,pause_y);

    int resume_x = this->width()*0.85 - exitButton->boundingRect().width()/2;
    int resume_y = this->height()*0.1 - exitButton->boundingRect().height()/2;
    exitButton->setPos(resume_x,resume_y);

    int save_x = this->width()*0.15 - saveButton->boundingRect().width()/2;
    int save_y = this->height()*0.1 - saveButton->boundingRect().height()/2;
    saveButton->setPos(save_x,save_y);

    int clo_x = this->width()*0.5 - clothesButton->boundingRect().width()/2;
    int clo_y = this->height()*0.2 - clothesButton->boundingRect().height()/2;
    clothesButton->setPos(clo_x,clo_y);

    int size_x = this->width()*0.15 - sizeButton->boundingRect().width()/2;
    int size_y = this->height()*0.2 - sizeButton->boundingRect().height()/2;
    sizeButton->setPos(size_x,size_y);

    int back_x = this->width()*0.85 - bgButton->boundingRect().width()/2;
    int back_y = this->height()*0.2 - bgButton->boundingRect().height()/2;
    bgButton->setPos(back_x,back_y);

}

void Game::displayMainMenu(){
    scene->clear();
    // create the title text
    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Stickrio"));
    QFont titleFont("comic sans",50);
    titleText->setFont(titleFont);
    int txPos = this->width()/2 - titleText->boundingRect().width()/2;
    int tyPos = 150;
    titleText->setPos(txPos,tyPos);
    scene->addItem(titleText);

    // create the play button
    Button* playButton = new Button(QString("Play"));
    int bxPos = this->width()/2 - playButton->boundingRect().width()/2;
    int byPos = 350;
    playButton->setPos(bxPos,byPos);
    connect(playButton,SIGNAL(clicked()),this,SLOT(start()));
    scene->addItem(playButton);

    // create the quit button
    Button* quitButton = new Button(QString("Quit"));
    int qxPos = this->width()/2 - quitButton->boundingRect().width()/2;
    int qyPos = 450;
    quitButton->setPos(qxPos,qyPos);
    connect(quitButton,SIGNAL(clicked()),this,SLOT(close()));
    scene->addItem(quitButton);
}
