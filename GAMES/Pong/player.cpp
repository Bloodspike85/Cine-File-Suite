#include "GAMES/Pong/player.h"

Player::Player():PainterObject()
{

}

Player::Player(unsigned int x, unsigned int y)
{
    this->setPOS(x,y);

    this->setVEL(0,0);
    this->setScore(0);
    this->setHuman(false);
    this->setSIZE(0,0);
}

unsigned int Player::getScore() const
{
    return score;
}

void Player::setScore(unsigned int newScore)
{
    score = newScore;
}

bool Player::getHuman() const
{
    return Human;
}

void Player::setHuman(bool newHuman)
{
    Human = newHuman;
}

Player::Player(unsigned int x, unsigned int y, unsigned int VEL_X, unsigned int VEL_Y,unsigned int size_x,unsigned int size_y):PainterObject(x,y,VEL_X,VEL_Y,size_x,size_y)
{
    qDebug() << "Player constructor : " << x << " " << y << " " << VEL_X << " " <<VEL_Y << " " << size_x << " " << size_y ;
}
