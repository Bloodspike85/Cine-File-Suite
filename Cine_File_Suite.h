#ifndef CINE_FILE_SUITE_H
#define CINE_FILE_SUITE_H

//Cette classe est la base du logiciel
//Elle sera l'interface graphique principal

#ifndef WIN32
    #include <sys/types.h>
#endif // !WIN32


#include <QApplication>
#include <QScreen>
#include "QToolButton"
#include "QLayout"
#include <QDesktopServices>
#include <QProcess>

#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include <QKeyEvent>

#include "GAMES/game.h"


#include "main.h"
#include "kdm_lister.h"
#include "KDM_Manager.h"


#define ADMIN_USER_NAME  "ADMIN"
#define ADMIN_PASSWORD "789456123"

class Cine_File_Suite : public QWidget
{

    Q_OBJECT

public :

    Cine_File_Suite(QWidget *Fenetre_Principal);
    ~Cine_File_Suite();

    QWidget *Creation_Interface_Graphique();
    QWidget *Creation_Fenetre_Option();
    QWidget *Creation_Fenetre_Autre();

    QWidget *Creation_Liste_Projecteur();

    QWidget* Creation_Fenetre_Bienvenue();

    //Lors du premier lancement il faudra configurer CINE_FILE_SUITE nous utiliserons donc ces fonctions

    QWidget *Creation_Configuration_0();
    QWidget *Creation_Configuration_1();
    QWidget *Creation_Configuration_2();
    QWidget *Creation_Configuration_3();
    QWidget *Creation_Configuration_4();

    void Read_Configuration_File();

    void Show_Main_App();
    void Show_Fenetre_Bienvenue();

    void reset_Grid_Layout();


    void keyPressEvent(QKeyEvent *Event);


public slots :

    void Handle_Button();
    void Add_Serveur_Number();
    void Delete_Serveur_Number();
    void Configuration_File_Modification();


    void Launch_Jeu();

private :

    //Vérification si le logiciel à acces à internet
    bool is_connected_to_internet()
    {
        // à implémenter
        if(QProcess::execute("ping -n 1 www.google.com") == 0)
        {
               return true;
        }
        else
        {
               return false;
        }

    }

    //On recupere le pointeur de la fenetre principal
    QWidget *Fenetre_Principal_Widget;

    //On creer la largeur et la hauteur de la fenetre
    int Largeur_Fenetre = 0;
    int Hauteur_Fenetre = 0;
    // On creer les point d'ancrage
    int Point_X = 0;
    int Point_Y = 0;

    //Trois éléments pour configurer une protection administrateur des option
    bool Is_Admin = false;
    QLineEdit *User_Name;
    QLineEdit *Password;
    QPushButton *Security_Test;

    /*Une variable int pour se situer dans la configuration
     *Un bouton suivant
     *Un bouton predent
     *Une variable contenant le nombre de projecteur
     *Un champ de texte pour informer du nombre de projecteur
     *Une liste de projecteur
     *Un layout pour contenir le nombre de projecteur et le label
     *Une scroll area qui contiendra le layout cité précédemment
     *Deux check box
     */

    int Place_In_The_Configuration;
    QPushButton *Cine_File_Suite_Configuration_Bouton_Suivant;
    QPushButton *Cine_File_Suite_Configuration_Bouton_Precedent;

    int Temp_Serveur_Number_Holder ;
    QLineEdit* Projecteur_Number_Holder_LineEdit;

    std::vector<QLineEdit*> Serveur_Number_Holder_Line_Edit;

    QScrollArea *Scroll_Area_Serveur_Number ;

    QGridLayout *GridLayout = new QGridLayout;

    QCheckBox *Sauvegarde_kdm_Configuration = nullptr;
    QCheckBox *Fichier_Log_Configuration = nullptr;

    /*******************************************************************************************************/

    //On a un widget pour l'élement sélectionné

    QWidget *Cine_File_Suite_App_Selectionnee;
    QWidget *Cine_File_Suite_App_Last;//Seulement pour retourner en arriere pour le tri de kdm

    QMenuBar *Cine_file_suite_menuBar;

    QMenu *Cine_file_suite_menu ;
    QAction *Jeu;

    //Chaine de carractere pour dire l'application choisi
    std::string App_State = "";


    //Des variables pour les options

    std::vector<std::string* > Serveur_Number_Holder;
    bool Save_Place_Holder = false ;
    bool Log_File_Holder = false;

    //Quatre boutons : Un pour KDM_Manager , un pour KDM_LISTER , un pour les options et un pour quitter


    QToolButton *KDM_Manager_Launcher;
    QToolButton *KDM_Lister_Launcher;
    QToolButton *Cine_File_Suite_Option;
    QToolButton *Cine_File_Suite_Autre;

    QToolButton *Cine_File_Suite_Quitter;

    //Deux Layout afin de tout oragniser un vertical pour le menu et les deux bouton et la date , un autre pour les deux boutons

    QVBoxLayout *Cine_File_Suite_Layout;
    QHBoxLayout *Cine_File_Suite_App_Layout;


    //Deux check box pour les options

    QCheckBox *Sauvegarde_Kdm = nullptr;
    QCheckBox *Fichier_Log = nullptr;
    QCheckBox *Debug_handler = nullptr;

    std::vector< QPushButton *> Bouton_delete_holder;
    bool Is_change_made;


    //Gestion des erreur
    bool CineFileSuiteDebug;






};


#endif
