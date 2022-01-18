/*TODO
*Mettre en place sur le resumer du tri des kdms un moyen afin de revenir en arriere et voir les opérations effectuées
*/






#include "Cine_File_Suite.h"
#include "GAMES/Pong/pong.h"
#include <QDebug>

Cine_File_Suite::Cine_File_Suite(QWidget *Fenetre_Principal):QWidget()
{
    Fenetre_Principal_Widget = new QWidget;
    Fenetre_Principal_Widget = Fenetre_Principal;
    Temp_Serveur_Number_Holder = 0;
    Is_change_made = false;



    Largeur_Fenetre = resolution_Ecran::Get_Resolution_Ecran().width() * 0.5;
    Hauteur_Fenetre = resolution_Ecran::Get_Resolution_Ecran().height() * 0.7;

    Point_X = (resolution_Ecran::Get_Resolution_Ecran().width() /2) - (Largeur_Fenetre /2);
    Point_Y = (resolution_Ecran::Get_Resolution_Ecran().height() /2) - (Hauteur_Fenetre /2);
    Fenetre_Principal->setWindowTitle("Cine File Suite (version C++)");


}
Cine_File_Suite::~Cine_File_Suite()
{

    Fenetre_Principal_Widget = nullptr;
    User_Name = nullptr;
    Password = nullptr;
    Security_Test = nullptr;
    Cine_File_Suite_Configuration_Bouton_Suivant = nullptr;
    Cine_File_Suite_Configuration_Bouton_Precedent = nullptr;

    Projecteur_Number_Holder_LineEdit = nullptr;;

    Serveur_Number_Holder_Line_Edit.clear();

    Scroll_Area_Serveur_Number = nullptr;

    GridLayout = nullptr;

    Sauvegarde_kdm_Configuration = nullptr;
    Fichier_Log_Configuration = nullptr;
    Cine_File_Suite_App_Selectionnee = nullptr;
    std::string App_State = "";


    Serveur_Number_Holder.clear();


    KDM_Manager_Launcher= nullptr;
    KDM_Lister_Launcher= nullptr;
    Cine_File_Suite_Option= nullptr;
    Cine_File_Suite_Autre= nullptr;

    Cine_File_Suite_Quitter= nullptr;
    Cine_File_Suite_Layout = nullptr;
    Cine_File_Suite_App_Layout = nullptr;
    Sauvegarde_Kdm = nullptr;
    Fichier_Log = nullptr;

    Bouton_delete_holder.clear();

    delete Fenetre_Principal_Widget ;
    delete User_Name ;
    delete Password ;
    delete Security_Test ;
    delete Cine_File_Suite_Configuration_Bouton_Suivant ;
    delete Cine_File_Suite_Configuration_Bouton_Precedent ;

    delete Projecteur_Number_Holder_LineEdit;

    delete Scroll_Area_Serveur_Number ;

    delete GridLayout ;

    delete Sauvegarde_kdm_Configuration;
    delete Fichier_Log_Configuration ;
    delete Cine_File_Suite_App_Selectionnee ;


    delete KDM_Manager_Launcher;
    delete KDM_Lister_Launcher;
    delete Cine_File_Suite_Option;
    delete Cine_File_Suite_Autre;

    delete Cine_File_Suite_Quitter;
    delete Cine_File_Suite_Layout ;
    delete Cine_File_Suite_App_Layout;
    delete Sauvegarde_Kdm ;
    delete Fichier_Log ;
}

void Cine_File_Suite::Show_Main_App()
{
    Creation_Interface_Graphique();



}
void Cine_File_Suite::Show_Fenetre_Bienvenue()
{
    qDebug() << "Création de la fenetre de bienvenue";
    Place_In_The_Configuration = 0;

    Cine_File_Suite_App_Selectionnee = Creation_Configuration_0();
    if(!Cine_File_Suite_App_Selectionnee->isVisible())
    {
        Cine_File_Suite_App_Selectionnee->show();
    }


}

void Cine_File_Suite::Read_Configuration_File()
{


    std::ifstream *Config_File;

    Config_File = new std::ifstream;
    Config_File->open(FichierConfiguration);

    bool SERVEUR = false ;
    CineFileSuiteDebug = false;
    Save_Place_Holder = false;
    Log_File_Holder = false;

    if(Config_File)
    {
        std::string Memo_Config;
        while(std::getline(*Config_File,Memo_Config))
        {
            std::istringstream Premier_Mot(Memo_Config.c_str());
            std::string LineHeader;
            Premier_Mot >> LineHeader;
            if(LineHeader.compare("Serveur") == 0)
            {
                SERVEUR = true ;
                LineHeader = "";
                Premier_Mot >> LineHeader;
                Serveur_Number_Holder.push_back(new std::string(LineHeader));
                Serveur_Number_Holder_Line_Edit.push_back(new QLineEdit(Serveur_Number_Holder.at(Serveur_Number_Holder.size()-1)->c_str()));

            }
            if(LineHeader.compare("Debug") == 0)
            {

                LineHeader = "";
                Premier_Mot >> LineHeader;
                if(atoi(LineHeader.c_str()) != 0)
                {
                    CineFileSuiteDebug = true;
                }
            }
            if(LineHeader.compare("Sauvegarde") == 0)
            {

                LineHeader = "";
                Premier_Mot >> LineHeader;
                if(atoi(LineHeader.c_str()) != 0)
                {
                    Save_Place_Holder = true;
                }
            }
            if(LineHeader.compare("Log") == 0)
            {

                LineHeader = "";
                Premier_Mot >> LineHeader;
                if(atoi(LineHeader.c_str()) != 0)
                {
                    Log_File_Holder = true;
                }
            }
            LineHeader = "";

        }

        Config_File->close();

    }

    if(Log_File_Holder && SERVEUR && Save_Place_Holder)
    {
        qDebug() << "Configuration OK";
    }
    else
    {
        if(!Log_File_Holder)
        {
            qDebug() << "Pas d'option de configuration concernant la création d'un fichier LOG";
        }
        if(!CineFileSuiteDebug)
        {
            qDebug() << "Pas d'option de configuration concernant le debug";
        }
        if(!SERVEUR)
        {
            qDebug() << "Pas d'option de configuration concernant une liste de serveur";
        }
        if(!Save_Place_Holder)
        {
            qDebug() << "Pas d'option de configuration concernant la création d'un dossier de sauvegarde des nouvelles KDM triées";
        }

        qDebug() << "Mise en place de la configuration par défaut concernant les éléments manquant";
        Configuration_File_Modification();
    }

}

QWidget* Cine_File_Suite::Creation_Liste_Projecteur()
{
    qDebug() << "Création de la liste de projecteur";
    QWidget *Conteneur = new QWidget;
    QVBoxLayout *Conteneur_Holder = new QVBoxLayout;

    Scroll_Area_Serveur_Number = new QScrollArea;
    QWidget *Scroll_Conteneur = new QWidget(Scroll_Area_Serveur_Number);

    GridLayout = new QGridLayout;

    reset_Grid_Layout();


    if(Serveur_Number_Holder.size() != 0)
    {


        for(unsigned int i = 0; i < Serveur_Number_Holder.size() ; i++)
        {

            std::string Projecteur_Number = "Projecteur_" + QString::number(i+1).toStdString();
            qDebug() << Projecteur_Number.c_str() ;

            GridLayout->addWidget(new QLabel(Projecteur_Number.c_str()),i,0,Qt::AlignTop);

            Serveur_Number_Holder_Line_Edit.push_back(new QLineEdit(Serveur_Number_Holder.at(i)->c_str()));
            GridLayout->addWidget(Serveur_Number_Holder_Line_Edit.at(i),i,1,Qt::AlignTop);


        }

    }
    else
    {
           GridLayout->addWidget(new QLabel("Aucun numéro de serveur renseigné actuellement"),0,0,Qt::AlignTop);
    }




        Conteneur_Holder->addWidget(Scroll_Area_Serveur_Number);


        Scroll_Conteneur->setLayout(GridLayout);


        Scroll_Area_Serveur_Number->setWidget(Scroll_Conteneur);
        Scroll_Area_Serveur_Number->setWidgetResizable(true);


        Conteneur->setLayout(Conteneur_Holder);
    return Conteneur;
}

QWidget* Cine_File_Suite::Creation_Interface_Graphique()
{

    App_State = "KDM_MANAGER"; // Application par défaut
    Read_Configuration_File();

    QWidget *Conteneur = new QWidget();





    qDebug() << "Récupération des dimensions de l'écran" ;

    Fenetre_Principal_Widget->setGeometry(Point_X,Point_Y,Largeur_Fenetre,Hauteur_Fenetre);
    Fenetre_Principal_Widget->setWindowIcon(QPixmap(":/Images/Background"));
    Fenetre_Principal_Widget->setWindowTitle("Cine_File_Suite");
    //On perpare les layout avec en premier la  barre de menu pour ajouter pong

    Cine_file_suite_menuBar = new QMenuBar;

    Cine_file_suite_menu = Cine_file_suite_menuBar->addMenu("&Play");
    Jeu = new QAction("Jeu");

    Cine_file_suite_menu->addAction(Jeu);

    Cine_file_suite_menuBar->setMinimumSize(Largeur_Fenetre,20);
    Cine_file_suite_menuBar->setMaximumSize(Largeur_Fenetre,20);


    //puis les boutons

    qDebug() << "Préparation des différents layouts" ;
    Cine_File_Suite_App_Layout = new QHBoxLayout;

    qDebug() << "Création du bouton pour quitter" ;
    Cine_File_Suite_Quitter = new QToolButton;
    Cine_File_Suite_Quitter->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    Cine_File_Suite_Quitter->setIcon(QPixmap(":/Images/Logo_Quitter"));
    Cine_File_Suite_Quitter->setIconSize(QSize(75, 75));
    Cine_File_Suite_Quitter->setText("Quitter");
    Cine_File_Suite_Quitter->setAutoRaise(true);

    qDebug() << "Création du bouton pour les options" ;
    Cine_File_Suite_Option = new QToolButton;
    Cine_File_Suite_Option->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    Cine_File_Suite_Option->setIcon(QPixmap(":/Images/Logo_Parametre"));
    Cine_File_Suite_Option->setIconSize(QSize(75, 75));
    Cine_File_Suite_Option->setText("Option");
    Cine_File_Suite_Option->setAutoRaise(true);

    qDebug() << "Création du bouton pour les A propos de" ;
    Cine_File_Suite_Autre = new QToolButton;
    Cine_File_Suite_Autre->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    Cine_File_Suite_Autre->setIcon(QPixmap(":/Images/Logo_About"));
    Cine_File_Suite_Autre->setIconSize(QSize(75, 75));
    Cine_File_Suite_Autre->setText("A propos de :");
    Cine_File_Suite_Autre->setAutoRaise(true);



    qDebug() << "Création du bouton pour KDM_MANAGER" ;
    KDM_Manager_Launcher = new QToolButton;
    KDM_Manager_Launcher->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    KDM_Manager_Launcher->setIcon(QPixmap(":/Images/Logo_KDM_Manager"));
    KDM_Manager_Launcher->setIconSize(QSize(75, 75));
    KDM_Manager_Launcher->setText(KDM_MANAGER_VERSION);
    KDM_Manager_Launcher->setAutoRaise(true);


    qDebug() << "Création du bouton pour KDM_Lister" ;
    KDM_Lister_Launcher = new QToolButton;
    KDM_Lister_Launcher->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    KDM_Lister_Launcher->setIcon(QPixmap(":/Images/Logo_KDM_Lister"));
    KDM_Lister_Launcher->setIconSize(QSize(75, 75));
    KDM_Lister_Launcher->setText(KDM_LISTER_VERSION);
    KDM_Lister_Launcher->setAutoRaise(true);

    qDebug() << "Ajout des boutons au layout" ;
    Cine_File_Suite_App_Layout->addWidget(KDM_Manager_Launcher,Qt::AlignLeft);
    Cine_File_Suite_App_Layout->addWidget(KDM_Lister_Launcher,Qt::AlignLeft);
    Cine_File_Suite_App_Layout->addWidget(Cine_File_Suite_Option,Qt::AlignRight);
    Cine_File_Suite_App_Layout->addWidget(Cine_File_Suite_Autre,Qt::AlignRight);
    Cine_File_Suite_App_Layout->addWidget(Cine_File_Suite_Quitter,Qt::AlignRight);


    qDebug() << "Applications choisi par defaut est KDM_MANAGER" ;
    Cine_File_Suite_App_Selectionnee = new KDM_MANAGER(this->height()-30,this->width(),Save_Place_Holder,Log_File_Holder,CineFileSuiteDebug);

    qDebug() << "Création du layout complet" ;
    Cine_File_Suite_Layout = new QVBoxLayout(this);
    Cine_File_Suite_Layout->addWidget(Cine_file_suite_menuBar);
    Cine_File_Suite_Layout->addLayout(Cine_File_Suite_App_Layout);
    Cine_File_Suite_Layout->addWidget(Cine_File_Suite_App_Selectionnee);

    qDebug() << "Mise en place du layout" ;
    Conteneur->setLayout(Cine_File_Suite_Layout);

    connect(KDM_Manager_Launcher,SIGNAL(clicked()),this,SLOT(Handle_Button()));
    connect(KDM_Lister_Launcher,SIGNAL(clicked()),this,SLOT(Handle_Button()));
    connect(Cine_File_Suite_Option,SIGNAL(clicked()),this,SLOT(Handle_Button()));
    connect(Cine_File_Suite_Autre,SIGNAL(clicked()),this,SLOT(Handle_Button()));
    connect(Cine_File_Suite_Quitter,SIGNAL(clicked()),this,SLOT(Handle_Button()));

    connect(Jeu,SIGNAL(triggered(bool)),this,SLOT(Launch_Jeu()));

    Conteneur->setMinimumSize(Largeur_Fenetre,Hauteur_Fenetre);

    Fenetre_Principal_Widget->layout()->addWidget(Conteneur);

    return Conteneur;
}

QWidget* Cine_File_Suite::Creation_Fenetre_Option()
{

    QWidget *Conteneur = new QWidget;

    QHBoxLayout *Connection_Administrateur_Layout = new QHBoxLayout;

    QGroupBox *Connection_Administrateur_GroupBox = new QGroupBox("Gestion administrateur");

    Connection_Administrateur_GroupBox->setLayout(Connection_Administrateur_Layout);
    User_Name = new QLineEdit();
    User_Name->setMaximumWidth(100);

    Password = new QLineEdit();
    Password->setMaximumWidth(100);

    Security_Test = new QPushButton("Connection");
    Security_Test->setMaximumWidth(200);

    Connection_Administrateur_Layout->addWidget(new QLabel("Nom d'utilisateur :"),Qt::AlignCenter);
    Connection_Administrateur_Layout->addWidget(User_Name,Qt::AlignCenter);
    Connection_Administrateur_Layout->addWidget(new QLabel("Mot de passe :"),Qt::AlignCenter);
    Connection_Administrateur_Layout->addWidget(Password,Qt::AlignCenter);
    Connection_Administrateur_Layout->addWidget(Security_Test,Qt::AlignCenter);

    Connection_Administrateur_Layout->setSizeConstraint(QLayout::SetFixedSize);


    if(Is_Admin)
    {
        User_Name->setText(ADMIN_USER_NAME);
        Password->setText(ADMIN_PASSWORD);
        Security_Test->setEnabled(false);
    }




    QVBoxLayout *Vertical_Layout = new QVBoxLayout();
    QVBoxLayout *Serveur_Number_Holder_Layout = new QVBoxLayout;

    QVBoxLayout *Check_Box_Layout = new QVBoxLayout();


    QGroupBox *Check_Box_Holder = new QGroupBox("Option de sauvegarde et de fichier log :");
    QGroupBox *Numero_Serveur_Holder = new QGroupBox("Numéro de serveur :");

    Sauvegarde_Kdm = new QCheckBox("Création d'un dossier de sauvegarde");
    Sauvegarde_Kdm->setFont(QFont("Matura MT Script Capitals Normal",10));
    Sauvegarde_Kdm->setChecked(Save_Place_Holder);

    Fichier_Log = new QCheckBox("Création d'un fichier LOG");
    Fichier_Log->setFont(QFont("Matura MT Script Capitals Normal",10));
    Fichier_Log->setChecked(Log_File_Holder);

    Debug_handler = new QCheckBox("Gestion debug");
    Debug_handler->setFont(QFont("Matura MT Script Capitals Normal",10));
    Debug_handler->setChecked(CineFileSuiteDebug);


    Check_Box_Layout->addWidget(Sauvegarde_Kdm);
    Check_Box_Layout->addWidget(Fichier_Log);
    Check_Box_Layout->addWidget(Debug_handler);

    Check_Box_Holder->setLayout(Check_Box_Layout);

    QWidget *Creation_Liste_Projecteur_Holder = Creation_Liste_Projecteur();

    Serveur_Number_Holder_Layout->addWidget(Creation_Liste_Projecteur_Holder);

    if(Bouton_delete_holder.size()!= 0)
    {
        Bouton_delete_holder.clear();
    }

    for(unsigned int i = 0; i < Serveur_Number_Holder.size() ; i++)
    {
        Bouton_delete_holder.push_back(new QPushButton("Supprimer ce serveur"));
        GridLayout->addWidget(Bouton_delete_holder.at(i),i,2,Qt::AlignTop);
        QObject::connect(Bouton_delete_holder.at(i),SIGNAL(clicked()),this,SLOT(Delete_Serveur_Number()));
    }

    Numero_Serveur_Holder->setLayout(Serveur_Number_Holder_Layout);

    QPushButton *Bouton_Add_Serveur = new QPushButton;
    Bouton_Add_Serveur->setText("Ajouter un serveur");
    Bouton_Add_Serveur->setFont(QFont("Matura MT Script Capitals Normal",10,QFont::Bold));
    Bouton_Add_Serveur->setStyleSheet("border : 2px solid grey ;border-radius: 10px;padding : 5px;background-color: orange;");
    Bouton_Add_Serveur->setMinimumWidth(this->width());
    Bouton_Add_Serveur->setCursor(Qt::PointingHandCursor);



    QPushButton *Bouton_Ok = new QPushButton;
    Bouton_Ok->setText("Appliquer les modifications");
    Bouton_Ok->setFont(QFont("Matura MT Script Capitals Normal",10,QFont::Bold));
    Bouton_Ok->setStyleSheet("border : 2px solid grey ;border-radius: 10px;padding : 5px;background-color: orange;");
    Bouton_Ok->setMinimumWidth(this->width());
    Bouton_Ok->setEnabled(Is_change_made);
    Bouton_Ok->setCursor(Qt::PointingHandCursor);


    Vertical_Layout->addWidget(Connection_Administrateur_GroupBox);
    Vertical_Layout->addWidget(Check_Box_Holder);
    Vertical_Layout->addWidget(Numero_Serveur_Holder);
    Vertical_Layout->addWidget(Bouton_Add_Serveur);
    Vertical_Layout->addWidget(Bouton_Ok);
    Conteneur->setLayout(Vertical_Layout);

    Check_Box_Holder->setEnabled(Is_Admin);
    Numero_Serveur_Holder->setEnabled(Is_Admin);
    Bouton_Add_Serveur->setEnabled(Is_Admin);


    QObject::connect(Bouton_Ok,SIGNAL(clicked()),this,SLOT(Configuration_File_Modification()));
    QObject::connect(Bouton_Add_Serveur,SIGNAL(clicked()),this,SLOT(Add_Serveur_Number()));

    connect(Security_Test,SIGNAL(clicked()),this,SLOT(Handle_Button()));
    connect(Sauvegarde_Kdm,SIGNAL(clicked()),this,SLOT(Handle_Button()));
    connect(Fichier_Log,SIGNAL(clicked()),this,SLOT(Handle_Button()));


    return Conteneur ;
}

QWidget* Cine_File_Suite::Creation_Fenetre_Autre()
{
    QWidget *Conteneur = new QWidget;

    QVBoxLayout *Vertical_Layout = new QVBoxLayout();

    Vertical_Layout->addWidget(new QLabel("KDM_Manager et KDM_Lister sont des applications créés dans le but\n"
                                          "de simplifier le travail du projectionniste du circuit itinérant. \n\n"
                                          "KDM_Manager permet de pouvoir trier la totalité des KDMs\n"
                                          "par type de contenu et numéro de serveur. \n\n"
                                          "KDM_Lister permet de lister la totalité des KDMs présente sur le TMS\n\n"
                                          "Support technique : \n\ncinefile.kdmmanager@gmail.com \n\n\n"
                                          "Ce logiciel à été écrit par Oiselet Alain ,\n"
                                          "Pour faire valoir ce que de droit.\n\n"),0,Qt::AlignCenter);


    Conteneur->setLayout(Vertical_Layout);

    Conteneur->setStyleSheet("font-size : 14px;");





    return Conteneur ;
}



void Cine_File_Suite::Configuration_File_Modification()
{
    qDebug() << "Modification de la configuration de CINE_FILE_SUITE";

    std::ofstream *Config_File;

    Config_File = new std::ofstream;
    Config_File->open(FichierConfiguration);

    if(Config_File)
    {
        if(Save_Place_Holder)
        {
            *Config_File << "Sauvegarde 1" << std::endl;
        }
        else
        {
            *Config_File << "Sauvegarde 0" << std::endl;
        }

        if(Log_File_Holder)
        {
            *Config_File << "Log 1" << std::endl;
        }
        else
        {
            *Config_File << "Log 0" << std::endl;
        }

        if(CineFileSuiteDebug)
        {
            *Config_File << "Debug 1" << std::endl;
        }
        else
        {
            *Config_File << "Debug 0" << std::endl;
        }

        for(unsigned int i = 0 ; i < Serveur_Number_Holder_Line_Edit.size();i++)
        {
            QString Info = "Serveur ";
            Info.append(Serveur_Number_Holder_Line_Edit.at(i)->text());
            *Config_File << Info.toStdString() << std::endl;
        }


    }
    else
    {
        qDebug() << "Le fichier ne peut être créé";
    }

    Config_File->close();
    Is_change_made = false;

    if(App_State.compare("OPTION") == 0)
    {
        if(Cine_File_Suite_App_Selectionnee != nullptr)
        {
            delete Cine_File_Suite_App_Selectionnee ;
            Cine_File_Suite_App_Selectionnee = new QWidget;
        }
        Is_change_made = false;

        Cine_File_Suite_App_Selectionnee = Creation_Fenetre_Option() ;
        Cine_File_Suite_Layout->addWidget(Cine_File_Suite_App_Selectionnee);
    }

}

void Cine_File_Suite::Launch_Jeu()
{

    QWidget *Game = new class Game();
    Game->show();
    Cine_File_Suite_App_Selectionnee->setEnabled(false);
}


void Cine_File_Suite::reset_Grid_Layout()
{
    if(Serveur_Number_Holder_Line_Edit.size() != 0)
    {
        Serveur_Number_Holder_Line_Edit.clear();
    }
    if(GridLayout != nullptr)
    {
        qDebug() << GridLayout->rowCount() << " " << GridLayout->columnCount() ;
        for(int i = 0 ; i < GridLayout->rowCount() ; i++)
        {
            for(int j = 0 ; j < GridLayout->columnCount() ; j++)
            {
                QLayoutItem *Widget_Item = GridLayout->itemAtPosition(i,j);


                if(Widget_Item != nullptr)
                {
                    Widget_Item->widget()->hide();

                }
            }
        }

    }



}

void Cine_File_Suite::Delete_Serveur_Number()
{
    std::vector <std::string *> To_Copie;

    for(unsigned int i = 0 ; i < Serveur_Number_Holder.size() ; i++)
    {

        if(QObject::sender() != Bouton_delete_holder.at(i))
        {
           To_Copie.push_back(new std::string(*Serveur_Number_Holder.at(i)));
        }

    }

    Serveur_Number_Holder.clear();
    Serveur_Number_Holder_Line_Edit.clear();

    for(unsigned int i = 0 ; i < To_Copie.size() ; i++)
    {

           Serveur_Number_Holder.push_back(new std::string(*To_Copie.at(i)));

    }
    if(Cine_File_Suite_App_Selectionnee != nullptr)
    {
        delete Cine_File_Suite_App_Selectionnee ;
        Cine_File_Suite_App_Selectionnee = new QWidget;
    }

    Is_change_made = true;
    Cine_File_Suite_App_Selectionnee = Creation_Fenetre_Option() ;
    Cine_File_Suite_Layout->addWidget(Cine_File_Suite_App_Selectionnee);
}

void Cine_File_Suite::Add_Serveur_Number()
{
    Serveur_Number_Holder_Line_Edit.push_back(new QLineEdit("XXXXXX"));
    Serveur_Number_Holder.push_back(new std::string("XXXXXX"));

    if(Cine_File_Suite_App_Selectionnee != nullptr)
    {
        delete Cine_File_Suite_App_Selectionnee ;
        Cine_File_Suite_App_Selectionnee = new QWidget;
    }

    Is_change_made = true;
    Cine_File_Suite_App_Selectionnee = Creation_Fenetre_Option() ;
    Cine_File_Suite_Layout->addWidget(Cine_File_Suite_App_Selectionnee);
}

void Cine_File_Suite::Handle_Button()
{

    /****************************************** Gestion pour la configuration ******************************************/

    //Gestion des boutons suivant et precedent au cours de la configuration du logiciel
    if(QObject::sender() == Cine_File_Suite_Configuration_Bouton_Suivant)
    {
        Place_In_The_Configuration++;
        if(Place_In_The_Configuration > 5)
        {
            Place_In_The_Configuration = 5;
        }

        qDebug() << Place_In_The_Configuration ;
        switch (Place_In_The_Configuration)
        {
            case 0:
            Cine_File_Suite_App_Selectionnee->hide();
            Cine_File_Suite_App_Selectionnee = Creation_Configuration_0();
            Cine_File_Suite_App_Selectionnee->show();
                break;
            case 1:
            Cine_File_Suite_App_Selectionnee->hide();
            Cine_File_Suite_App_Selectionnee = Creation_Configuration_1();
            Cine_File_Suite_App_Selectionnee->show();
                break;
            case 2:
            Cine_File_Suite_App_Selectionnee->hide();
            Cine_File_Suite_App_Selectionnee = Creation_Configuration_2();
            Cine_File_Suite_App_Selectionnee->show();
                break;
            case 3:
            Cine_File_Suite_App_Selectionnee->hide();
            Cine_File_Suite_App_Selectionnee = Creation_Configuration_3();
            Cine_File_Suite_App_Selectionnee->show();
                break;
            case 4:
            Cine_File_Suite_App_Selectionnee->hide();
            Cine_File_Suite_App_Selectionnee = Creation_Configuration_4();
            Cine_File_Suite_App_Selectionnee->show();
                break;
            case 5:
            Cine_File_Suite_App_Selectionnee->hide();
            delete Cine_File_Suite_App_Selectionnee;
            Fenetre_Principal_Widget->close();
            Configuration_File_Modification();
            qApp->quit();
                break;


        }
    }

    if(QObject::sender() == Cine_File_Suite_Configuration_Bouton_Precedent)
    {
        Place_In_The_Configuration--;
        if(Place_In_The_Configuration < 0)
        {
            Place_In_The_Configuration = 0;
        }
        switch (Place_In_The_Configuration)
        {
            case 0:
            Cine_File_Suite_App_Selectionnee->hide();
            Cine_File_Suite_App_Selectionnee = Creation_Configuration_0();
            Cine_File_Suite_App_Selectionnee->show();
                break;
            case 1:
            Cine_File_Suite_App_Selectionnee->hide();
            Cine_File_Suite_App_Selectionnee = Creation_Configuration_1();
            Cine_File_Suite_App_Selectionnee->show();
                break;
            case 2:
            Cine_File_Suite_App_Selectionnee->hide();
            Cine_File_Suite_App_Selectionnee = Creation_Configuration_2();
            Cine_File_Suite_App_Selectionnee->show();
                break;
            case 3:
            Cine_File_Suite_App_Selectionnee->hide();
            Cine_File_Suite_App_Selectionnee = Creation_Configuration_3();
            Cine_File_Suite_App_Selectionnee->show();
                break;
            case 4:
            Cine_File_Suite_App_Selectionnee->hide();
            Cine_File_Suite_App_Selectionnee = Creation_Configuration_4();
            Cine_File_Suite_App_Selectionnee->show();
                break;


        }
    }

    //Gestion du systeme de mise à jour du gridlayout lorsqu'on change le nombre de projecteur dans la configuration

    if(QObject::sender() == Projecteur_Number_Holder_LineEdit)
    {

        //On récupère le nombre de projecteur
        Cine_File_Suite_App_Selectionnee->hide();
        Temp_Serveur_Number_Holder = Projecteur_Number_Holder_LineEdit->text().toInt();




        if(Temp_Serveur_Number_Holder == 0)
        {

            Cine_File_Suite_App_Selectionnee = Creation_Configuration_2();

            Cine_File_Suite_Configuration_Bouton_Suivant->setEnabled(false);
        }
        else
        {

            if(Serveur_Number_Holder.size() != 0)
            {
               Serveur_Number_Holder.clear();
            }

            for(int i = 0 ; i < Temp_Serveur_Number_Holder ;i++)
            {
                Serveur_Number_Holder.push_back(new std::string("XXXXXX"));

            }

            Cine_File_Suite_App_Selectionnee = Creation_Configuration_2();


            Cine_File_Suite_Configuration_Bouton_Suivant->setEnabled(true);

        }

        Cine_File_Suite_App_Selectionnee->show();

    }

    //On gère les cases à cocher pour les options

    if(QObject::sender() == Fichier_Log_Configuration)
    {
        if(Fichier_Log_Configuration->checkState() == Qt::Checked)
        {
            Log_File_Holder = true;
            qDebug() << "Check";
        }
        if(Fichier_Log_Configuration->checkState() == Qt::Unchecked)
        {
            Log_File_Holder = false;
            qDebug() << "UnCheck";
        }

    }

    if(QObject::sender() == Debug_handler)
    {
        if(Fichier_Log_Configuration->checkState() == Qt::Checked)
        {
            CineFileSuiteDebug = true;
            qDebug() << "Check";
        }
        if(Fichier_Log_Configuration->checkState() == Qt::Unchecked)
        {
            CineFileSuiteDebug = false;
            qDebug() << "UnCheck";
        }

    }

    if(QObject::sender() == Sauvegarde_kdm_Configuration)
    {
        if(Sauvegarde_kdm_Configuration->checkState() == Qt::Checked)
        {
            Save_Place_Holder = true ;
            qDebug() << "Check";
        }
        if(Sauvegarde_kdm_Configuration->checkState() == Qt::Unchecked)
        {
            Save_Place_Holder = false ;
            qDebug() << "UnCheck";
        }
    }

    /****************************************** Gestions des SLOT pour l'application principal *********************************/


    //A chaque changement d'application, on mets à false le bouton "Appliquer les modifications" de la fenêtre OPTION


    if(QObject::sender() == KDM_Manager_Launcher && App_State.compare("KDM_MANAGER") != 0)
    {
        if(Cine_File_Suite_App_Selectionnee != nullptr)
        {
            delete Cine_File_Suite_App_Selectionnee ;
            Cine_File_Suite_App_Selectionnee = new QWidget;
        }
        Is_change_made = false;
        Is_Admin = false;

        Cine_File_Suite_App_Selectionnee = new KDM_MANAGER(Fenetre_Principal_Widget->height(),Fenetre_Principal_Widget->width(),Sauvegarde_Kdm,Fichier_Log,CineFileSuiteDebug) ;
        Cine_File_Suite_Layout->addWidget(Cine_File_Suite_App_Selectionnee);
        App_State = "KDM_MANAGER";
    }

    if(QObject::sender() == KDM_Lister_Launcher && App_State.compare("KDM_LISTER") != 0)
    {
        if(Cine_File_Suite_App_Selectionnee != nullptr)
        {
            delete Cine_File_Suite_App_Selectionnee ;
            Cine_File_Suite_App_Selectionnee = new QWidget;
        }
        Is_change_made = false;
        Is_Admin = false;
        Cine_File_Suite_App_Selectionnee = new KDM_Lister(Fenetre_Principal_Widget) ;
        Cine_File_Suite_Layout->addWidget(Cine_File_Suite_App_Selectionnee);
        App_State = "KDM_LISTER";
    }

    if(QObject::sender() == Cine_File_Suite_Option && App_State.compare("OPTION") != 0)
    {
        if(Cine_File_Suite_App_Selectionnee != nullptr)
        {
            delete Cine_File_Suite_App_Selectionnee ;
            Cine_File_Suite_App_Selectionnee = new QWidget;
        }
        Is_change_made = false;
        Is_Admin = false;

        Cine_File_Suite_App_Selectionnee = Creation_Fenetre_Option() ;
        Cine_File_Suite_Layout->addWidget(Cine_File_Suite_App_Selectionnee);
        App_State = "OPTION";
    }

    if(QObject::sender() == Security_Test)
    {
        if(User_Name->text().compare(ADMIN_USER_NAME) == 0 && Password->text().compare(ADMIN_PASSWORD) == 0)
        {
            qDebug() << "Connection de l'administrateur réussi";
            Is_Admin = true;
        }

        if(Cine_File_Suite_App_Selectionnee != nullptr)
        {
            delete Cine_File_Suite_App_Selectionnee ;
            Cine_File_Suite_App_Selectionnee = new QWidget;
        }
        Is_change_made = false;

        Cine_File_Suite_App_Selectionnee = Creation_Fenetre_Option() ;
        Cine_File_Suite_Layout->addWidget(Cine_File_Suite_App_Selectionnee);
        App_State = "OPTION";

    }

    if(QObject::sender() == Cine_File_Suite_Autre && App_State.compare("AUTRES") != 0)
    {
        if(Cine_File_Suite_App_Selectionnee != nullptr)
        {
            delete Cine_File_Suite_App_Selectionnee ;
            Cine_File_Suite_App_Selectionnee = new QWidget;
        }
        Is_change_made = false;
        Is_Admin = false;
        Cine_File_Suite_App_Selectionnee = Creation_Fenetre_Autre() ;
        Cine_File_Suite_Layout->addWidget(Cine_File_Suite_App_Selectionnee);
        App_State = "AUTRES";
    }

    //Gestion des cases a cocher dans les OPTION
    if(QObject::sender() == Fichier_Log)
    {
        if(!Is_change_made)
        {
            Is_change_made = true;
        }
        if(Fichier_Log->checkState() == Qt::Checked)
        {
            Log_File_Holder = true;
            qDebug() << "Check";
        }
        if(Fichier_Log->checkState() == Qt::Unchecked)
        {
            Log_File_Holder = false;
            qDebug() << "UnCheck";
        }

        if(Cine_File_Suite_App_Selectionnee != nullptr)
        {
            delete Cine_File_Suite_App_Selectionnee ;
            Cine_File_Suite_App_Selectionnee = new QWidget;
        }

        Cine_File_Suite_App_Selectionnee = Creation_Fenetre_Option() ;
        Cine_File_Suite_Layout->addWidget(Cine_File_Suite_App_Selectionnee);

    }
    if(QObject::sender() == Sauvegarde_Kdm)
    {
        if(!Is_change_made)
        {
            Is_change_made = true;
        }
        if(Sauvegarde_Kdm->checkState() == Qt::Checked)
        {
            Save_Place_Holder = true ;
            qDebug() << "Check";
        }
        if(Sauvegarde_Kdm->checkState() == Qt::Unchecked)
        {
            Save_Place_Holder = false ;
            qDebug() << "UnCheck";
        }

        if(Cine_File_Suite_App_Selectionnee != nullptr)
        {
            delete Cine_File_Suite_App_Selectionnee ;
            Cine_File_Suite_App_Selectionnee = new QWidget;
        }

        Cine_File_Suite_App_Selectionnee = Creation_Fenetre_Option() ;
        Cine_File_Suite_Layout->addWidget(Cine_File_Suite_App_Selectionnee);
    }

    if(QObject::sender() == Cine_File_Suite_Quitter)
    {
        Cine_File_Suite_App_Selectionnee = nullptr;
        qApp->quit();
    }

}


/********************************************** Partie configuration ************************************/

QWidget *Cine_File_Suite::Creation_Configuration_0()
{
    // Un texte de bienvenue

    Fenetre_Principal_Widget->setGeometry(Point_X,Point_Y,Largeur_Fenetre,Hauteur_Fenetre);

    QWidget *Conteneur = new QWidget(Fenetre_Principal_Widget);
    QVBoxLayout *Conteneur_Layout = new QVBoxLayout;

    QHBoxLayout *Bouton_Layout = new QHBoxLayout;
    QHBoxLayout *Title_And_Logo_Holder = new QHBoxLayout;
    QLabel *Icone_CFS = new QLabel;
    Icone_CFS->setPixmap(QPixmap(":/Images/Background"));
    Icone_CFS->setMaximumSize(128,128);


    Cine_File_Suite_Configuration_Bouton_Precedent = new QPushButton("Précédent");
    Cine_File_Suite_Configuration_Bouton_Suivant = new QPushButton("Suivant");

    Title_And_Logo_Holder->addWidget(new QLabel("Configuration de Cine_File_Suite"),0,Qt::AlignCenter);
    Title_And_Logo_Holder->addWidget(Icone_CFS);


    Conteneur_Layout->addLayout(Title_And_Logo_Holder);
    Conteneur_Layout->addWidget(new QLabel("     Cine_File_Suite est un ensemble de logiciel.\n\n"
                                           "     KDM_MANAGER vous permettra de trier vos KDM.\n"
                                           "     Il se chargera de supprimer les KDMs qui ne sont plus valide,\n"
                                           "     de trier vos nouvelles KDMs et de supprimer les dossiers vide.\n\n\n"
                                           "     KDM_Lister vous permettra de lister vos KDM par numéro de serveur, \n"
                                           "     ainsi que d'obtenir la dite liste en format HTML.\n\n\n"),0,Qt::AlignCenter);




    Bouton_Layout->addWidget(Cine_File_Suite_Configuration_Bouton_Precedent,1,Qt::AlignRight);
    Bouton_Layout->addWidget(Cine_File_Suite_Configuration_Bouton_Suivant,1,Qt::AlignRight);

    Cine_File_Suite_Configuration_Bouton_Precedent->hide();
    Cine_File_Suite_Configuration_Bouton_Suivant->setMaximumWidth(100);
    Cine_File_Suite_Configuration_Bouton_Precedent->setMaximumWidth(100);

    Conteneur_Layout->addLayout(Bouton_Layout,Qt::AlignRight);


    Conteneur->setStyleSheet("font-size : 18px;");
    Conteneur->setMinimumSize(Largeur_Fenetre,Hauteur_Fenetre);
    Conteneur->setMaximumSize(Largeur_Fenetre,Hauteur_Fenetre);

    Conteneur->setLayout(Conteneur_Layout);

    connect(Cine_File_Suite_Configuration_Bouton_Suivant,SIGNAL(clicked()),this,SLOT(Handle_Button()));


    return Conteneur;
}
QWidget *Cine_File_Suite::Creation_Configuration_1()
{
    //Choix de sauvegarde et de log

    QWidget *Conteneur = new QWidget(Fenetre_Principal_Widget);
    QVBoxLayout *Conteneur_Layout = new QVBoxLayout;

    QHBoxLayout *Bouton_Layout = new QHBoxLayout;

    Fenetre_Principal_Widget->setGeometry(Point_X,Point_Y,Largeur_Fenetre,Hauteur_Fenetre);

    Sauvegarde_kdm_Configuration =  new QCheckBox("Souhaitez-vous sauvegarder vos KDMs en plus de les triées?");
    Fichier_Log_Configuration = new QCheckBox("Souhaitez-vous créer un fichier LOG ?");

    QHBoxLayout *Title_And_Logo_Holder = new QHBoxLayout;
    QLabel *Icone_CFS = new QLabel;
    Icone_CFS->setPixmap(QPixmap(":/Images/Background"));
    Icone_CFS->setMaximumSize(128,128);


    Cine_File_Suite_Configuration_Bouton_Precedent = new QPushButton("Précédent");
    Cine_File_Suite_Configuration_Bouton_Suivant = new QPushButton("Suivant");

    Title_And_Logo_Holder->addWidget(new QLabel("Configuration de Cine_File_Suite"),0,Qt::AlignCenter);
    Title_And_Logo_Holder->addWidget(Icone_CFS);


    Conteneur_Layout->addLayout(Title_And_Logo_Holder);
    Conteneur_Layout->addWidget(Sauvegarde_kdm_Configuration,0,Qt::AlignLeft);
    Conteneur_Layout->addWidget(Fichier_Log_Configuration,0,Qt::AlignLeft);

    Bouton_Layout->addWidget(Cine_File_Suite_Configuration_Bouton_Precedent,1,Qt::AlignRight);
    Bouton_Layout->addWidget(Cine_File_Suite_Configuration_Bouton_Suivant,1,Qt::AlignRight);

    Conteneur_Layout->addLayout(Bouton_Layout);

    Cine_File_Suite_Configuration_Bouton_Precedent->show();
    Cine_File_Suite_Configuration_Bouton_Suivant->setEnabled(true);

    connect(Sauvegarde_kdm_Configuration,SIGNAL(clicked()),this,SLOT(Handle_Button()));
    connect(Fichier_Log_Configuration,SIGNAL(clicked()),this,SLOT(Handle_Button()));

    connect(Cine_File_Suite_Configuration_Bouton_Suivant,SIGNAL(clicked()),this,SLOT(Handle_Button()));
    connect(Cine_File_Suite_Configuration_Bouton_Precedent,SIGNAL(clicked()),this,SLOT(Handle_Button()));

    Conteneur->setStyleSheet("font-size : 18px;");
    Conteneur->setMinimumSize(Largeur_Fenetre,Hauteur_Fenetre);
    Conteneur->setMaximumSize(Largeur_Fenetre,Hauteur_Fenetre);

    Conteneur->setLayout(Conteneur_Layout);

    return Conteneur;
}


QWidget *Cine_File_Suite::Creation_Configuration_2()
{
    //Remplir la liste de projecteur

    QWidget *Conteneur = new QWidget(Fenetre_Principal_Widget);
    QVBoxLayout *Conteneur_Layout = new QVBoxLayout;

    QHBoxLayout *Bouton_Layout = new QHBoxLayout;

    Projecteur_Number_Holder_LineEdit = new QLineEdit;

    Fenetre_Principal_Widget->setGeometry(Point_X,Point_Y,Largeur_Fenetre,Hauteur_Fenetre);

    Cine_File_Suite_Configuration_Bouton_Precedent = new QPushButton("Précédent");
    Cine_File_Suite_Configuration_Bouton_Suivant = new QPushButton("Suivant");

    QHBoxLayout *Projecteur_Number_Holder = new QHBoxLayout;
    Projecteur_Number_Holder->addWidget(new QLabel("Combien avez vous de projecteur? (Appuyer sur entrée pour confirmer)   "),0,Qt::AlignLeft);
    Projecteur_Number_Holder->addWidget(Projecteur_Number_Holder_LineEdit,0,Qt::AlignLeft);
    Projecteur_Number_Holder->setAlignment(Qt::AlignLeft);

    Projecteur_Number_Holder_LineEdit->setMaximumWidth(75);
    Projecteur_Number_Holder_LineEdit->setText(QString::number(Temp_Serveur_Number_Holder));

    Projecteur_Number_Holder->setSpacing(10);

    Conteneur_Layout->addWidget(new QLabel("Configuration de Cine_File_Suite\n"),0,Qt::AlignCenter);
    Conteneur_Layout->addLayout(Projecteur_Number_Holder);
    Conteneur_Layout->addWidget(Creation_Liste_Projecteur());

    Bouton_Layout->addWidget(Cine_File_Suite_Configuration_Bouton_Precedent,1,Qt::AlignRight);
    Bouton_Layout->addWidget(Cine_File_Suite_Configuration_Bouton_Suivant,1,Qt::AlignRight);

    Conteneur_Layout->addLayout(Bouton_Layout);

    Cine_File_Suite_Configuration_Bouton_Suivant->setEnabled(false);



    Conteneur->setLayout(Conteneur_Layout);

    connect(Projecteur_Number_Holder_LineEdit,SIGNAL(editingFinished()),this,SLOT(Handle_Button()));
    connect(Cine_File_Suite_Configuration_Bouton_Suivant,SIGNAL(clicked()),this,SLOT(Handle_Button()));
    connect(Cine_File_Suite_Configuration_Bouton_Precedent,SIGNAL(clicked()),this,SLOT(Handle_Button()));

    Conteneur->setStyleSheet("font-size : 18px;");
    Conteneur->setMinimumSize(Largeur_Fenetre,Hauteur_Fenetre);
    return Conteneur;
}
QWidget *Cine_File_Suite::Creation_Configuration_3()
{
    //Résumer des choix et de la liste de projecteur
    QWidget *Conteneur = new QWidget(Fenetre_Principal_Widget);
    QVBoxLayout *Conteneur_Layout = new QVBoxLayout;

    QHBoxLayout *Bouton_Layout = new QHBoxLayout;

    Fenetre_Principal_Widget->setGeometry(Point_X,Point_Y,Largeur_Fenetre,Hauteur_Fenetre);

    QHBoxLayout *Title_And_Logo_Holder = new QHBoxLayout;
    QLabel *Icone_CFS = new QLabel;
    Icone_CFS->setPixmap(QPixmap(":/Images/Background"));
    Icone_CFS->setMaximumSize(128,128);


    Cine_File_Suite_Configuration_Bouton_Precedent = new QPushButton("Précédent");
    Cine_File_Suite_Configuration_Bouton_Suivant = new QPushButton("Suivant");

    Title_And_Logo_Holder->addWidget(new QLabel("Configuration de Cine_File_Suite"),0,Qt::AlignCenter);
    Title_And_Logo_Holder->addWidget(Icone_CFS);


    Conteneur_Layout->addLayout(Title_And_Logo_Holder);

    if(Save_Place_Holder)
    {
        Conteneur_Layout->addWidget(new QLabel("Vous avez décidé de sauvegarder vos nouvelles KDM dans un dossier.\n"));
    }
    if(Log_File_Holder)
    {
        Conteneur_Layout->addWidget(new QLabel("Vous avez décider d'avoir un fichier Log.\n"));
    }

    Conteneur_Layout->addWidget(new QLabel("Vous avez entrer " + QString::number(Serveur_Number_Holder_Line_Edit.size()) + " numéro de serveur.\n"));

    for(unsigned int i = 0 ; i < Serveur_Number_Holder.size() ;i++)
    {
        Conteneur_Layout->addWidget(new QLabel("Projecteur " + QString::number(i +1 ) + " : " + Serveur_Number_Holder_Line_Edit.at(i)->text()));
    }



    Bouton_Layout->addWidget(Cine_File_Suite_Configuration_Bouton_Precedent,1,Qt::AlignRight);
    Bouton_Layout->addWidget(Cine_File_Suite_Configuration_Bouton_Suivant,1,Qt::AlignRight);

    Conteneur_Layout->addLayout(Bouton_Layout);



    Conteneur->setLayout(Conteneur_Layout);

    connect(Cine_File_Suite_Configuration_Bouton_Suivant,SIGNAL(clicked()),this,SLOT(Handle_Button()));
    connect(Cine_File_Suite_Configuration_Bouton_Precedent,SIGNAL(clicked()),this,SLOT(Handle_Button()));
    Conteneur->setStyleSheet("font-size : 18px;");
    Conteneur->setMinimumSize(Largeur_Fenetre,Hauteur_Fenetre);

    return Conteneur;
}
QWidget *Cine_File_Suite::Creation_Configuration_4()
{
    // Remerciement et fin
    QWidget *Conteneur = new QWidget(Fenetre_Principal_Widget);
    QVBoxLayout *Conteneur_Layout = new QVBoxLayout;

    QHBoxLayout *Bouton_Layout = new QHBoxLayout;

    Fenetre_Principal_Widget->setGeometry(Point_X,Point_Y,Largeur_Fenetre,Hauteur_Fenetre);

    QHBoxLayout *Title_And_Logo_Holder = new QHBoxLayout;
    QLabel *Icone_CFS = new QLabel;
    Icone_CFS->setPixmap(QPixmap(":/Images/Background"));
    Icone_CFS->setMaximumSize(128,128);


    Cine_File_Suite_Configuration_Bouton_Precedent = new QPushButton("Précédent");
    Cine_File_Suite_Configuration_Bouton_Suivant = new QPushButton("Terminer");

    Title_And_Logo_Holder->addWidget(new QLabel("Configuration de Cine_File_Suite"),0,Qt::AlignCenter);
    Title_And_Logo_Holder->addWidget(Icone_CFS);


    Conteneur_Layout->addLayout(Title_And_Logo_Holder);
    Conteneur_Layout->addWidget(new QLabel("Merci d'avoir configuré CINE_FILE_SUITE.\n\n"
                                           "Afin de terminer cette configuration, merci de relancer CINE_FILE_SUITE.exe"),0,Qt::AlignLeft);




    Bouton_Layout->addWidget(Cine_File_Suite_Configuration_Bouton_Precedent,1,Qt::AlignRight);
    Bouton_Layout->addWidget(Cine_File_Suite_Configuration_Bouton_Suivant,1,Qt::AlignRight);


    Conteneur_Layout->addLayout(Bouton_Layout);

    Conteneur->setLayout(Conteneur_Layout);

    connect(Cine_File_Suite_Configuration_Bouton_Suivant,SIGNAL(clicked()),this,SLOT(Handle_Button()));
    connect(Cine_File_Suite_Configuration_Bouton_Precedent,SIGNAL(clicked()),this,SLOT(Handle_Button()));

    Conteneur->setStyleSheet("font-size : 18px;");
    Conteneur->setMinimumSize(Largeur_Fenetre,Hauteur_Fenetre);
    return Conteneur;
}

void Cine_File_Suite::keyPressEvent(QKeyEvent *Event)
{
    if(Event->key() == Qt::Key_P)
    {
        std::cout << "Let's play !" << std::endl;
    }
}
