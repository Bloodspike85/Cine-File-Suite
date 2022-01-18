#ifndef SNAKE_H
#define SNAKE_H

#include <QObject>
#include <QWidget>
#include <QPainter>

#include "GAMES/Commune/PainterObject.h"

class snake : public PainterObject
{

public:
    snake(unsigned x , unsigned int y);

    void update(QWidget *Parent);
    void Draw(QWidget *Parent);

    void AddTail(unsigned x, unsigned y)
    {
        Body.push_back(new Vector2u(x,y));
    }

    const std::string &getDirection() const;
    void setDirection(const std::string &newDirection);

    unsigned int getSpeed() const;
    void setSpeed(unsigned int newSpeed);

private :

    Vector2u *Head ;
    std::vector <Vector2u *> Body;

    std::string Direction;

    unsigned int speed;


};

#endif // SNAKE_H
