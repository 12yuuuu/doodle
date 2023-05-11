#ifndef GAME_H
#define GAME_H

#include <QGraphicsPixmapItem>
#include <QWidget>
#include <QGraphicsScene>
#include <vector>
#include <QTimer>
#include <QGraphicsTextItem>
#include <QFont>
#include <QMediaPlayer>
#include <QBrush>
#include <QImage>
#include <QGraphicsView>
#include <QDebug>
#include <QPixmap>
#include <QGraphicsTextItem>
#include "player.h"
#include "platform.h"
#include "monster.h"
#include "score.h"
#include "item.h"
#include "button.h"

class Player;
class Platform;
class Monster;
class Score;
class Item;
class Button;

class Game: public QGraphicsView
{
public:
    Game();
    QGraphicsScene * scene;
    Player * player;
    //Monster * monster;
    std::vector<Platform*> platform;
    std::vector<Monster*> monster;
    Platform * plat;
    std::vector<Item*> item;
    void movePlatforms(double);
    void createPlatform();
    void endGame(int);
    void startplay();
    Score * score;
    //Item * items;
    int lastSpecialPlatformScore;
    int lastpy = 0;
    QGraphicsPixmapItem * toolbar, * gameover;
    bool startgame = false;
    QTimer * timer;
    QGraphicsPixmapItem * welcomeBackground;
    Button * playButton;
    QGraphicsView * view;
    bool hasItem = false;
    bool hasMonster = false;
    QGraphicsPixmapItem* hearts[3];
    int numHearts = 3;
    void decreaseHp();
    //void platformDis();
    //void bulletDis();
public slots:
    void start();
};

#endif // GAME_H