#include "GAMES/Casse_brique/CB_player.h"

CB_Player::CB_Player():PainterObject()
{

}

CB_Player::CB_Player(unsigned int x, unsigned int y)
{
    this->setPOS(x,y);

    this->setVEL(0,0);

    this->setSIZE(0,0);

    this->setHuman(false);


}

unsigned int CB_Player::getScore() const
{
    return score;
}

void CB_Player::setScore(unsigned int newScore)
{
    score = newScore;
}

bool CB_Player::getHuman() const
{
    return Human;
}

void CB_Player::setHuman(bool newHuman)
{
    Human = newHuman;
}

CB_Player::CB_Player(unsigned int x, unsigned int y, unsigned int VEL_X, unsigned int VEL_Y,unsigned int size_x,unsigned int size_y):PainterObject(x,y,VEL_X,VEL_Y,size_x,size_y)
{
    qDebug() << "Player constructor : " << x << " " << y << " " << VEL_X << " " <<VEL_Y << " " << size_x << " " << size_y ;
}
