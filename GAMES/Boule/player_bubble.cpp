#include "player_bubble.h"

Player_bubble::Player_bubble(QRect *Dimension):Bubble(Dimension)
{
    launch = false;
    Position.setX(Dimension->x());
    Position.setY(Dimension->y());

    this->setDirection(0,0);
    this->setVelocite(0,0);
    this->setSpeed(0.05,0.05);
}

bool Player_bubble::getLaunch() const
{
    return launch;
}

void Player_bubble::setLaunch(bool newLaunch)
{
    launch = newLaunch;
}



const Vector2d &Player_bubble::getDirection() const
{
    return Direction;
}

void Player_bubble::setDirection(double x, double y)
{
    this->Direction.setX(x);
    this->Direction.setY(y);
}

const Vector2d &Player_bubble::getPosition() const
{
    return Position;
}

void Player_bubble::setPosition(double x, double y)
{
    Position.setX(x);
    Position.setY(y);
}

const Vector2d &Player_bubble::getVelocite() const
{
    return Velocite;
}

void Player_bubble::setVelocite(double x, double y)
{
    Velocite.setX(x);
    Velocite.setY(y);
}

const Vector2d &Player_bubble::getSpeed() const
{
    return Speed;
}

void Player_bubble::setSpeed(double x, double y)
{
    Speed.setX(x);
    Speed.setY(y);
}
