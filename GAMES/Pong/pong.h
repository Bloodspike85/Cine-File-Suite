#ifndef PONG_H
#define PONG_H


#include <QWidget>
#include <QLayout>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <iostream>

#include <main.h>
#include <GAMES/Pong/player.h>
#include <GAMES/Pong/balle.h>

#include <QColor>
#include <QTimer>

#include <QPaintEvent>

class pong : public QWidget
{

    Q_OBJECT

public:
    pong();

    void Check_Collision();

    void init();
	void Reset();

    void paintEvent(QPaintEvent *Event);


    void keyPressEvent(QKeyEvent *Event);

public slots:

    void Tick();




private :

    QTimer Delta_time;

    const int B_Lower_angle = -10;
    const int B_upper_angle = 10;


    QWidget *Main_window;
    unsigned int score;

    Player *Pong_Player;
    Player *Pong_IA;
    Balle *Pong_Balle;

    QPainter *Score_text;

    bool Game_state;








};

#endif // PONG_H
