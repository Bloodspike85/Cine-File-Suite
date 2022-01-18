#include "bubble.h"

Bubble::Bubble(QRect *Dimension)
{

    this->setPOS(Dimension->x(),Dimension->y());
    this->setSIZE(Dimension->width(),Dimension->height());

    this->setVEL(0,0);
    this->setOrigin(this->getPOS().getX() + (this->getSIZE().getX() / 2),this->getPOS().getY() + (this->getSIZE().getY() / 2));



    this->Color = new QBrush(Qt::GlobalColor(rand() % ( 19 + 1) + 1));

}

Bubble::~Bubble()
{

}


void Bubble::Draw(QWidget *Parent)
{
    this->painter = new QPainter(Parent);

    this->painter->setPen(Qt::black);
    this->painter->setBrush(*getColor());

    this->painter->drawEllipse(this->getPOS().getX(),this->getPOS().getY(),this->getSIZE().getX(),this->getSIZE().getY());
}

void Bubble::Draw(QWidget *Parent, double x, double y)
{
    this->painter = new QPainter(Parent);

    this->painter->setPen(Qt::black);
    this->painter->setBrush(*getColor());

    this->painter->drawEllipse(x,y,this->getSIZE().getX(),this->getSIZE().getY());

}

bool Bubble::CheckNearBubbleColor(Bubble *b)
{
    if(this->Color == b->getColor())
    {
        return true;
    }

    return false;
}

bool Bubble::CheckColision(Bubble *b)
{
    if(this->getOrigin().getX() > b->getPOS().getX() && this->getOrigin().getX() < (b->getPOS().getX() + b->getSIZE().getX()))
    {
        if(this->getOrigin().getY() > b->getPOS().getY() && this->getOrigin().getY() < (b->getPOS().getY() + b->getSIZE().getY()))
        {
            return true;
        }
    }

    return false;
}

bool Bubble::CheckColision(Bubble *b,double x, double y)
{
    if(x > b->getPOS().getX() && x < (b->getPOS().getX() + b->getSIZE().getX()))
    {
        if(y > b->getPOS().getY() && y < (b->getPOS().getY() + b->getSIZE().getY()))
        {
            return true;
        }
    }

    return false;
}

const Vector2u &Bubble::getOrigin() const
{
    return Origin;
}

void Bubble::setOrigin(unsigned int x,unsigned int y)
{
    Origin.setX(x);
    Origin.setY(y);
}

QBrush *Bubble::getColor() const
{
    return Color;
}

void Bubble::setColor(QBrush *newColor)
{
    Color = newColor;
}
