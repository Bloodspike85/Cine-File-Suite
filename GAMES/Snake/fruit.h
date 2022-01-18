#ifndef FRUIT_H
#define FRUIT_H

#include "GAMES/Commune/PainterObject.h"
#include "GAMES/Commune/Vector.h"

#include <QPainter>
#include <QWidget>

class fruit : public PainterObject
{
public:
    fruit();

    void update();

    void Draw(QWidget *Parent);
    void Draw(QWidget *Parent,double x,double y);

private :


};

#endif // FRUIT_H
