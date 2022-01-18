#include "gameoflife.h"

GameOfLife::GameOfLife():QWidget()
{
    this->setWindowTitle("Cine_File_Suite : Le jeu de la vie");


    srand(time(NULL));

    for(int i = 0 ; i < GOL_NBR_DE_COLONNE ; i++)
    {
        for(int j = 0 ; j < GOL_NBR_DE_LIGNE ; j++)
        {
            Map[i][j] = rand() % ( 1 + 1) + 0;
        }
    }

    setBloc_size_X(this->width() / GOL_NBR_DE_COLONNE);
    setBloc_size_Y(this->height() / GOL_NBR_DE_LIGNE);

    connect(&Delta_time,SIGNAL(timeout()),this,SLOT(Tick()));

    Delta_time.start(100);

}

void GameOfLife::paintEvent(QPaintEvent *Event)
{
    QPainter *Map_painter = new QPainter(this);

    for(int i = 0 ; i < GOL_NBR_DE_COLONNE ; i++)
    {
        for(int j = 0 ; j < GOL_NBR_DE_LIGNE ; j++)
        {
            if(Map[i][j] == ALIVE)
            {
                Map_painter->fillRect(i * getBloc_size_X() , j * getBloc_size_Y() , getBloc_size_X() , getBloc_size_Y() ,QBrush(Qt::white));

            }
            else if(Map[i][j] == DEAD)
            {
                Map_painter->fillRect(i * getBloc_size_X() , j * getBloc_size_Y() , getBloc_size_X() , getBloc_size_Y() ,QBrush(Qt::black));

            }


        }
    }


}

int GameOfLife::checkneighboor(unsigned int Array[][GOL_NBR_DE_COLONNE],unsigned int x, unsigned int y)
{

    unsigned int somme = 0;


        for(int i = -1 ; i < 2 ;i++)
        {
            for(int j = -1 ; j < 2 ;j++)
            {
                int cols = (x + i + GOL_NBR_DE_COLONNE ) % GOL_NBR_DE_COLONNE;
                int rows = (y + j + GOL_NBR_DE_LIGNE) % GOL_NBR_DE_LIGNE ;

                somme += Array[cols][rows];
            }
        }

        return somme;


}

void GameOfLife::Tick()
{

    unsigned int Next_Frame[GOL_NBR_DE_LIGNE][GOL_NBR_DE_COLONNE] ;


    for(int i = 0 ; i < GOL_NBR_DE_COLONNE ; i++)
    {
        for(int j = 0 ; j < GOL_NBR_DE_LIGNE ; j++)
        {
            int state = Map[i][j];

            int somme = this->checkneighboor(Map,i,j);

            if(state == DEAD && somme == 3)
            {
                 Next_Frame[i][j] = ALIVE;
            }
            else if(state == ALIVE && (somme < 2 || somme > 3))
            {
                Next_Frame[i][j] = DEAD;
            }
            else
            {
                Next_Frame[i][j] = state ;
            }
        }
    }

    for(int i = 0 ; i < GOL_NBR_DE_COLONNE ; i++)
    {
        for(int j = 0 ; j < GOL_NBR_DE_LIGNE ; j++)
        {
            Map[i][j] = Next_Frame[i][j];
        }

    }

    repaint();

}

unsigned int GameOfLife::getBloc_size_Y() const
{
    return bloc_size_Y;
}

void GameOfLife::setBloc_size_Y(unsigned int newBloc_size_Y)
{
    bloc_size_Y = newBloc_size_Y;
}

unsigned int GameOfLife::getBloc_size_X() const
{
    return bloc_size_X;
}

void GameOfLife::setBloc_size_X(unsigned int newBloc_size)
{
    bloc_size_X = newBloc_size;
}
