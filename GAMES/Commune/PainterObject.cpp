#include "PainterObject.h"

PainterObject::PainterObject()
{
    this->POS.setX(0);
    this->POS.setY(0);
    this->VEL.setX(0);
    this->VEL.setY(0);

    this->setAngle(0);
}

PainterObject::PainterObject(unsigned int x, unsigned int y, unsigned int VEL_X, unsigned int VEL_Y,unsigned int size_x,unsigned int size_y)
{
    this->POS.setX(x);
    this->POS.setY(y);
    this->VEL.setX(VEL_X);
    this->VEL.setY( VEL_Y);
    this->SIZE.setX(size_x);
    this->SIZE.setY(size_y);

    this->setAngle(0);
}

bool PainterObject::CheckCollision(PainterObject *painterObject,int ComeFrom)
{

    switch (ComeFrom)
    {
        case LEFT :

            if((painterObject->getPOS().getX() + painterObject->getSIZE().getX()) >= this->getPOS().getX() && (painterObject->getPOS().getX() + painterObject->getSIZE().getX()) <= (this->getPOS().getX() + this->getSIZE().getX()))
            {

                if(painterObject->getPOS().getY() >= this->getPOS().getY() && painterObject->getPOS().getY() <= (this->getPOS().getY() + this->getSIZE().getY()))
                {

                    return true;
                }
                else
                {
                    qDebug() << "NON";
                    return false;
                }
            }
            else
            {
                qDebug() << "NON";
               return false;
            }

        break;

        case UP :

            if(painterObject->getPOS().getX() >= this->getPOS().getX() && painterObject->getPOS().getX() <= (this->getPOS().getX() + this->getSIZE().getX()))
            {
                if((painterObject->getPOS().getY() + painterObject->getSIZE().getY()) >= this->getPOS().getY() && (painterObject->getPOS().getY() + painterObject->getSIZE().getY()) <= (this->getPOS().getY() + this->getSIZE().getY()))
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
               return false;
            }

        break;

        case RIGHT :

            if(painterObject->getPOS().getX() >= this->getPOS().getX() && painterObject->getPOS().getX() <= (this->getPOS().getX() + this->getSIZE().getX()))
            {
                if(painterObject->getPOS().getY() >= this->getPOS().getY() && painterObject->getPOS().getY() <= (this->getPOS().getY() + this->getSIZE().getY()))
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
               return false;
            }

        break;

        case DOWN :

            if(painterObject->getPOS().getX() >= this->getPOS().getX() && painterObject->getPOS().getX() <= (this->getPOS().getX() + this->getSIZE().getX()))
            {
                if(painterObject->getPOS().getY() >= this->getPOS().getY() && painterObject->getPOS().getY() <= (this->getPOS().getY() + this->getSIZE().getY()))
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
               return false;
            }

        break;

    default:
        std::cout << "Une erreur c'est produite : le comeFrom numero " << ComeFrom << " n'existe pas " << std::endl;
        return false;

        break;

    }


}

const Vector2u &PainterObject::getPOS() const
{
    return POS;
}

void PainterObject::setPOS(const unsigned int New_x, const unsigned int New_y)
{
    POS.setX(New_x);
    POS.setY(New_y);
}

const Vector2u &PainterObject::getVEL() const
{
    return VEL;
}

void PainterObject::setVEL(const unsigned int New_x, const unsigned int New_y)
{
    VEL.setX(New_x);
    VEL.setY(New_y);
}

const Vector2u &PainterObject::getSIZE() const
{
    return SIZE;
}

void PainterObject::setSIZE(const unsigned int New_x, const unsigned int New_y)
{
    SIZE.setX(New_x);
    SIZE.setY(New_y);
}

double PainterObject::getAngle() const
{
    return angle;
}

void PainterObject::setAngle(double newAngle)
{
    angle = newAngle;
}
