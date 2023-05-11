#include "score.h"
#include <QFont>
#include <qDebug>

Score::Score(QGraphicsItem *parent): QGraphicsTextItem(parent)
{
    grade = 100;
    // draw the text
    setPlainText(QString("Score: ") + QString::number(grade)); // Score: 0
    setDefaultTextColor(Qt::black);
    setFont(QFont("Comic Sans MS",12));
}
 
void Score::increase(int highest)
{
    grade = highest;
    setPlainText(QString("Score: ") + QString::number(grade));
    finalscore = grade; // Score: 1
    qDebug() << finalscore ;
}
int Score::getScore(){
    qDebug() << grade ;
    return grade;
}

int Score::getfinalscore(){
    qDebug() << "finalscore" <<finalscore;
    return finalscore;
}