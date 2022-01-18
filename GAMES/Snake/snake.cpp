#include "snake.h"

snake::snake(unsigned x , unsigned int y)
{
    this->Head = new Vector2u(x,y);

    this->setSIZE(10,10);

    this->setDirection("Aucune");
    this->setSpeed(this->getSIZE().getX() / 3);
}

void snake::update(QWidget *Parent)
{
    if(Head->getX() < 1 )
    {
        Head->setX(Parent->width() - this->getSIZE().getX());
        Head->setY(Head->getY());

    }
    else if(Head->getX() > Parent->width() )
    {
        Head->setX(2);
        Head->setY(Head->getY());

    }
    else if(Head->getY() < 1 )
    {
        Head->setY(Parent->height() - this->getSIZE().getY());
        Head->setX(Head->getX());

    }
    else  if(Head->getY() > Parent->height() )
    {
        Head->setX(Head->getX());
        Head->setY(2);

    }
    else
    {
        if(this->getDirection() == "Haut")
            {
                Head->setX(this->getPOS().getX());
                Head->setY(this->getPOS().getY() - this->getSpeed()) ;
            }
            else if(this->getDirection() == "Bas")
            {
                Head->setX(this->getPOS().getX());
                Head->setY(this->getPOS().getY() + this->getSpeed()) ;
            }
            else if(this->getDirection() == "Gauche")
            {
                Head->setX(this->getPOS().getX() - this->getSpeed() );
                Head->setY(this->getPOS().getY());
            }
            else if(this->getDirection() == "Droite")
            {
                Head->setX(this->getPOS().getX() + this->getSpeed() );
                Head->setY(this->getPOS().getY());
            }
    }

    this->setPOS(Head->getX(),Head->getY());

}

void snake::Draw(QWidget *Parent)
{
    //Dessine la tête

    this->painter = new QPainter(Parent);

    this->painter->setBrush(QBrush(Qt::white));
    this->painter->drawRect(Head->getX(),Head->getY(),this->getSIZE().getX(),this->getSIZE().getY());


    //Puis la queue

    if(!this->Body.empty())
    {
        for(unsigned int i = 0; i < Body.size() ; i++)
        {
            this->painter->drawRect(Body[i]->getX(),Body[i]->getY(),this->getSIZE().getX(),this->getSIZE().getY());
        }
    }
}

const std::string &snake::getDirection() const
{
    return Direction;
}

void snake::setDirection(const std::string &newDirection)
{
    Direction = newDirection;
}

unsigned int snake::getSpeed() const
{
    return speed;
}

void snake::setSpeed(unsigned int newSpeed)
{
    speed = newSpeed;
}
