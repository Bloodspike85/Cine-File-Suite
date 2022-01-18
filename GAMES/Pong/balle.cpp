#include "GAMES/Pong/balle.h"

Balle::Balle()
{

}

Balle::Balle(unsigned int x, unsigned int y, unsigned int VEL_X, unsigned int VEL_Y,unsigned int size_x,unsigned int size_y):PainterObject(x,y,VEL_X,VEL_Y,size_x,size_y)
{

}

bool Balle::getLaunch() const
{
    return Launch;
}

void Balle::setLaunch(bool newLaunch)
{
    Launch = newLaunch;
}
