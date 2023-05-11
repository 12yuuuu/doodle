#include "monster.h"

Monster::Monster(int t)
{
    switch (t)
    {
    case 0:
        break;
    case 1:
        setPixmap(QPixmap("./dataset/images/monster1.png"));
        break;
    case 2:
        setPixmap(QPixmap("./dataset/images/monster2.png"));
        break;
    case 3:
        setPixmap(QPixmap("./dataset/images/monster3.png"));
        break;
    case 4:
        setPixmap(QPixmap("./dataset/images/monster4.png"));
        break;
    default:
        break;
    }
    setZValue(3);

    jumponmonster = new QMediaPlayer;
    jumponmonster->setMedia(QUrl::fromLocalFile("./dataset/sounds/jumponmonster.wav"));
        // 設定音量
    jumponmonster->setVolume(50);
}

void Monster::collide(Player * player)
{
    if (player->getVel() < 0) 
    {
        if(player->pos().y() + player->pixmap().height() >= pos().y() - pixmap().height())
        {
            jumponmonster->play();
            QTimer* timer = new QTimer(this);
            connect(timer, SIGNAL(timeout()), this, SLOT(move()));
            timer->start(50);
            player->setVel();
        }
    } 
    else 
    {
        if (!hasCollidedWithPlayer)
            game->decreaseHp();
    }
    hasCollidedWithPlayer = true;
}

void Monster::hit(Game * game)
{
    game->scene->removeItem(this);
}

void Monster::move()
{
    setY(pos().y() + 10);
}


