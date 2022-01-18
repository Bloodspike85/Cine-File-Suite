#ifndef GESTIONS_DES_PROJECTEURS_H
#define GESTIONS_DES_PROJECTEURS_H

#ifndef WIN32
    #include <sys/types.h>
#endif // !WIN32

#include <QApplication>
#include <QLabel>
#include <QLayout>
#include <QPushButton>
#include <QLineEdit>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <iostream>
#include <QDebug>
#include "dirent.h"




class ProjecteurCheck : public QWidget
{
    Q_OBJECT
    public:
    //Constructeur et destructeur//
    ProjecteurCheck();
    ~ProjecteurCheck();

    unsigned int GetServeurNumber();//Savoir combien il y a de projecteur//
    static unsigned int GetActiveServeurNumber();//Savoir combien de dossier de proj nous avons//
    void Remplir_Liste_Serveur();

    unsigned int Get_Serveur_Name_Size(){return Numero_De_Serveur.size();}


    std::string Get_Element_Liste_Projecteur(unsigned int Numero){return *Numero_De_Serveur[Numero];}

    static unsigned int GetListOfServer();


public slots:
void remplir_La_Liste();
void Enregistrer();


    private:
        unsigned int Nombre_de_serveur;

        QLineEdit *Ecrire = nullptr;
        std::vector<QLineEdit*> Lecture_serveur;
        std::vector<QLabel*> Lecture_Projecteur;

        std::vector<std::string*> Numero_De_Serveur;

};

#endif


