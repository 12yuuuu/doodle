#ifndef BUTTON_H
#define BUTTON_H
 
#include "game.h"
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QPixmap>
#include <QObject>
#include <QMouseEvent>
#include <QPushButton>
#include <QGraphicsPixmapItem>
 
class Button: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    // constructors
    Button(QGraphicsItem * parent = NULL);
    // public methods (events)
    void mousePressEvent(QGraphicsSceneMouseEvent *);
signals:
    void clicked();
};
 
#endif // BUTTON_H