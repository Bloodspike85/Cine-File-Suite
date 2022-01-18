#include "GAMES/Casse_brique/CB_brick.h"

#include <ctime>

CB_Brick::CB_Brick():PainterObject()
{

}

CB_Brick::CB_Brick(unsigned int x, unsigned int y):PainterObject()
{


    this->setPOS(x,y);

    this->setVEL(0,0);

    this->setSIZE(0,0);

    this->setAlive(true);
    this->setVie(rand() % 3 + 1);

    std::cout << this->getVie() << std::endl;
}

CB_Brick::CB_Brick(unsigned int x, unsigned int y, unsigned int VEL_X, unsigned int VEL_Y,unsigned int size_x,unsigned int size_y):PainterObject(x,y,VEL_X,VEL_Y,size_x,size_y)
{
    qDebug() << "Player constructor : " << x << " " << y << " " << VEL_X << " " <<VEL_Y << " " << size_x << " " << size_y ;
}

void CB_Brick::Update_bricks()
{

    if(this->getAlive())
    {
        if(Vie == 1)
        {
            Color = new QBrush(Qt::red);
        }
        else if(Vie == 2)
        {
            Color = new QBrush(Qt::green);
        }
        else if(Vie == 3)
        {
            Color = new QBrush(Qt::blue);
        }
    }

    if(this->painter != nullptr)
    {
        this->painter->setBrush(*Color);
    }

}


unsigned int CB_Brick::getVie()
{
    return Vie;
}

void CB_Brick::setVie(unsigned int newVie)
{
    Vie = newVie;
}


bool CB_Brick::getAlive()
{
    if(this->getVie() > 0)
    {
        Alive = true;
    }
    else
    {
        Alive = false;
    }
    return Alive;
}

void CB_Brick::setAlive(bool newAlive)
{
    Alive = newAlive;
}

QBrush *CB_Brick::getColor()
{
    return Color;
}

void CB_Brick::setColor(QBrush *newColor)
{
    Color = newColor;
}
