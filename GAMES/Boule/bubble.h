#ifndef BUBBLE_H
#define BUBBLE_H

//Calcul angle x = x + cos(angle)
//Calcul angle y = y + (sin(angle) * -1)

#include "GAMES/Commune/PainterObject.h"
#include "GAMES/Commune/Vector.h"
#include <QWidget>

class Bubble : public PainterObject
{

public:
    Bubble(QRect *Dimension);
    ~Bubble();

    void update(float DT);

    void Draw(QWidget *Parent);
    void Draw(QWidget *Parent,double x,double y);

    bool CheckNearBubbleColor(Bubble *b);

    QBrush *getColor() const;
    void setColor(QBrush *newColor);

    bool CheckColision(Bubble *b);
    bool CheckColision(Bubble *b,double x, double y);

    const Vector2u &getOrigin() const;
    void setOrigin(unsigned int x,unsigned int y);

private :


    QBrush *Color;

    Vector2u Origin;


};

#endif // BUBBLE_H
