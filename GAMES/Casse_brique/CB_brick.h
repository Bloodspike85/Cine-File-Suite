#ifndef CB_BRICK_H
#define CB_BRICK_H

#include "GAMES/Commune/PainterObject.h"

class CB_Brick : public PainterObject
{
public:
    CB_Brick();
    CB_Brick(unsigned int x, unsigned int y);
    CB_Brick(unsigned int x, unsigned int y, unsigned int VEL_X, unsigned int VEL_Y, unsigned int size_x, unsigned int size_y);
    void Update_bricks();

    unsigned int getVie();
    void setVie(unsigned int newVie);

    bool getAlive();
    void setAlive(bool newAlive);

    QBrush *getColor();
    void setColor(QBrush *newColor);

private :

    unsigned int Vie;
    bool Alive;

    QBrush *Color;
};

#endif // CB_BRICK_H
