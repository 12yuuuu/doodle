#include "Player.h"

extern Game * game;

Player::Player(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    vel = 5;
    // set graphic
    QPixmap playerPixmap("./dataset/images/doodleL.png");
    setPixmap(playerPixmap);
    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    connect(timer, &QTimer::timeout, this, &Player::Camera);
    connect(timer, SIGNAL(timeout()), this, SLOT(highest(bool)));
    timer->start(8);
    shoot = new QMediaPlayer;
    shoot->setMedia(QUrl::fromLocalFile("./dataset/sounds/shoot.wav"));
        // 設定音量
    shoot->setVolume(50);

    jump = new QMediaPlayer;
    jump->setMedia(QUrl::fromLocalFile("./dataset/sounds/jump.wav"));
        // 設定音量
    jump->setVolume(50);
}

void Player::keyPressEvent(QKeyEvent *event)
{
    // move the player left and right
    if (event->key() == Qt::Key_Left)
    {
        leftface = true;
        setPixmap(QPixmap("./dataset/images/doodleUL.png"));
        if (pos().x() <= 0)
        {
            setX(540);
        }
        dx = -4;
        timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(moveX()));
        timer->start(5);
    }
    else if (event->key() == Qt::Key_Right)
    {
        leftface = false;
        setPixmap(QPixmap("./dataset/images/doodleUR.png"));
        if (pos().x() >= 540)
        {
            setX(0);
        }
        dx = 4;
        timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(moveX()));
        timer->start(5);
    }
    
    // shoot with the spacebar
    else if (event->key() == Qt::Key_Space)
    {
        // Get the current mouse position
        QPoint mousePos = QCursor::pos();
        QPointF playerPos = this->pos();
        Bullet *bullet = new Bullet(nullptr, playerPos.x(), playerPos.y(),mousePos.x()-1172, mousePos.y()-375);
        scene()->addItem(bullet);
        setZValue(1);
        setPixmap(QPixmap("./dataset/images/doodleS.png"));
        shoot->play();
    }
}

void Player::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left)
    {
        dx = 0;
        disconnect(timer, SIGNAL(timeout()), this, SLOT(moveX()));
    }
    else if (event->key() == Qt::Key_Right)
    {
        dx = 0;
        disconnect(timer, SIGNAL(timeout()), this, SLOT(moveX()));
    }
}

void Player::move()
{
    if (vel <= -5)
    {
        QList<QGraphicsItem*> colliding_items1 = collidingItems();
        for(int i = 0, n = colliding_items1.size();i<n; ++i)
        {
            Platform * platform = dynamic_cast<Platform *>(colliding_items1[i]);
            if(platform)
            {
                if(leftface)
                    setPixmap(QPixmap("./dataset/images/doodleL.png"));
                else
                    setPixmap(QPixmap("./dataset/images/doodleR.png"));
                platform->collide(this, platform->getType());
                yCounter = 0; 
                jump->play(); 
            }
        }
    }
    
    QList<QGraphicsItem*> colliding_items2 = collidingItems();
    for(int i = 0, n = colliding_items2.size();i<n; ++i)
    {
        Monster * monster = dynamic_cast<Monster *>(colliding_items2[i]);
        if(monster)
        {
            monster->collide(this);
            yCounter = 0;
        }
    }
    QList<QGraphicsItem*> colliding_items3 = collidingItems();
    for(int i = 0, n = colliding_items3.size();i<n; ++i)
    {
        Item * item = dynamic_cast<Item *>(colliding_items3[i]);
        if(item)
        {
            item->collide(this, item->getType());
        }
    }

    yCounter++;
    if (touchSpring)
    {
        vel = 10;
        if (middle)
        {
            vel = 0;
            deltaY = -10;
            game -> movePlatforms(deltaY);
        }
        if (yCounter == 96)
        {
            vel = -5;
            yCounter = 0;
            middle = false;
            touchSpring =false;
        }
    }
    else if (touchTrampoline)
    {
        vel = 10;
        if (middle)
        {
            vel = 0;
            deltaY = -20;
            game -> movePlatforms(deltaY);
        }
        if (yCounter == 96)
        {
            vel = -5;
            yCounter = 0;
            middle = false;
            touchTrampoline =false;
        }
    }
    else if (touchHat)
    {
        if (middle)
        {
            deltaY = -40;
            game -> movePlatforms(deltaY);
        }
        if (yCounter == 96)
        {
            //3840
            vel = -5;
            yCounter = 0;
            middle = false;
            touchHat =false;
            if(leftface)
                setPixmap(QPixmap("./dataset/images/doodleUL.png"));
            else
                setPixmap(QPixmap("./dataset/images/doodleUR.png"));
        }
        if (hcount >= 4)
        {
            hcount = 1;
        }
        QString hatImagePath = QString("./dataset/images/doodleH/doodleH%1.png").arg(hcount);
        QPixmap hatPixmap(hatImagePath);
        setPixmap(hatPixmap);
        hcount++;
    }
    else if (touchJet)
    {
        if (middle)
        {
            deltaY = -80;
            game -> movePlatforms(deltaY);
        }
        if (yCounter == 96)
        {
            //7680
            vel = -5;
            yCounter = 0;
            middle = false;
            touchJet =false;
            if(leftface)
                setPixmap(QPixmap("./dataset/images/doodleUL.png"));
            else
                setPixmap(QPixmap("./dataset/images/doodleUR.png"));
        }
        if (jcount >= 10)
        {
            jcount = 1;
        }  
        QString jetImagePath = QString("./dataset/images/doodleJ/doodleJ%1.png").arg(jcount);
        QPixmap jetPixmap(jetImagePath);
        setPixmap(jetPixmap);
        jcount++;
    }
    else
    {
        if (middle)
        {
            deltaY = -5;
            game -> movePlatforms(deltaY);
        }
        if (yCounter == 64)
        {
            vel = -5;
            yCounter = 0;
            middle = false;
        }
    }
    setY(pos().y() - vel);
    //end gmae
    if (pos().y() > 960)
    {
        for(int i = 0; i < 1; i++)
        {
            game -> endGame(game -> score ->getfinalscore());
        }
    }
}

void Player::setVel()
{   
    vel = 5;
    if(leftface)
        setPixmap(QPixmap("./dataset/images/doodleUL.png"));
    else
        setPixmap(QPixmap("./dataset/images/doodleUR.png"));
}

double Player::getVel()
{
    return vel;
}

void Player::Camera()
{
    if (pos().y() < 480)
    {
        middle = true;
        vel = 0;
    }
}

void Player::highest(bool first)
{
    if(first){
        height = 480; 
    }
    else{
        height += 5;
    }
    game -> score -> increase(height);
}

void Player::moveX()
{
    setX(pos().x()+dx);
    timer->start(5);
}