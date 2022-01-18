#ifndef BALLE_H
#define BALLE_H

#include "GAMES/Commune/PainterObject.h"


class Balle : public PainterObject
{
public:
    Balle();
    Balle(unsigned int x, unsigned int y, unsigned int VEL_X, unsigned int VEL_Y,unsigned int size_x,unsigned int size_y);

    bool getLaunch() const;
    void setLaunch(bool newLaunch);

private:

    bool Launch;
};

#endif // BALLE_H
