#include "bullet.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <qmath.h>
#include <QDebug>

Bullet::Bullet(QGraphicsItem *parent, double startX, double startY, double targetX, double targetY): QObject(), QGraphicsPixmapItem(parent)
{
    // draw graphics
    setPixmap(QPixmap("./dataset/images/bullet.png"));
    setPos(startX+40, startY-40);
    double dx = targetX - startX;
    double dy = targetY - startY;

    // 根据移動向量计算移動單位向量
    double length = std::sqrt(dx * dx + dy * dy);
    double unitX = dx / length;
    double unitY = dy / length;

    // 設置子彈的移動速度
    double speed = 50;
    dx = unitX * speed;
    dy = unitY * speed;

    // 保存移動向量
    this->dx = dx;
    this->dy = dy;

    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(50);
}

void Bullet::move()
{
    QList<QGraphicsItem*> colliding_bullet = collidingItems();
    for(int i = 0, n = colliding_bullet.size();i<n; ++i)
    {
        Monster * monster = dynamic_cast<Monster *>(colliding_bullet[i]);
        if(monster)
        {
            monster->hit(game);
        }
    }
    setPos(x()+dx, y()+dy);
}