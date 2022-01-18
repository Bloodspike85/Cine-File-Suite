#include "GAMES/Pong/pong.h"

pong::pong():QWidget()
{

    srand (time(NULL));
    this->setWindowFlags(Qt::Window
                         | Qt::WindowMinimizeButtonHint
                         | Qt::WindowMaximizeButtonHint
                         | Qt::WindowCloseButtonHint);

    this->setWindowTitle("Cine_File_Suite : Pong");

    qDebug() << "Windows flags OK" ;
    this->setGeometry((resolution_Ecran::Get_Resolution_Ecran().width() /4)  ,
                      (resolution_Ecran::Get_Resolution_Ecran().height() /4)  ,
                      (resolution_Ecran::Get_Resolution_Ecran().width() / 2),
                      (resolution_Ecran::Get_Resolution_Ecran().height() / 2));

    qDebug() << "geo OK" ;
    this->setFocusPolicy(Qt::StrongFocus);
    qDebug() << "focus OK" ;

    Pong_Player = new Player(20 , this->height() /2);
    Pong_Player->setSIZE(10,100);
    Pong_Player->setPOS(Pong_Player->getPOS().getX(),Pong_Player->getPOS().getY() - (Pong_Player->getSIZE().getY() /2));
    Pong_Player->setHuman(true);
    qDebug() << "Player OK" ;

    Pong_IA = new Player((resolution_Ecran::Get_Resolution_Ecran().width() / 2) - 40,this->height() /2);
    Pong_IA->setSIZE(10,100);
    Pong_IA->setHuman(false);
    qDebug() << "IA OK" ;

    Pong_Balle = new Balle(Pong_Player->getPOS().getX() + 15,
                     Pong_Player->getPOS().getY() + 25,
                     10,0,50,50);

    qDebug() << "BALLE OK" ;

    Reset();

    Pong_Player->setScore(0);
    Pong_IA->setScore(0);




    connect(&Delta_time,SIGNAL(timeout()),this,SLOT(Tick()));

    Delta_time.start(25);

}

void pong::Reset()
{
    Pong_Balle->setPOS(Pong_Player->getPOS().getX() + 15,Pong_Player->getPOS().getY() + 25);

    Pong_Balle->setVEL(10,0);

    Pong_Balle->setLaunch(false) ;
    Pong_Balle->setSIZE(50,50);
}

void pong::Check_Collision()
{
    if(Pong_Balle->getLaunch())
	{

		
			//On vérifie si il y a collision avec l'écran (en haut et en bas)

        if(Pong_Balle->getPOS().getY() < 10 || (Pong_Balle->getPOS().getY() + Pong_Balle->getSIZE().getY()) >= (unsigned int)(this->height()))
        {
            Pong_Balle->setVEL(Pong_Balle->getVEL().getX() + 1, -Pong_Balle->getVEL().getY());

        }




		//Puis avec les raquettes

        //Player

        if(Pong_Player->CheckCollision(Pong_Balle,ComeFrom::RIGHT))
        {

            Pong_Balle->setSIZE(Pong_Balle->getSIZE().getX() - 5,Pong_Balle->getSIZE().getY() -5);

            Pong_Balle->setVEL(-Pong_Balle->getVEL().getX() ,(rand() % (B_upper_angle - B_Lower_angle + 1) + B_Lower_angle));

        }
        else
        {
            Pong_Balle->setVEL(Pong_Balle->getVEL().getX(),Pong_Balle->getVEL().getY());
        }


        //IA
        if(Pong_IA->CheckCollision(Pong_Balle,ComeFrom::LEFT))
        {

            Pong_Balle->setSIZE(Pong_Balle->getSIZE().getX() - 5,Pong_Balle->getSIZE().getY() -5);

            Pong_Balle->setVEL(-Pong_Balle->getVEL().getX() ,(rand() % (B_upper_angle - B_Lower_angle + 1) + B_Lower_angle));
        }
        else
        {
            Pong_Balle->setVEL(Pong_Balle->getVEL().getX(),Pong_Balle->getVEL().getY());
        }

        //Est ce que l'on marque un point?
        if(Pong_Balle->getPOS().getX() <= 10)
        {
            Reset();
            Pong_IA->setScore(Pong_IA->getScore() + 1);


        }
        else if((Pong_Balle->getPOS().getX() + Pong_Balle->getSIZE().getX()) >= (unsigned int)(this->width() - 10))
        {
            Reset();
            Pong_Player->setScore(Pong_Player->getScore() + 1);

        }
	}
	else
	{
        Pong_Balle->setPOS(Pong_Player->getPOS().getX() + 15,Pong_Player->getPOS().getY() + 25);

	}
    
}



void pong::paintEvent(QPaintEvent *Event)
{
    if(Pong_Balle->getSIZE().getX() < 5)
    {
        Pong_Balle->setSIZE(5,5);
    }

    if(!Pong_Balle->getLaunch())
    {
        QPainter *Launch_text = new QPainter(this);
        Launch_text->drawText(10,(this->height() - 25),QString("Appuyer sur la barre espace pour lancer la balle et les flèches directionnelles pour déplacer la raquette"));

    }

    QPainter *Border = new QPainter(this);
    Border->drawRoundedRect(5,5,this->width() - 10,this->height() - 10,3,3);

    Pong_Player->painter = new QPainter(this);
    Pong_Player->painter->setBrush(Qt::black);
    Pong_Player->painter->setPen(Qt::red);
    Pong_Player->painter->drawRoundedRect(Pong_Player->getPOS().getX(),Pong_Player->getPOS().getY(),Pong_Player->getSIZE().getX(),Pong_Player->getSIZE().getY(),3,3);


    Pong_IA->painter = new QPainter(this);
    Pong_IA->painter->setBrush(Qt::black);
    Pong_IA->painter->setPen(Qt::red);
    Pong_IA->painter->drawRoundedRect(Pong_IA->getPOS().getX(),Pong_IA->getPOS().getY(),Pong_IA->getSIZE().getX(),Pong_IA->getSIZE().getY(),3,3);




    Pong_Balle->painter = new QPainter(this);
    Pong_Balle->painter->setBrush(Qt::black);
    Pong_Balle->painter->setPen(Qt::red);
    Pong_Balle->painter->drawEllipse(Pong_Balle->getPOS().getX(),Pong_Balle->getPOS().getY(),Pong_Balle->getSIZE().getX(),Pong_Balle->getSIZE().getY());




    Score_text = new QPainter(this);
    Score_text->drawText((this->width() / 2),20,QString(QString::number(Pong_Player->getScore()) + " :: " + QString::number(Pong_IA->getScore()) ));


    QPainter *BPOSX = new QPainter(this);
    BPOSX->drawText(10,20,QString("Pos X" + QString::number(Pong_Balle->getPOS().getX())));
    QPainter *BPOSY = new QPainter(this);
    BPOSY->drawText(10,30,QString("Pos Y" + QString::number(Pong_Balle->getPOS().getY())));
    QPainter *VELX = new QPainter(this);
    VELX->drawText(10,40,QString("VEL X" + QString::number(Pong_Balle->getVEL().getX())));
    QPainter *VELY = new QPainter(this);
    VELY->drawText(10,50,QString("VEL Y" + QString::number(Pong_Balle->getVEL().getY())));
    QPainter *Launch = new QPainter(this);
    Launch->drawText(10,60,QString("Launch State" + QString::number(Pong_Balle->getLaunch())));
    QPainter *Ball_size = new QPainter(this);
    Ball_size->drawText(10,70,QString("Ball size :" + QString::number(Pong_Balle->getSIZE().getX())));









}

void pong::keyPressEvent(QKeyEvent *Event)
{
    std::cout << "On appuie sur une touche : " << std::endl;
	
    if(!Pong_Balle->getLaunch() && Event->key() == Qt::Key_Space)
	{
        std::cout << "START" << std::endl;
        Pong_Balle->setLaunch(true);

        Pong_Balle->setVEL(Pong_Balle->getVEL().getX() + 10 , rand() % (B_upper_angle - B_Lower_angle + 1) + B_Lower_angle);


        update();

	}
	if(Event->key() == Qt::Key_Up)
    {
        if(Pong_Player->getPOS().getY() > 10)
        {
            Pong_Player->setPOS(Pong_Player->getPOS().getX(),Pong_Player->getPOS().getY() - 10);
        }
        else
        {
            Pong_Player->setPOS(Pong_Player->getPOS().getX() ,10);
        }

    }
    else if(Event->key() == Qt::Key_Down)
    {
        if(Pong_Player->getPOS().getY() < (unsigned int)(this->height() - (Pong_Player->getSIZE().getY() + 10)))
        {
            Pong_Player->setPOS(Pong_Player->getPOS().getX() ,Pong_Player->getPOS().getY() + 10);
        }
        else
        {
            Pong_Player->setPOS(Pong_Player->getPOS().getX() ,this->height() - (Pong_Player->getSIZE().getY() + 10));
        }
    }
    else if(Event->key() == Qt::Key_Escape)
    {
        this->close();

    }
    










}

void pong::Tick()
{
    Check_Collision();

    Pong_Balle->setPOS(Pong_Balle->getPOS().getX() + Pong_Balle->getVEL().getX() , Pong_Balle->getPOS().getY() + Pong_Balle->getVEL().getY());


    if((Pong_IA->getPOS().getY() + Pong_IA->getSIZE().getY()) <= (unsigned int)this->height() )
    {
        Pong_IA->setPOS(Pong_IA->getPOS().getX(),Pong_Balle->getPOS().getY() - 25);
    }
    else
    {
        Pong_IA->setPOS(Pong_IA->getPOS().getX(),this->height() - Pong_IA->getSIZE().getY() );
    }

    if( Pong_IA->getPOS().getY() >= 10 )
    {
        Pong_IA->setPOS(Pong_IA->getPOS().getX(),Pong_Balle->getPOS().getY() - 25);
    }
    else
    {
        Pong_IA->setPOS(Pong_IA->getPOS().getX(),10);
    }


    update();
}





