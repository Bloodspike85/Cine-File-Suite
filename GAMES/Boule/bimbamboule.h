#ifndef BIMBAMBOULE_H
#define BIMBAMBOULE_H

#include <QTimer>
#include <math.h>
#include "QWidget"
#include "GAMES/Boule/bubble.h"
#include "GAMES/Boule/player_bubble.h"


#define NBR_DE_COLONNE 30


class BimBamBoule : public QWidget
{
    Q_OBJECT

public:
    BimBamBoule();

    void Game_update();
    void Game_Draw();

    void Add_One_Row();


    void paintEvent(QPaintEvent *Event);


    void keyPressEvent(QKeyEvent *Event);

    unsigned int getCurrentPlayer() const;
    void setCurrentPlayer(unsigned int newCurrentPlayer);

public slots:

    void Tick();

private:

    unsigned int NBR_DE_LIGNE_MAX;

    QTimer Delta_time;


    std::vector<Player_bubble *> Player_b;

    unsigned int CurrentPlayer;

    unsigned int nombre_de_ligne_start;

    bool Game_Start;

    PainterObject *Pointeur;

    std::vector<Bubble *> bubble;

    const double angle_max = 6.3;
    const double angle_min = 3.15;


};

#endif // BIMBAMBOULE_H
