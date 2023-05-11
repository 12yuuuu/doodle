#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QImage>
#include <QGraphicsItem>
#include <QPixmap>
#include <QLabel>
#include <QList>
#include <vector>
#include "platform.h"
#include "score.h"
#include "item.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include "bullet.h"
#include <QPointF>
#include <QTimer>
#include <QtGlobal>
#include <QMediaPlayer>

#include <QDebug>

class Platform;
class Item;

class Player:public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Player(QGraphicsItem * parent=0);
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent *event);
    double vel;
    double jumpheight;
    double getVel();
    void setVel();
    Platform * platform;
    void Camera();
    bool leftface = true;
    int height = 0;
    Item * item;
    bool middle = false;
    double deltaY = 0;
    int yCounter = 0;
    bool touchSpring = false;
    bool touchTrampoline = false;
    bool touchHat = false;
    bool touchJet = false;
    int hcount = 1;
    int jcount = 1;
    int dx = 0;
    QTimer* timer, timerx;
    int before = 960;
    bool first = true;
    QMediaPlayer *shoot, *jump;
public slots:
    void moveX();
    void move();
    void highest(bool);
};

#endif // PLAYER_H