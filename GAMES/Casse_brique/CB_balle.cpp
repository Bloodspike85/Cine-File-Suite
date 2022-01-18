#include "GAMES/Casse_brique/CB_balle.h"

CB_Balle::CB_Balle()
{

}

CB_Balle::CB_Balle(unsigned int x, unsigned int y, unsigned int VEL_X, unsigned int VEL_Y,unsigned int size_x,unsigned int size_y):PainterObject(x,y,VEL_X,VEL_Y,size_x,size_y)
{

}


bool CB_Balle::getLaunch() const
{
    return Launch;
}

void CB_Balle::setLaunch(bool newLaunch)
{
    Launch = newLaunch;
}

