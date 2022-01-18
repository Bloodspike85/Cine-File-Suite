#ifndef CB_BALLE_H
#define CB_BALLE_H

#include "GAMES/Commune/PainterObject.h"

class CB_Balle : public PainterObject
{
public:
    CB_Balle();

    CB_Balle(unsigned int x, unsigned int y);
    CB_Balle(unsigned int x, unsigned int y, unsigned int VEL_X, unsigned int VEL_Y, unsigned int size_x, unsigned int size_y);



    bool getLaunch() const;
    void setLaunch(bool newLaunch);

private:

    bool Launch;

};

#endif // CB_BALLE_H
