#ifndef ITEM_H
#define ITEM_H

#include "player.h"
#include "game.h"
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>

class Game;
class Player;

class Item: public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    Item(int);
    QTimer * timer;
    Game * game;
    void collide(Player*, int);
    int type;
    int getType(); 
};

#endif