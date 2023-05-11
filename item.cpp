#include "item.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h> 

enum items {
    noitem,
    spring,
    trampoline,
    propellerhat,
    jetpack,
};

Item::Item(int t): QObject(), QGraphicsPixmapItem(nullptr)
{
    type = t;
    switch (t)
    {
    case 0:
        break;
    case 1:
        setPixmap(QPixmap("./dataset/images/item-spring1.png"));
        break;
    case 2:
        setPixmap(QPixmap("./dataset/images/item-trampoline1.png"));
        break;
    case 3:
        setPixmap(QPixmap("./dataset/images/item-propeller-hat.png"));
        break;
    case 4:
        setPixmap(QPixmap("./dataset/images/item-jetpack.png"));
        break;
    default:
        break;
    }
    setZValue(1);
}

void Item::collide(Player * player, int n)
{
    switch (n)
    {
        case 0:
            break;
        case 1:
            if (player->vel < 0 && player->pos().y() + player->pixmap().height() >= pos().y() - pixmap().height())
            {
                setPixmap(QPixmap("./dataset/images/item-spring2.png"));
                player->yCounter = 0;
                player->touchSpring = true;
            }
            break;
        case 2:
            if (player->vel < 0 && player->pos().y() + player->pixmap().height() >= pos().y() - pixmap().height())
            {
                for (int i = 0; i <= 3; ++i)
                {
                    QString trampolineImagePath = QString("./dataset/images/item-trampoline%1.png").arg(i);
                    QPixmap trampolinePixmap(trampolineImagePath);
                    setPixmap(trampolinePixmap);
                }
                player->yCounter = 0;
                player->touchTrampoline = true;
            }  
            break;
        case 3:
            player->yCounter = 0;
            player->touchHat = true;
            break;
        case 4:
            player->yCounter = 0;
            player->touchJet = true;
            break;
    }
}

int Item::getType() 
{
    return type;
}