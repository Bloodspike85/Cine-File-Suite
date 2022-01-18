#ifndef PLAYER_BUBBLE_H
#define PLAYER_BUBBLE_H

#include "GAMES/Boule/bubble.h"

class Player_bubble : public Bubble
{
public:

    Player_bubble(QRect *Dimension);

    bool getLaunch() const;
    void setLaunch(bool newLaunch);


    const Vector2d &getDirection() const;
    void setDirection(double x, double y);



    const Vector2d &getPosition() const;
    void setPosition(double x, double y);

    const Vector2d &getVelocite() const;
    void setVelocite(double x, double y);

    const Vector2d &getSpeed() const;
    void setSpeed(double x, double y);

private:

    bool launch;

    Vector2d Velocite;
    Vector2d Direction;
    Vector2d Position;
    Vector2d Speed;





};

#endif // PLAYER_BUBBLE_H
