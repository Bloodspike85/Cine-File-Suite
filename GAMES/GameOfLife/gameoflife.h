#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H

#include <QObject>
#include <QWidget>

#include <QPainter>
#include <QTimer>

#define GOL_NBR_DE_COLONNE 250
#define GOL_NBR_DE_LIGNE 250

enum{DEAD,ALIVE};

class GameOfLife : public QWidget
{

    Q_OBJECT

public:

    GameOfLife();

    void paintEvent(QPaintEvent *Event);

    int checkneighboor(unsigned int Array[][GOL_NBR_DE_COLONNE],unsigned int x, unsigned int y);

    unsigned int getBloc_size_X() const;
    void setBloc_size_X(unsigned int newBloc_size);

    unsigned int getBloc_size_Y() const;
    void setBloc_size_Y(unsigned int newBloc_size_Y);

public slots:

    void Tick();

private :

    QTimer Delta_time;

    unsigned int Map[GOL_NBR_DE_LIGNE][GOL_NBR_DE_COLONNE];

    unsigned int bloc_size_X;
    unsigned int bloc_size_Y;
};

#endif // GAMEOFLIFE_H
