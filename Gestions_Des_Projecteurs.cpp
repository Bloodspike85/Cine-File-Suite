#include "Gestions_Des_Projecteurs.h"
#include "main.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>



ProjecteurCheck::ProjecteurCheck()
{
    Nombre_de_serveur = 0;
    Ecrire = nullptr;
}

ProjecteurCheck::~ProjecteurCheck()
{
    qDebug() << "Suppression du gestion de serveur ... \n" ;

    if(!Lecture_serveur.empty())
    {
        Lecture_serveur.clear();
    }
    if(!Lecture_Projecteur.empty())
    {
        Lecture_Projecteur.clear();
    }
    if(Numero_De_Serveur.empty())
    {
       Numero_De_Serveur.clear();
    }


    if(Ecrire != nullptr)
    {
       delete Ecrire;
    }


    qDebug() << "Suppression du gestion de serveur réussi \n" ;

}

unsigned int ProjecteurCheck::GetListOfServer()
{
    std::ifstream Liste_De_Serveur;
    Liste_De_Serveur.open(FichierConfiguration);
    unsigned int NB_de_serveur = 0;

    if(Liste_De_Serveur)
    {

        std::cout << "Fichier de configuration ouvert" << std::endl;
        std::string numero_de_serveur;


        while(std::getline(Liste_De_Serveur,numero_de_serveur))
        {
            std::istringstream Premier_Mot(numero_de_serveur.c_str());
            std::string LineHeader;
            Premier_Mot >> LineHeader;
            if(LineHeader.compare("Serveur") == 0)
            {
                NB_de_serveur++;
            }
            LineHeader = "";

        }
        Liste_De_Serveur.close();
    }
    else
    {
        std::cout << "Une erreur est survenue lors de l'ouverture du fichier de configuration" << std::endl;
    }




    return NB_de_serveur;
}

unsigned int ProjecteurCheck::GetServeurNumber()
{

    std::cout << "getserveurnumber()" << std::endl;
    std::ifstream Liste_De_Serveur;
    Liste_De_Serveur.open(FichierConfiguration);

    if(Liste_De_Serveur.is_open())
    {

        std::cout << "Fichier de configuration ouvert" << std::endl;

        std::string numero_de_serveur = "";

        if(!Numero_De_Serveur.empty())
        {
            std::cout << "suppression de la liste de serveur" << std::endl;
            Numero_De_Serveur.clear();
        }
        else
        {
            std::cout << "pas de liste de serveur" << std::endl;
        }

        while(std::getline(Liste_De_Serveur,numero_de_serveur))
        {
            std::cout << numero_de_serveur << std::endl;
            std::istringstream Premier_Mot(numero_de_serveur.c_str());
            std::string LineHeader;
            Premier_Mot >> LineHeader;
            if(LineHeader.compare("Serveur") == 0)
            {
                LineHeader = "";
                Premier_Mot >> LineHeader;
                Nombre_de_serveur++;
                Numero_De_Serveur.push_back(new std::string(LineHeader));

            }
            LineHeader = "";

        }

        std::cout << "Il y a " << Nombre_de_serveur << " serveur." << std::endl;
        Liste_De_Serveur.close();

    }
    else
    {
        std::cout << "Une erreur est survenue lors de l'ouverture du fichier de configuration" << std::endl;
    }




    return Nombre_de_serveur;
}

void ProjecteurCheck::Remplir_Liste_Serveur()
{
    QWidget *Fenetre;
    QLabel *Text;
    QVBoxLayout *Layout;
    QPushButton *Bouton;
    Bouton = new QPushButton("OK");

    Fenetre = new QWidget;
    Text = new QLabel;
    Text->setText("Combien avez-vous de projecteurs?");
    Layout = new QVBoxLayout;
    Ecrire = new QLineEdit;

    Fenetre->setLayout(Layout);
    Layout->addWidget(Text);
    Layout->addWidget(Ecrire);
    Layout->addWidget(Bouton);

    Fenetre->show();
    Fenetre->move(20,20);




    connect(Bouton,SIGNAL(clicked(bool)),this,SLOT(remplir_La_Liste()));
    connect(Bouton,SIGNAL(clicked(bool)),Fenetre,SLOT(close()));

}


void ProjecteurCheck::remplir_La_Liste()
{
    if(Ecrire->text().toInt() == 0)
    {
        return;
    }
    else
    {
        Nombre_de_serveur = Ecrire->text().toUInt();
        QLabel *Warning;
        Warning = new QLabel("Apres avoir cliqué sur OK merci de redemarer le logiciel");
        QWidget *Fenetre;
        QVBoxLayout *Layout;
        QPushButton *Bouton;

        Fenetre = new QWidget;
        Layout = new QVBoxLayout;
        Bouton = new QPushButton;
        Bouton->setText("OK");

        //std::cout << Nombre_de_serveur << std::endl;
        for(unsigned int i =0;i < Nombre_de_serveur ;i++)
        {
          std::stringstream Conv;
          Conv << i+1;
          std::string Temporaire;
          Temporaire = "Numero de serveur du projecteur_"+ Conv.str();
          Lecture_Projecteur.push_back(new QLabel);
          Lecture_Projecteur[i]->setText(QString(Temporaire.c_str()));
          Lecture_serveur.push_back(new QLineEdit);
        }

        for(unsigned int i =0;i < Nombre_de_serveur;i++)
        {
            Layout->addWidget(Lecture_Projecteur[i]);
            Layout->addWidget(Lecture_serveur[i]);
        }

        Layout->addWidget(Bouton);
        Layout->addWidget(Warning);

        Fenetre->setLayout(Layout);

        Fenetre->move(20,20);
        Fenetre->show();

        Fenetre->setFocus();

        connect(Bouton,SIGNAL(clicked(bool)),this,SLOT(Enregistrer()));
    }

}

void ProjecteurCheck::Enregistrer()
{
    std::ofstream Liste_De_Serveur;
    Liste_De_Serveur.open(FichierConfiguration);

    for(unsigned int i = 0;i < Nombre_de_serveur;i++)
    {
        Liste_De_Serveur << "Serveur " << Lecture_serveur[i]->text().toStdString() << std::endl;
    }
    Liste_De_Serveur.close();

    qApp->closeAllWindows();

}

unsigned int ProjecteurCheck::GetActiveServeurNumber()
{
    struct dirent *FichierLu;
    DIR *Repertoire;
    std::vector <std::string*> Temporaire;
    unsigned int Nombre_De_Serveur_Actif = 0;


    Repertoire = nullptr;
    Repertoire = opendir(".");

    while ((FichierLu = readdir(Repertoire)))
    {
        if(FichierLu->d_name == NULL)
        {
            break;
        }
        Temporaire.push_back(new std::string(FichierLu->d_name));
        //std::cout << "Fichier = " << FichierLu->d_name << std::endl;
    }

    closedir(Repertoire);

    //std::cout << Temporaire.size() << std::endl;
    for(unsigned int i = 0;i < Temporaire.size();i++)
    {
        for(unsigned int j =0;j < GetListOfServer() ;j++)
        {
            std::stringstream Conv;
            Conv << j+1;
            std::string Temp;
            Temp = "Projecteur_" + Conv.str();
            //std::cout << "Est ce que " << Temporaire[i]->c_str() << " est egale a " << Temp << " ?" << std::endl;
             if(Temporaire[i]->compare(Temp) == 0)
             {
                 //std::cout << "oui" << std::endl;
                 Nombre_De_Serveur_Actif++;
             }
             else
             {
                //std::cout << "non" << std::endl;
             }
        }


    }


    return Nombre_De_Serveur_Actif;




}
