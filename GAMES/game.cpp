#include "game.h"

Game::Game():QWidget()
{
    Creation_IHM();

    this->setLayout(Jeu_Layout);

}

Game::~Game()
{



    if(Jeu_Layout != nullptr)
    {
        delete Jeu_Layout;
    }
    if(Jeu_Selectionne != nullptr)
    {
        delete Jeu_Selectionne;
    }
}

QWidget *Game::Creation_IHM()
{
    QWidget *Conteneur = new QWidget(this);

    Jeu_Layout = new QVBoxLayout();

    Jeu_Layout->addWidget(new QLabel("Veuillez choisir votre jeu"));

    Liste_Jeu[Jeu_Pong] = new QPushButton("Ding_PONG");
    Liste_Jeu[Jeu_Casse_Brique] = new QPushButton("ca casse pas une brique");
    Liste_Jeu[Jeu_Boule] = new QPushButton("BIM BAM BOULE");
    Liste_Jeu[Jeu_GameOfLife] = new QPushButton("Le jeu de la vie");
    Liste_Jeu[Jeu_Snake] = new QPushButton("SSSSSSSNAKE");

    Jeu_Layout->addWidget(Liste_Jeu[Jeu_Pong]);
    Jeu_Layout->addWidget(Liste_Jeu[Jeu_Casse_Brique]);
    Jeu_Layout->addWidget(Liste_Jeu[Jeu_Boule]);
    Jeu_Layout->addWidget(Liste_Jeu[Jeu_GameOfLife]);
    Jeu_Layout->addWidget(Liste_Jeu[Jeu_Snake]);




    connect(Liste_Jeu[Jeu_Pong],SIGNAL(clicked()),this,SLOT(Handle_Bouton()));
    connect(Liste_Jeu[Jeu_Casse_Brique],SIGNAL(clicked()),this,SLOT(Handle_Bouton()));
    connect(Liste_Jeu[Jeu_Boule],SIGNAL(clicked()),this,SLOT(Handle_Bouton()));
    connect(Liste_Jeu[Jeu_GameOfLife],SIGNAL(clicked()),this,SLOT(Handle_Bouton()));
    connect(Liste_Jeu[Jeu_Snake],SIGNAL(clicked()),this,SLOT(Handle_Bouton()));

    Conteneur->setLayout(Jeu_Layout);

    return  Conteneur;
}

void Game::Handle_Bouton()
{
    if(QObject::sender() == Liste_Jeu[Jeu_Pong])
    {
        if(Jeu_Selectionne != nullptr)
        {
            delete Jeu_Selectionne;
        }
        Jeu_Selectionne = new pong();
        Jeu_Selectionne->show();
    }

    if(QObject::sender() == Liste_Jeu[Jeu_Casse_Brique])
    {
        if(Jeu_Selectionne != nullptr)
        {
            delete Jeu_Selectionne;
        }
        Jeu_Selectionne = new Casse_brique();
        Jeu_Selectionne->show();
    }

    if(QObject::sender() == Liste_Jeu[Jeu_Boule])
    {
        if(Jeu_Selectionne != nullptr)
        {
            delete Jeu_Selectionne;
        }
        Jeu_Selectionne = new BimBamBoule();
        Jeu_Selectionne->show();
    }

    if(QObject::sender() == Liste_Jeu[Jeu_GameOfLife])
    {
        if(Jeu_Selectionne != nullptr)
        {
            delete Jeu_Selectionne;
        }
        Jeu_Selectionne = new GameOfLife();
        Jeu_Selectionne->show();
    }

    if(QObject::sender() == Liste_Jeu[Jeu_Snake])
    {
        if(Jeu_Selectionne != nullptr)
        {
            delete Jeu_Selectionne;
        }
        Jeu_Selectionne = new Snake_Game();
        Jeu_Selectionne->show();
    }
}
