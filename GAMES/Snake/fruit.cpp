#include "fruit.h"

fruit::fruit()
{

}


void fruit::update()
{

}

void fruit::Draw(QWidget *Parent)
{
    this->painter = new QPainter(Parent);

    this->painter->setPen(Qt::black);
    this->painter->setBrush(QBrush(Qt::darkYellow));

    this->painter->drawEllipse(this->getPOS().getX(),this->getPOS().getY(),this->getSIZE().getX(),this->getSIZE().getY());

}

void fruit::Draw(QWidget *Parent, double x, double y)
{

    this->setPOS(x,y);

    this->painter = new QPainter(Parent);

    this->painter->setPen(Qt::black);
    this->painter->setBrush(QBrush(Qt::darkYellow));

    this->painter->drawEllipse(this->getPOS().getX(),this->getPOS().getY(),this->getSIZE().getX(),this->getSIZE().getY());



}
