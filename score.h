#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsTextItem>

class Score: public QGraphicsTextItem{
public:
    Score(QGraphicsItem * parent=0);
    void increase(int);
    int getScore();
    int getfinalscore();
    int grade = 0;
    int finalscore = 0;
};

#endif // SCORE_H