#ifndef PainterObject_H
#define PainterObject_H

#include <iostream>

#include "GAMES/Commune/Vector.h"

#include <QDebug>
#include <QPainter>
#include <QPaintEvent>

enum ComeFrom{LEFT,UP,RIGHT,DOWN};



class PainterObject
{
public:

    PainterObject();
    PainterObject(unsigned int x, unsigned int y, unsigned int VEL_X, unsigned int VEL_Y,unsigned int size_x,unsigned int size_y);

    void paintEvent(QPaintEvent *Event);

    bool CheckCollision(PainterObject *painterObject,int ComeFrom);

    QPainter *painter;


    const Vector2u &getPOS() const;
    void setPOS(const unsigned int New_x, const unsigned int New_y);

    const Vector2u &getVEL() const;
    void setVEL(const unsigned int New_x, const unsigned int New_y);

    const Vector2u &getSIZE() const;
    void setSIZE(const unsigned int New_x, const unsigned int New_y);

    double getAngle() const;
    void setAngle(double newAngle);


private:

    Vector2u POS;

    Vector2u VEL;

    Vector2u SIZE;

    double angle;









};

#endif // PainterObject_H
