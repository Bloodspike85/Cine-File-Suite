#ifndef KDM_MANAGER_H
#define KDM_MANAGER_H

#ifndef WIN32
    #include <sys/types.h>
#endif // !WIN32


#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <ios>
#include <vector>
#include<algorithm>

#include <QApplication>
#include <QPushButton>
#include "QProgressBar"
#include "QScrollArea"
#include "QScrollBar"
#include "QCheckBox"
#include <QLayout>
#include <QGroupBox>
#include <QMenuBar>
#include <QToolButton>
#include <QLineEdit>
#include <QTimer>



#include "message_box.h"
#include "structure.h"
#include "Gestions_Des_Projecteurs.h"

class Directory;
#include "Gestions_Des_Dossiers.h"

class kdm;
#include "Gestions_des_kdms.h"

class fichiers;
#include "Gestions_Des_Fichiers.h"












class KDM_MANAGER : public QWidget
{

    Q_OBJECT

    public:

    KDM_MANAGER(int Hauteur_Fenetre,int Largeur_Fenetre, bool Save_Activation,bool Log_Activation, bool m_debug);
    ~KDM_MANAGER();


    QWidget* Creation_Interface_Graphique();
    QWidget* Creation_Interface_Graphique_Resultat();


    const std::string CurrentDateAndTime();
    void TriKDM();
    void EffaceDossierVide();
    void InitiateAll();

    void LaunchApp();

    void Creation_Log();
    void Erreur_Log(std::string Erreur_string);
    QWidget* Get_Resultat();

    int Dossier_effacer(){return Cmb_Dossier_Effacer;}
    int KDM_Copier(){return Cmb_KDM_copier;}
    int KDM_effacer(){return Cmb_KDM_Effacer;}
    int KDM_Sauvegarder(){return Cmb_KDM_Sauvegarder;}

    void Ajouter_Un_TexteInfo(std::string Texte);
    void Ajouter_Un_Dossier_Supprimer(std::string Texte){Dossier_Supprimer.push_back(new std::string(Texte));}
    void Ajouter_Une_Nouvelle_KDM(std::string Texte){m_Nouvelle_KDM.push_back(new std::string(Texte));}
    void Ajouter_Une_KDM_Supprimer(std::string Texte){KDM_Supprimer.push_back(new std::string(Texte));}
    void Ajouter_Une_KDM_Arrivant_A_Expiration(std::string Texte){Kdm_Arrivant_A_Expiration.push_back(new std::string(Texte));}

    void Ajouter_Un_erreur_handler(std::string Texte)
    {
        //On crée un fichier log pour voir ou se situe l'erreur

        Error_handler.push_back(new std::string(Texte));
        Erreur_Log(Texte);
    }

    bool Get_Sauvegarde_State(){return Is_Sauvegarde_Activated ;}
    bool Get_Debug_State(){return Is_Debug_handler_Activated ;}

    void Incrementation_KDM_Sauvegarder(){ Cmb_KDM_Sauvegarder++ ;}
    void Incrementation_KDM_Copier(){ Cmb_KDM_copier++ ;}
    void Incrementation_KDM_Effacer(){ Cmb_KDM_Effacer++ ;}
    void Incrementation_Dossier_Effacer(){ Cmb_Dossier_Effacer++ ;}




    std::string Get_Element_Dossier_Supprimer(unsigned int Numero){return *Dossier_Supprimer[Numero];}

    unsigned int Get_Dossier_Supprimer_Size(){return Dossier_Supprimer.size();}

    unsigned int Get_KDM_Supprimer_Size(){return KDM_Supprimer.size();}
    unsigned int Get_KDM_Arrivant_A_Expiration_Size(){return Kdm_Arrivant_A_Expiration.size();}


    std::string Get_Nouvelle_KDM(unsigned int Numero){return *m_Nouvelle_KDM[Numero];}
    unsigned int Get_Nouvelle_KDM_Size(){return  m_Nouvelle_KDM.size();}



    std::string Get_Element_KDM_Supprimer(unsigned int Numero){return *KDM_Supprimer[Numero];}

    std::string Get_Element_KDM_Arrivant_A_Expiration(unsigned int Numero){return *Kdm_Arrivant_A_Expiration[Numero];}


    std::string Get_erreur_handler(unsigned int Numero){return *Error_handler[Numero];}
    unsigned int Get_erreur_handler_Size(){return  Error_handler.size();}






    unsigned int getTotal_file_readed();
    void setTotal_file_readed(unsigned int newTotal_file_readed);

public slots:

    void Gestion_Bouton();
    void tick();



    private:

    QTimer *Timer;

    std::string *Folder_Path;

    QWidget *Fenetre_Actuelle;
    QVBoxLayout *Fenetre_Holder;

    bool Is_Sauvegarde_Activated;
    bool IS_Log_Activated;
    bool Is_Debug_handler_Activated;

    std::vector <std::string*> Dossier_Supprimer;
    std::vector <std::string*> m_Nouvelle_KDM;
    std::vector <std::string*> KDM_Supprimer;
    std::vector <std::string*> Kdm_Arrivant_A_Expiration;

    std::vector <std::string*> Error_handler;


    QScrollArea *Scroll_info = nullptr;
    QProgressBar *m_Progress_Bar = nullptr;

    QVBoxLayout *Kdm_Manager_Layout = nullptr;
    QHBoxLayout *Kdm_Manager_Bouton_And_CheckBox_Holder;

    QVBoxLayout *Info_Layout_Holder = nullptr;
    QHBoxLayout *Kdm_Trier = nullptr;

    QPushButton *KDM_Manager_return_back;
    QToolButton *Kdm_Manager_Bouton;

    Message_Box *Box[3];

    QLabel *Info_Holder = nullptr;

    QWidget* Fenetre_Option;

    Mon_Logiciel logiciel ;

    Directory *DirRep = nullptr;

    fichiers *FileReader = nullptr;


    std::string Ancien_Texte;
    std::string Nouveau_Texte;
    std::string Today;
    int Progress_Value;

    int j;

    double Total_File_Number;
    double Total_file_readed;

    int Cmb_KDM_Effacer;
    int Cmb_KDM_Sauvegarder;
    int Cmb_KDM_copier;

    int Cmb_Dossier_Effacer;

    int Hauteur_Fenetre;
    int Largeur_Fenetre;


    std::vector<QLabel*> Text_Info;


};


#include "main.h"

#endif


