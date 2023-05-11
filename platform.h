#ifndef PLATFORM_H
#define PLATFORM_H

#include "player.h"
#include "game.h"
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QGraphicsItem>
#include <QPixmap>
#include <QGraphicsScene>
#include <QtGlobal>
#include <QDebug>
#include "item.h"
#include <QMediaPlayer>

class Player;
class Game;
class Item;

class Platform: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    Platform(int);     
    void collide(Player *, int);
    Game * game;
    Player * player;
    int getType();
    int type;
    int v = 5;
    QMediaPlayer  *platformbreak;
public slots:
    void move();
    void down();
};
#endif