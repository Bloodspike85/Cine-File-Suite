#ifndef PLAYER_H
#define PLAYER_H

#include "GAMES/Commune/PainterObject.h"

class Player : public PainterObject
{
public:
    Player();
    Player(unsigned int x, unsigned int y);
    Player(unsigned int x, unsigned int y, unsigned int VEL_X, unsigned int VEL_Y,unsigned int size_x,unsigned int size_y);

    unsigned int getScore() const;
    void setScore(unsigned int newScore);

    bool getHuman() const;
    void setHuman(bool newHuman);

private :

    unsigned int score;
    bool Human;
};

#endif // PLAYER_H
