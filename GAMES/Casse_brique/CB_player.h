#ifndef CB_PLAYER_H
#define CB_PLAYER_H

#include "GAMES/Commune/PainterObject.h"

class CB_Player : public PainterObject
{
public:
    CB_Player();
    CB_Player(unsigned int x, unsigned int y);
    CB_Player(unsigned int x, unsigned int y, unsigned int VEL_X, unsigned int VEL_Y,unsigned int size_x,unsigned int size_y);

    unsigned int getScore() const;
    void setScore(unsigned int newScore);

    bool getHuman() const;
    void setHuman(bool newHuman);

private :

    unsigned int score;
    bool Human;
};

#endif // CB_PLAYER_H
