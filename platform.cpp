#include "platform.h"

enum platformstypes {
    normal = 0,
    broken = 1,
    moving = 2,
    disappear = 3,
};

Platform::Platform(int t)
{
    type = t;
    switch (t)
    {
    case 0:
        setPixmap(QPixmap("./dataset/images/stair-basic.png"));
        break;
    case 1:
        setPixmap(QPixmap("./dataset/images/stair-broken1.png"));
        break;
    case 2:
        setPixmap(QPixmap("./dataset/images/stair-blue.png"));
        break;
    case 3:
        setPixmap(QPixmap("./dataset/images/stair-disapear.png"));
        break;
    default:
        setPixmap(QPixmap("./dataset/images/stair-basic.png"));
        break;
    }
    setZValue(1);

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Platform::move);
    timer->start(50);

    platformbreak = new QMediaPlayer;
    platformbreak->setMedia(QUrl::fromLocalFile("./dataset/sounds/break.wav"));
        // 設定音量
    platformbreak->setVolume(50);
}

void Platform::collide(Player * player, int n)
{   
    switch (n)
    {
        case 0:
            if(player->vel <= -5)
            {
                if(player->pos().y() + player->pixmap().height() >= pos().y() - pixmap().height())
                {
                    player->setVel();
                }
            }
            break;
        case 1:
            if(player->vel <= -5)
            {
                if(player->pos().y() + player->pixmap().height() >= pos().y() - pixmap().height())
                {
                    platformbreak->play();
                    qDebug()<<"broken";
                    player->setVel();
                    for (int i = 0; i <= 4; ++i)
                    {
                        QString brokenImagePath = QString("./dataset/images/stair-broken%1.png").arg(i);
                        QPixmap brokenPixmap(brokenImagePath);
                        setPixmap(brokenPixmap);
                    }
                    QTimer* timer = new QTimer(this);
                    connect(timer, &QTimer::timeout, this, &Platform::down);
                    timer->start(10);
                }  
            }
            break;
        case 2:
            if(player->vel <= -5)
            {
                if(player->pos().y() + player->pixmap().height() >= pos().y() - pixmap().height())
                {
                    qDebug()<<"moving";
                    player->setVel();
                }
            }
            break;
        case 3:
            if(player->vel <= -5)
            {
                if(player->pos().y() + player->pixmap().height() >= pos().y() - pixmap().height())
                {
                    qDebug()<<"disappear";
                    player->setVel();
                    
                }
            }
            break;
    }
}

int Platform::getType() 
{
    return type;
}

void Platform::down()
{
    setY(pos().y() + 10);
}

void Platform::move()
{
    if (getType() == 2)
    {
        if (pos().x() >= 420)
            v = -5;
        else if (pos().x() <= 0)
            v = 5;
        setX(pos().x() + v);
    }
}