#include "snake_game.h"

Snake_Game::Snake_Game() : QWidget()
{
    this->setWindowTitle("Cine_File_Suite : SSSSNAKE");

    this->setGeometry(50,50,800,600);

    Player = new snake(this->width() / 2 , this->height() / 2);
    Fruit = new fruit();

    connect(&Delta_time,SIGNAL(timeout()),this,SLOT(Tick()));

    Delta_time.start(25);

}

void Snake_Game::Game_update()
{
    Player->update(this);
    repaint();
}

void Snake_Game::Game_draw()
{
    Player->Draw(this);
    Fruit->Draw(this);
}

void Snake_Game::paintEvent(QPaintEvent *Event)
{
    QPainter *Border = new QPainter(this);
    Border->drawRoundedRect(5,5,this->width() - 10,this->height() - 10,3,3);


    Game_draw();
}

void Snake_Game::keyPressEvent(QKeyEvent *Event)
{
    std::cout << "push le bouton " << std::endl;
    if(Event->key() == Qt::Key_Left)
    {
        Player->setDirection("Gauche");
    }
    else if(Event->key() == Qt::Key_Right)
    {
        Player->setDirection("Droite");
    }
    else if(Event->key() == Qt::Key_Up)
    {
        Player->setDirection("Haut");
    }
    else if(Event->key() == Qt::Key_Down)
    {
        Player->setDirection("Bas");
    }
}


void Snake_Game::Tick()
{
    Game_update();

}
