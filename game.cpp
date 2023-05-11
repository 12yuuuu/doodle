#include "Game.h"
#include <QGraphicsTextItem>
#include <QFont>
#include <QMediaPlayer>
#include <QBrush>
#include <QImage>
#include <QGraphicsView>
#include <QObject>
#include <QMessageBox>
#include <QGraphicsPixmapItem>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QString>

#include <QDebug>

Game::Game()
{
    //start interface
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,540,960);
    //setBackgroundBrush(QBrush(QImage("./dataset/images/welcome.png"))); 
    setScene(scene);
 
    QPixmap backgroundPixmap("./dataset/images/welcome.png");
    scene->setBackgroundBrush(backgroundPixmap);
 
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(540,960);
    
    QTimer* timer = new QTimer(this);
    playButton = new Button();
    connect(playButton, &Button::clicked, this, &Game::startplay);
    scene->addItem(playButton);
    timer->start(20);  
}

void Game::startplay()
{
    if(scene)
    {
        scene -> removeItem(playButton);
        delete playButton;
        playButton = nullptr;
        scene -> clear();
    }
    QPixmap backgroundPixmap("./dataset/images/background.png");
    scene->setBackgroundBrush(backgroundPixmap);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(540,960);

    toolbar = new QGraphicsPixmapItem();
    toolbar->setPixmap(QPixmap("./dataset/images/toolbar.png"));
    toolbar->setPos(0,-40);
    toolbar->setZValue(6);
    scene->addItem(toolbar);
 
    // create the player
    player = new Player();
    player->setPos(200,860); 
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
 
    // add the player to the scene
    scene->addItem(player);
 
    Platform* p1 = new Platform(0);
    platform.push_back(p1);
    p1 -> setPos(200,880);
    scene -> addItem(p1);
    Platform* p2 = new Platform(0);
    platform.push_back(p2);
    p2 -> setPos(rand() % 420 + 40,700);
    scene -> addItem(p2);
    Platform* p3 = new Platform(1);
    platform.push_back(p3);
    p3 -> setPos(rand() % 420 + 40,580);
    scene -> addItem(p3);
    Platform* p4 = new Platform(0);
    platform.push_back(p4);
    p4 -> setPos(rand() % 420 + 40,450);
    scene -> addItem(p4);
    Platform* p5 = new Platform(0);
    platform.push_back(p5);
    p5 -> setPos(rand() % 420 + 40,320);
    scene -> addItem(p5);
    Platform* p6 = new Platform(0);
    platform.push_back(p6);
    p6 -> setPos(rand() % 420 + 40,210);
    scene -> addItem(p6);
    Platform* p7 = new Platform(1);
    platform.push_back(p7);
    p7 -> setPos(rand() % 420 + 40,100);
    scene -> addItem(p7);
    Platform* p8 = new Platform(0);
    platform.push_back(p8);
    p8 -> setPos(rand() % 420 + 40,-20);
    scene -> addItem(p8);
 
    score = new Score();
    scene -> addItem(score);
    score -> setZValue(7);

    for (int i = 0; i < 3; ++i) 
    {
        hearts[i] = new QGraphicsPixmapItem(QPixmap("./dataset/images/hp.png"));
        QPixmap newPixmap = hearts[i]->pixmap().scaled(40, 40);
        hearts[i]->setPixmap(newPixmap);
        hearts[i]->setPos(490 - i * 50, 15);
        scene->addItem(hearts[i]);
        hearts[i]->setZValue(8);
    }
}

void Game::movePlatforms(double Y)
{
    if(player->touchHat)
        lastpy += 40;
    else if(player->touchJet)
        lastpy += 80;
    else
        lastpy += 5;
    for (std::size_t i = 0; i < platform.size(); i++)
    {
        platform[i]->setY(platform[i]->pos().y() - Y);
        if (platform[i]->pos().y() > 960)
        {
            delete platform[i];
            platform.erase(platform.begin() + i);
            createPlatform();
            i--;
        }
    }
    for (std::size_t i = 0; i < item.size(); i++)
    {
        item[i]->setY(item[i]->pos().y() - Y);
    }
    for (std::size_t i = 0; i < monster.size(); i++)
    {
        monster[i]->setY(monster[i]->pos().y() - Y);
    }
}

void Game::createPlatform()
{
    int random_numberx = rand() % 421;
    int random_numbery = rand() % 151 + 60;
    int random_chance = rand() % 100 + 1;
    int platformType = 0;
    int itemType = 0;
    int monsterType = 0;
    static int platformCount = 0;
    static int itemPlatformCount = 0;
    bool hasItem = false;
    bool hasMonster = false;

    if (score->getScore() - lastSpecialPlatformScore > 1000 && score->getScore() < 6000 && random_chance > 90)
    {
        platformType = 1;
        lastSpecialPlatformScore = score->getScore();
    }
    else if (score->getScore() - lastSpecialPlatformScore > 3000 && score->getScore() >= 6000 && score->getScore() < 9000 && random_chance > 90)
    {
        platformType = 2;
        lastSpecialPlatformScore = score->getScore();
    }
    else if (score->getScore() - lastSpecialPlatformScore > 5000 && score->getScore() >= 9000 && random_chance > 90)
    {
        platformType = 3;
        lastSpecialPlatformScore = score->getScore();
    }
    else if(random_chance <= 90)
    {
        platformType = 0;
    }
    else
    {
        platformType = 1;
    }
    Platform *p = new Platform(platformType);
    platform.push_back(p);
    p->setPos(random_numberx, lastpy - random_numbery);
    scene->addItem(p);
    lastpy = lastpy - random_numbery;
    
    //generate monster
    if (!hasItem) 
    {
        if (platformType == 0)
        {
            if (/*score->getScore() >= 3000 &&*/ score->getScore() < 6000) 
            {
                if (rand() % 100 < 30) 
                {
                    monsterType = 1;
                    hasMonster = true;
                }
            } 
            else if (score->getScore() >= 6000 && score->getScore() < 9000) 
            {
                if (rand() % 100 < 20) 
                {
                    monsterType = 1;
                    hasMonster = true;
                }
                else if (rand() % 100 < 10) 
                {
                    monsterType = 2;
                    hasMonster = true;
                }
            } 
            else if (score->getScore() >= 9000 && score->getScore() < 12000) 
            {
                if (rand() % 100 < 10) 
                {
                    monsterType = 1;
                    hasMonster = true;
                }
                else if (rand() % 100 < 10) 
                {
                    monsterType = 2;
                    hasMonster = true;
                }
                else if (rand() % 100 < 10)
                {
                    monsterType = 3;
                    hasMonster = true;
                }
            } 
            else if (score->getScore() >= 12000) 
            {
                if (rand() % 100 < 10) 
                {
                    monsterType = 1;
                    hasMonster = true;
                }
                else if (rand() % 100 < 10) 
                {
                    monsterType = 2;
                    hasMonster = true;
                }
                else if (rand() % 100 < 10) 
                {
                    monsterType = 3;
                    hasMonster = true;
                }
                else if (rand() % 100 < 10)
                {
                    monsterType = 4;
                    hasMonster = true;
                }
            }
            Monster * m = new Monster(monsterType);
            if (monsterType != 0)
                monster.push_back(m);
            m->setPos(p->pos().x(), p->pos().y() - 30 - 50);
            scene->addItem(m);
        }
    }

    //generate item
    if (itemPlatformCount < 2 && !hasMonster) 
    {
        if (platformType == 0)
        {
            if (platformCount >= 15) 
            {
                itemPlatformCount = 0;
                platformCount = 0;
            }

            if (/*score->getScore() >= 3000 && */score->getScore() < 6000) 
            {
                if (rand() % 100 < 30) 
                {
                    itemType = 1;
                    hasItem = true;
                }
            } 
            else if (score->getScore() >= 6000 && score->getScore() < 9000) 
            {
                if (rand() % 100 < 20) 
                {
                    itemType = 1;
                    hasItem = true;
                }
                else if (rand() % 100 < 10) 
                {
                    itemType = 2;
                    hasItem = true;
                }
            } 
            else if (score->getScore() >= 9000 && score->getScore() < 12000) 
            {
                if (rand() % 100 < 10) 
                {
                    itemType = 1;
                    hasItem = true;
                }
                else if (rand() % 100 < 10) 
                {
                    itemType = 2;
                    hasItem = true;
                }
                else if (rand() % 100 < 10) 
                {
                    itemType = 3;
                    hasItem = true;
                }
            } 
            else if (score->getScore() >= 12000) 
            {
                if (rand() % 100 < 10) 
                {
                    itemType = 1;
                    hasItem = true;
                }
                else if (rand() % 100 < 10) 
                {
                    itemType = 2;
                    hasItem = true;
                }
                else if (rand() % 100 < 10) 
                {
                    itemType = 3;
                    hasItem = true;
                }
                else if (rand() % 100 < 10) 
                {
                    itemType = 4;
                    hasItem = true;
                }
            }
        }
        if (hasItem)
        {
            itemPlatformCount++;
        }
        Item * i = new Item(itemType);
        if (itemType != 0)
            item.push_back(i);
        i->setPos(p->pos().x() + 40, p->pos().y() - 30);
        scene->addItem(i);
    }
    platformCount++;
}

void Game::endGame(int finalscore)
{
    if(scene){
        scene -> removeItem(playButton);
        scene -> removeItem(player);
        delete playButton;
        delete player;
        playButton = nullptr;
        player = nullptr;
        scene -> clear();
    }
    QPixmap backgroundPixmap("./dataset/images/welcome.png");
    scene->setBackgroundBrush(backgroundPixmap);

    gameover = new QGraphicsPixmapItem();
    gameover->setPixmap(QPixmap("./dataset/images/end.png"));
    gameover->setPos(130,259);
    gameover->setZValue(6);
    scene->addItem(gameover);

    QGraphicsTextItem* scoreText = new QGraphicsTextItem();  // Create a text item
    scoreText->setPlainText(QString("Score:  ") + QString::number(finalscore));  // Set the text
    scoreText->setDefaultTextColor(Qt::black);
    scoreText->setFont(QFont("Comic Sans MS",12));
    scoreText->setPos(130,480);
    scene->addItem(scoreText);  // Add the text item to the scene
    scoreText->setZValue(7);
}

void Game::decreaseHp()
{
    qDebug()<<numHearts;
    numHearts--;
    if (numHearts <= 0)
    {
        //game->endGame();
    }
    else
    {
        scene->removeItem(hearts[numHearts]);
    }     
}
