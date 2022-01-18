#ifndef CASSE_BRIQUE_H
#define CASSE_BRIQUE_H


#include <QWidget>
#include <QLayout>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <iostream>
#include <ctime>

#include <main.h>


#include <GAMES/Casse_brique/CB_brick.h>

#include <GAMES/Casse_brique/CB_player.h>

#include <GAMES/Casse_brique/CB_balle.h>


#include <QColor>
#include <QTimer>

#include <QPaintEvent>



class Casse_brique : public QWidget
{

    Q_OBJECT

public:
    Casse_brique();

    void Check_Collision();

    void init();
    void Reset();

    void paintEvent(QPaintEvent *Event);


    void keyPressEvent(QKeyEvent *Event);

public slots:

    void Tick();




private :

    QTimer Delta_time;

    const int B_Lower_angle = -30;
    const int B_upper_angle = 30;


    QWidget *Main_window;
    unsigned int score;

    CB_Player *Raquette;

    static const unsigned int nbr_de_ligne = 5 ;
    static const unsigned int nbr_de_colonne = 10 ;
    CB_Brick *Bricks[nbr_de_colonne][nbr_de_ligne];
    CB_Balle *Balle;

    QPainter *Score_text;

    bool Game_state;







};

#endif // CASSE_BRIQUE_H
