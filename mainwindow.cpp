
#include <QDebug>
#include "mainwindow.h"

Main_Window::Main_Window():QWidget()
{
    fichiers::handle_Old_Conf_file();


    Proj = new ProjecteurCheck();

    Main_App_Layout = new QHBoxLayout();

    this->setLayout(Main_App_Layout);



    unsigned int NB_Serveur = Proj->GetServeurNumber();

    qDebug() << NB_Serveur ;

    if(NB_Serveur == 0)
    {
        qDebug() << "Création de la partie configuration" ;

        Main_APP = new Cine_File_Suite(this);
        Main_APP->Show_Fenetre_Bienvenue();
    }
    else
    {
        //création du neccessaire pour KDM_Lister et KDM_MANAGER//

        qDebug() << "Création de l'application principale" ;
        Main_APP = new Cine_File_Suite(this);
        Main_APP->Show_Main_App();

    }



}

Main_Window::~Main_Window()
{

        if(Proj != nullptr)delete Proj;

        Main_APP = nullptr ;
        delete Main_APP ;



}
