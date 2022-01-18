#include "GAMES/Boule/bimbamboule.h"
#include "GAMES/Commune/Vector.h"


BimBamBoule::BimBamBoule()
{


    NBR_DE_LIGNE_MAX = (this->height() / ( (this->width() / NBR_DE_COLONNE) + 5 ) );

    this->setWindowTitle("Cine_File_Suite : BIM BAM BOULE");

    srand(time(NULL));
    nombre_de_ligne_start = (rand() % (NBR_DE_LIGNE_MAX - 1) + 1);

    for(unsigned int i = 0; i < nombre_de_ligne_start ; i++)
    {
        for(unsigned int j = 0; j < NBR_DE_COLONNE ; j++)
        {
           bubble.push_back(new Bubble(new QRect(j * (this->width() / NBR_DE_COLONNE) + 5,i * (this->width() / NBR_DE_COLONNE) + 5,(this->width() -30) / NBR_DE_COLONNE,(this->width() -30) / NBR_DE_COLONNE)));
        }
    }

    Player_b.push_back( new Player_bubble(new QRect((this->width() / 2) - (this->width()/NBR_DE_COLONNE) / 2,
                                         this->height() - 10 - (this->width() /NBR_DE_COLONNE) ,
                                         (this->width() -30) / NBR_DE_COLONNE,
                                         (this->width() -30) / NBR_DE_COLONNE)) );




    Pointeur = new PainterObject(Player_b[Player_b.size() - 1]->getOrigin().getX(),Player_b[Player_b.size() - 1]->getOrigin().getY(),0,0,0,100);
    Pointeur->setAngle(angle_min);

    connect(&Delta_time,SIGNAL(timeout()),this,SLOT(Tick()));

    Delta_time.start(25);



}

void BimBamBoule::Game_update()
{
    if(Player_b[Player_b.size() - 1]->getLaunch())
    {
        if(Player_b[Player_b.size() - 1]->getPosition().getX() <= 0)
        {
            Player_b[Player_b.size() - 1]->setSpeed(- Player_b[Player_b.size() - 1]->getSpeed().getX() ,Player_b[Player_b.size() - 1]->getSpeed().getY());
        }
        else if(Player_b[Player_b.size() - 1]->getPosition().getY() <= 0)
        {
            Player_b[Player_b.size() - 1]->setSpeed(Player_b[Player_b.size() - 1]->getSpeed().getX() , - Player_b[Player_b.size() - 1]->getSpeed().getY());
        }
        if(Player_b[Player_b.size() - 1]->getPosition().getX() + Player_b[Player_b.size() - 1]->getSIZE().getX() >= this->width())
        {
            Player_b[Player_b.size() - 1]->setSpeed(- Player_b[Player_b.size() - 1]->getSpeed().getX() ,Player_b[Player_b.size() - 1]->getSpeed().getY());
        }
        else if(Player_b[Player_b.size() - 1]->getPosition().getY() +Player_b[Player_b.size() - 1]->getSIZE().getY() >= this->height())
        {
           Player_b[Player_b.size() - 1]->setSpeed(Player_b[Player_b.size() - 1]->getSpeed().getX() , - Player_b[Player_b.size() - 1]->getSpeed().getY());
        }

        Player_b[Player_b.size() - 1]->setVelocite(Player_b[Player_b.size() - 1]->getDirection().getX() * Player_b[Player_b.size() - 1]->getSpeed().getX() , Player_b[Player_b.size() - 1]->getDirection().getY() * Player_b[Player_b.size() - 1]->getSpeed().getY() );
    }

    if(!bubble.empty())
    {
        for(unsigned int i = 0; i < bubble.size() ; i++)
        {

                if(bubble[i] != NULL)
                {
                    //On regarde si on a une colision avec des balles du jeu
                   if(Player_b[Player_b.size() - 1]->CheckColision(bubble[i],Player_b[Player_b.size() - 1]->getPosition().getX(),Player_b[Player_b.size() - 1]->getPosition().getY()))
                   {
                       bubble[i]->setColor(new QBrush(Qt::yellow));
                       Player_b[Player_b.size() - 1]->setVelocite(0,0);//On arrete la balle du joueur
                       //On replace le joeur au bon endroit
                       Player_b[Player_b.size() - 1]->setPosition(bubble[i]->getPOS().getX(),bubble[i]->getPOS().getY() + bubble[i]->getSIZE().getY());


                       Player_b.push_back( new Player_bubble(new QRect((this->width() / 2) - (this->width()/NBR_DE_COLONNE) / 2,
                                                            this->height() - 10 - (this->width() /NBR_DE_COLONNE) ,
                                                            (this->width() -30) / NBR_DE_COLONNE,
                                                            (this->width() -30) / NBR_DE_COLONNE)) ); //on ajoute un joeur
                       Add_One_Row();

                       return;
                   }



                }


        }
    }

    repaint();

}

void BimBamBoule::Game_Draw()
{
    if(!Player_b[Player_b.size() - 1]->getLaunch())
    {
        Pointeur->painter = new QPainter(this);

        double endx = cos(Pointeur->getAngle()) * Pointeur->getSIZE().getY();
        double endy = sin(Pointeur->getAngle()) * Pointeur->getSIZE().getY();

        Pointeur->painter->drawLine(Pointeur->getPOS().getX() , Pointeur->getPOS().getY(),
                                    Pointeur->getPOS().getX() + endx,
                                    Pointeur->getPOS().getY() + endy);



    }

    if(!bubble.empty())
    {
        for(unsigned int i = 0; i < bubble.size() ; i++)
        {

            bubble[i]->Draw(this);


        }
    }

    for ( unsigned int i = 0; i <Player_b.size() ; i++ )
    {
        Player_b[i]->Draw(this,Player_b[i]->getPosition().getX(),Player_b[i]->getPosition().getY());
    }



}

void BimBamBoule::Add_One_Row()
{
    //Fonction à ré écrire

    if(nombre_de_ligne_start < NBR_DE_LIGNE_MAX)
    {

    std::vector<Bubble *> b_copie;

    if(!bubble.empty())
    {
        for(unsigned int i = 0 ; i < bubble.size() ; i++)
        {
            b_copie.push_back(bubble[i]);
        }
    }

    bubble.clear();

    if(!b_copie.empty())
    {
        for(unsigned int i = 0; i < 1 ; i++)
        {
            for(unsigned int j = 0; j < NBR_DE_COLONNE ; j++)
            {
               bubble.push_back(new Bubble(new QRect(j * (this->width() / NBR_DE_COLONNE) + 5,i * (this->width() / NBR_DE_COLONNE) + 5,(this->width() -30) / NBR_DE_COLONNE,(this->width() -30) / NBR_DE_COLONNE)));
            }
        }

        for(unsigned int i = 0 ; i < b_copie.size() ; i++)
        {
            bubble[i]->setPOS(bubble[i]->getPOS().getX(), bubble[i]->getPOS().getY() + bubble[i]->getSIZE().getY() );
            bubble.push_back(b_copie[i]);
        }
    }

        nombre_de_ligne_start++;

        //On déplace toutes les boules du joueur sauf la dernière que l'on utilise actuelement
        for(unsigned int i = 0;i < Player_b.size() -1 ; i++)
        {
            Player_b[i]->setPosition(Player_b[i]->getPosition().getX(),Player_b[i]->getPosition().getY() + Player_b[i]->getSIZE().getY());
        }
    }
}

void BimBamBoule::paintEvent(QPaintEvent *Event)
{
    QPainter *Border = new QPainter(this);
    Border->drawRoundedRect(5,5,this->width() - 10,this->height() - 10,3,3);

    QPainter *Information = new QPainter(this);
    Information->drawText(10,this->height() - 100 , QString(" Position X : " + QString::number(Player_b[Player_b.size() - 1]->getPosition().getX())));
    Information->drawText(10,this->height() - 90 , QString(" Position Y : " + QString::number(Player_b[Player_b.size() - 1]->getPosition().getY())));
    Information->drawText(10,this->height() - 80 , QString(" Direction X : " + QString::number(Player_b[Player_b.size() - 1]->getDirection().getX())));
    Information->drawText(10,this->height() - 70 , QString(" Direction Y : " + QString::number(Player_b[Player_b.size() - 1]->getDirection().getY())));
    Information->drawText(10,this->height() - 60 , QString(" Velocité X : " + QString::number(Player_b[Player_b.size() - 1]->getVelocite().getX())));
    Information->drawText(10,this->height() - 50 , QString(" Vélocité Y : " + QString::number(Player_b[Player_b.size() - 1]->getVelocite().getY())));

    Game_Draw();


}

void BimBamBoule::keyPressEvent(QKeyEvent *Event)
{
    if(!Player_b[Player_b.size() - 1]->getLaunch())
    {
        std::cout << Pointeur->getAngle() << std::endl;

        if(Event->key() == Qt::Key_Left)
        {
            if(Pointeur->getAngle() > angle_min)
            {
                Pointeur->setAngle(Pointeur->getAngle() - 0.1);
            }
            else
            {
                Pointeur->setAngle(angle_min);
            }

            repaint();
        }
        if(Event->key() == Qt::Key_Right)
        {
            if(Pointeur->getAngle() < angle_max)
            {
                Pointeur->setAngle(Pointeur->getAngle() + 0.1);
            }
            else
            {
                Pointeur->setAngle(angle_max);
            }
            repaint();
        }

        if(Event->key() == Qt::Key_Space)
        {
            Player_b[Player_b.size() - 1]->setLaunch(true);
            double endx = cos(Pointeur->getAngle()) * Pointeur->getSIZE().getY();
            double endy = sin(Pointeur->getAngle()) * Pointeur->getSIZE().getY();
            Player_b[Player_b.size() - 1]->setDirection(endx,endy);
        }
    }




}

void BimBamBoule::Tick()
{

    Player_b[Player_b.size() - 1]->setPosition(Player_b[Player_b.size() - 1]->getPosition().getX() + Player_b[Player_b.size() - 1]->getVelocite().getX(), Player_b[Player_b.size() - 1]->getPosition().getY() + Player_b[Player_b.size() - 1]->getVelocite().getY());

    Game_update();

    repaint();

}
