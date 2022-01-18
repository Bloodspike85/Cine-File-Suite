#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>

#include "GAMES/Pong/pong.h"
#include "GAMES/Casse_brique/casse_brique.h"
#include "GAMES/Boule/bimbamboule.h"
#include "GAMES/GameOfLife/gameoflife.h"
#include "GAMES/Snake/snake_game.h"

#include <QLayout>

enum Nom_Jeu{Jeu_Pong,Jeu_Casse_Brique,Jeu_Boule,Jeu_GameOfLife,Jeu_Snake,Jeu_Tetriste,Jeu_TouchePasLaBombe};

class Game :public QWidget
{
    Q_OBJECT

public:
    Game();
    ~Game();

    QWidget *Creation_IHM();

   public slots:

    void Handle_Bouton();

private :

    QWidget *Jeu_Selectionne = nullptr;

        QVBoxLayout *Jeu_Layout = nullptr;
       QPushButton *Liste_Jeu[Jeu_TouchePasLaBombe];
};

#endif // GAME_H
