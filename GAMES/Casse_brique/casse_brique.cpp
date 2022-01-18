#include "GAMES/Casse_brique/casse_brique.h"

Casse_brique::Casse_brique():QWidget()
{

    srand(time(NULL));

    this->setWindowFlags(Qt::Window
                         | Qt::WindowMinimizeButtonHint
                         | Qt::WindowMaximizeButtonHint
                         | Qt::WindowCloseButtonHint);

    this->setWindowTitle("Cine_File_Suite : Casse brique");

    qDebug() << "Windows flags OK" ;
    this->setGeometry((resolution_Ecran::Get_Resolution_Ecran().width() /4)  ,
                      (resolution_Ecran::Get_Resolution_Ecran().height() /4)  ,
                      (resolution_Ecran::Get_Resolution_Ecran().width() / 2),
                      (resolution_Ecran::Get_Resolution_Ecran().height()));

    qDebug() << "geo OK" ;
    this->setFocusPolicy(Qt::StrongFocus);
    qDebug() << "focus OK" ;

    Raquette = new CB_Player((resolution_Ecran::Get_Resolution_Ecran().width() /4) , this->height() - 50);

    Raquette->setSIZE(this->width() / 4,10);

    //Raquette->setPos_x(Raquette->getPos_x() - (Raquette->getSize_X() / 2));


    qDebug() << "Player OK" ;


            for(unsigned int i = 0 ; i < nbr_de_colonne ;i++)
            {
                for(unsigned int j = 0; j < nbr_de_ligne ; j++)
                {

                    Bricks[i][j] = new CB_Brick(5 + (i * ((this->width() - 10) / nbr_de_colonne )),5 + (j * 15));
                    Bricks[i][j]->setSIZE((this->width() / nbr_de_colonne) - 5 ,15);
                }

            }





    qDebug() << "bricks OK" ;

    Balle = new CB_Balle(200,200,10,0,25,25);

    Reset();

    qDebug() << "BALLE OK" ;







    connect(&Delta_time,SIGNAL(timeout()),this,SLOT(Tick()));

    Delta_time.start(25);













}

void Casse_brique::Reset()
{


    Balle->setVEL(5,-5);
    Balle->setLaunch(false) ;
    Balle->setSIZE(25,25);

    Balle->setPOS((Raquette->getPOS().getX() + (Raquette->getSIZE().getX() /2)) - (Balle->getSIZE().getX() / 2), Raquette->getPOS().getY() - Balle->getSIZE().getY() + 20);
}

void Casse_brique::Check_Collision()
{
    if(Balle->getLaunch())
    {

        //L'écran
        if(Balle->getPOS().getX() < 1)
        {
            Balle->setVEL(-Balle->getVEL().getX(),Balle->getVEL().getY());
        }

        if((Balle->getPOS().getX() + Balle->getSIZE().getX()) > (unsigned int)this->width())
        {
            Balle->setVEL(-Balle->getVEL().getX(),Balle->getVEL().getY());
        }

        if(Balle->getPOS().getY() < 10)
        {
            Balle->setVEL(Balle->getVEL().getX(),Balle->getVEL().getY());
        }

        if(Balle->getPOS().getY() + Balle->getSIZE().getY() > (unsigned int)this->height())
        {
            Reset();
        }


        //Player

        if(Raquette->CheckCollision(Balle,ComeFrom::UP))
        {
            Balle->setVEL(-Balle->getVEL().getX(),Balle->getVEL().getY());
        }

        //Bricks

        for(unsigned int i = 0 ; i < nbr_de_colonne ;i++)
        {
            for(unsigned int j = 0; j < nbr_de_ligne ; j++)
            {


                    if(Bricks[i][j]->getAlive())
                    {
                        if(Bricks[i][j]->CheckCollision(Balle,ComeFrom::UP))
                        {
                            Balle->setVEL(-Balle->getVEL().getX(),Balle->getVEL().getY());
                            Bricks[i][j]->setVie(Bricks[i][j]->getVie() - 1);
                        }
                        else if(Bricks[i][j]->CheckCollision(Balle,ComeFrom::RIGHT))
                        {
                            Balle->setVEL(-Balle->getVEL().getX(),Balle->getVEL().getY());
                            Bricks[i][j]->setVie(Bricks[i][j]->getVie() - 1);
                        }
                        else if(Bricks[i][j]->CheckCollision(Balle,ComeFrom::LEFT))
                        {
                            Balle->setVEL(-Balle->getVEL().getX(),Balle->getVEL().getY());
                            Bricks[i][j]->setVie(Bricks[i][j]->getVie() - 1);
                        }
                        else if(Bricks[i][j]->CheckCollision(Balle,ComeFrom::DOWN))
                        {
                            Balle->setVEL(-Balle->getVEL().getX(),Balle->getVEL().getY());
                            Bricks[i][j]->setVie(Bricks[i][j]->getVie() - 1);
                        }

                    }
            }
        }


    }
    else
    {
        Balle->setPOS((Raquette->getPOS().getX() + (Raquette->getSIZE().getX() /2)) - (Balle->getSIZE().getX() / 2),Raquette->getPOS().getY() - Balle->getSIZE().getY());

    }

}



void Casse_brique::paintEvent(QPaintEvent *Event)
{


    if(!Balle->getLaunch())
    {
        QPainter *Launch_text = new QPainter(this);
        Launch_text->drawText(10,(this->height() - 75),QString("Appuyer sur la barre espace pour lancer la balle \n et les flèches directionnelles pour déplacer la raquette"));

    }

    QPainter *Border = new QPainter(this);
    Border->drawRoundedRect(5,5,this->width() - 10,this->height() - 10,3,3);

    Raquette->painter = new QPainter(this);
    Raquette->painter->setBrush(Qt::black);
    Raquette->painter->setPen(Qt::red);
    Raquette->painter->drawRoundedRect(Raquette->getPOS().getX(),Raquette->getPOS().getY(),Raquette->getSIZE().getX(),Raquette->getSIZE().getY(),3,3);


    Balle->painter = new QPainter(this);
    Balle->painter->setBrush(Qt::black);
    Balle->painter->setPen(Qt::red);
    Balle->painter->drawEllipse(Balle->getPOS().getX(),Balle->getPOS().getY(),Balle->getSIZE().getX(),Balle->getSIZE().getY());


    for(unsigned int i = 0 ; i < nbr_de_colonne ;i++)
    {
        for(unsigned int j = 0; j < nbr_de_ligne ; j++)
        {

                if(Bricks[i][j]->getAlive())
                {
                    Bricks[i][j]->painter = new QPainter(this);

                    Bricks[i][j]->Update_bricks();
                    Bricks[i][j]->painter->setPen(Qt::black);
                    Bricks[i][j]->painter->drawRoundedRect(Bricks[i][j]->getPOS().getX(),Bricks[i][j]->getPOS().getY(),Bricks[i][j]->getSIZE().getX(),Bricks[i][j]->getSIZE().getY(),3,3);

                }

        }
    }




}

void Casse_brique::keyPressEvent(QKeyEvent *Event)
{
    std::cout << "On appuie sur une touche : " << std::endl;

    if(!Balle->getLaunch() && Event->key() == Qt::Key_Space)
    {
        std::cout << "START" << std::endl;
        Balle->setLaunch(true);
        srand(time(NULL));
        Balle->setVEL((rand() % ( - B_Lower_angle + 1) + B_Lower_angle), Balle->getVEL().getY() - 30);

        update();

    }
    if(Event->key() == Qt::Key_Left)
    {
        if(Raquette->getPOS().getX() > 10)
        {
            Raquette->setPOS(Raquette->getPOS().getX() - 10,Raquette->getPOS().getY());
        }
        else
        {
            Raquette->setPOS(10,Raquette->getPOS().getY());
        }

    }
    else if(Event->key() == Qt::Key_Right)
    {
        if((Raquette->getPOS().getX() + Raquette->getSIZE().getX()) < (unsigned int)this->width())
        {
            Raquette->setPOS(Raquette->getPOS().getX() + 10,Raquette->getPOS().getY());
        }
        else
        {
            Raquette->setPOS(this->width(),Raquette->getPOS().getY());
        }

    }
    else if(Event->key() == Qt::Key_Escape)
    {
        this->close();

    }











}

void Casse_brique::Tick()
{
    Check_Collision();

    if(Balle->getLaunch())
    {
        Balle->setPOS(Balle->getPOS().getX() + Balle->getVEL().getX(), Balle->getPOS().getY() + Balle->getVEL().getY());

    }



    update();
}





