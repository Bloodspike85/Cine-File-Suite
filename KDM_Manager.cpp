#include "KDM_Manager.h"
#include "QScreen"
#include "QTime"

KDM_MANAGER::KDM_MANAGER(int Hauteur_Fenetre,int Largeur_Fenetre, bool Save_Activation,bool Log_Activation, bool m_debug):QWidget()
{

    Is_Sauvegarde_Activated = Save_Activation;
    IS_Log_Activated = Log_Activation ;
    Is_Debug_handler_Activated = m_debug;

    Cmb_KDM_Effacer = 0;
    Cmb_KDM_Sauvegarder = 0;
    Cmb_KDM_copier = 0;

    Cmb_Dossier_Effacer = 0;


    this->Largeur_Fenetre = Largeur_Fenetre;
    this->Hauteur_Fenetre = Hauteur_Fenetre;


    Fenetre_Actuelle = new QWidget;
    Fenetre_Holder = new QVBoxLayout;
    Fenetre_Actuelle = Creation_Interface_Graphique();
    Fenetre_Holder->addWidget(Fenetre_Actuelle);
    this->setLayout(Fenetre_Holder);

    QDir Path_Folder_Name ;
    Folder_Path = new std::string(QCoreApplication::applicationDirPath().toStdString());

    qDebug() << Folder_Path->c_str() ;

    connect(Timer,SIGNAL(timeout()),this,SLOT(tick()));


}
KDM_MANAGER::~KDM_MANAGER()
{


        qDebug() << "Suppresion de KDM_MANAGER" ;

        qDebug() << "Suppresion de text info" ;

        if(!Text_Info.empty())
        {

            Text_Info.clear();

        }



        qDebug() << "Suppresion de Info_Holder" ;
        if(Info_Holder != nullptr)
        {
            Info_Holder = nullptr;
            delete Info_Holder;
        }

        qDebug() << "Suppresion de Scroll_Info" ;
        if(Scroll_info != nullptr)
        {
            Scroll_info = nullptr;
            delete Scroll_info;
        }

        qDebug() << "Suppresion de Info_Layout" ;
        if(Info_Layout_Holder != nullptr)
        {
            Info_Layout_Holder = nullptr ;
            delete Info_Layout_Holder;
        }

        qDebug() << "Suppresion de m_Progress_Bar" ;
        if(m_Progress_Bar != nullptr)
        {
            m_Progress_Bar = nullptr;
            delete m_Progress_Bar;
        }

        qDebug() << "Suppresion de Kdm_Trier" ;
        if(Kdm_Trier != nullptr)
        {
            Kdm_Trier = nullptr;
            delete Kdm_Trier;
        }

        if(Kdm_Manager_Bouton != nullptr)
        {
            qDebug() << "Suppresion de Kdm_Manager_Bouton" ;
            Kdm_Manager_Bouton = nullptr;
            delete Kdm_Manager_Bouton ;
        }

        if(Kdm_Manager_Layout != nullptr)
        {
            qDebug() << "Suppresion de Kdm_Manager_Layout" ;
            Kdm_Manager_Layout = nullptr;
            delete Kdm_Manager_Layout;
        }


        qDebug() << "Suppresion de DirRep" ;
        if(DirRep != nullptr)
        {
            DirRep = nullptr;
            delete DirRep;
        }

        if(Fenetre_Actuelle != nullptr)
        {
            qDebug() << "Suppresion de Fenetre_Actuelle" ;
            Fenetre_Actuelle = nullptr;
            delete Fenetre_Actuelle;
        }
        if(Fenetre_Holder != nullptr)
        {
            qDebug() << "Suppresion de Frame_Holder" ;
            Fenetre_Holder = nullptr ;
            delete Fenetre_Holder;
        }

        qDebug() << "Suppresion de KDM_MANAGER OK " ;



}

void KDM_MANAGER::Ajouter_Un_TexteInfo(std::string Texte)
{
    std::cout << Texte << std::endl;
    try
    {
        if(Text_Info.empty())
        {
            Text_Info.push_back(new QLabel);
            Text_Info[0]->setText(Texte.c_str());
            Text_Info[0]->setStyleSheet("Background-color : transparent ; color : green;");
            Text_Info[0]->setFont(QFont("Matura MT Script Capitals Normal",10,QFont::Bold));
            Info_Layout_Holder->addWidget(Text_Info[0]);
        }
        else
        {
            Text_Info.push_back(new QLabel);
            Text_Info[Text_Info.size()-1]->setText(Texte.c_str());
            Text_Info[Text_Info.size()-1]->setStyleSheet("Background-color : transparent ; color : green;");
            Text_Info[Text_Info.size()-1]->setFont(QFont("Matura MT Script Capitals Normal",10,QFont::Bold));
            Info_Layout_Holder->addWidget(Text_Info[Text_Info.size()-1]);
        }

        Scroll_info->verticalScrollBar()->setValue(Scroll_info->verticalScrollBar()->maximum());
        qApp->processEvents();
    }
    catch (const std::bad_alloc &)
    {
        std::cout << "ERREUR : Ajout du texte => " + Texte + " IMPOSSIBLE" << std::endl;
    }


}



QWidget* KDM_MANAGER::Creation_Interface_Graphique()
{

    QWidget *Conteneur = new QWidget;

    InitiateAll();
    QLabel *Date = new QLabel();


    Date->setText(QDate::currentDate().toString("dddd dd MMMM yyyy" ));
    Date->setAlignment(Qt::AlignRight);
    Date->setStyleSheet("font-size:12px;");



    m_Progress_Bar = new QProgressBar;
    m_Progress_Bar->setTextVisible(true);
    m_Progress_Bar->setValue(0);
    m_Progress_Bar->setAlignment(Qt::AlignCenter);
    m_Progress_Bar->setFormat(QString("Aucune action en cours"));

    Kdm_Manager_Layout = new QVBoxLayout;
    Kdm_Manager_Bouton_And_CheckBox_Holder = new QHBoxLayout;
    Kdm_Manager_Layout->addWidget(Date);

    Info_Layout_Holder = new QVBoxLayout; //Layout info

    //Disposition des éléments sur la fenetre//

    //Création du Bouton//
    Kdm_Manager_Bouton = new QToolButton;

    Kdm_Manager_Bouton->setCursor(Qt::PointingHandCursor);
    Kdm_Manager_Bouton->setStyleSheet("border : 2px solid grey ;border-radius: 10px;padding : 5px;background-color: orange;");

    Kdm_Manager_Bouton->setMinimumSize(Largeur_Fenetre / 2,50);
    Kdm_Manager_Bouton->setMaximumSize(Largeur_Fenetre / 2,50);
    Kdm_Manager_Bouton->setText("Trie des KDMs");


    Kdm_Manager_Bouton_And_CheckBox_Holder->addWidget(Kdm_Manager_Bouton);
    Kdm_Manager_Layout->addLayout(Kdm_Manager_Bouton_And_CheckBox_Holder);


    Info_Holder = new QLabel;
    Info_Holder->setStyleSheet("Background-color : black;");

    Scroll_info = new QScrollArea();
    Kdm_Manager_Layout->addWidget(Scroll_info);
    Scroll_info->setStyleSheet("background-color : black;");
    Scroll_info->size().setWidth(Largeur_Fenetre/2);

/***************************************************************************************************************************************/


    Ajouter_Un_TexteInfo("Configuration de KDM_MANAGER en cours ...");
    Ajouter_Un_TexteInfo("Configuration de KDM_MANAGER : OK");
    Ajouter_Un_TexteInfo("Configuration de KDM_LISTER en cours ...");
    Ajouter_Un_TexteInfo("Configuration de KDM_LISTER : OK");
    Ajouter_Un_TexteInfo("Démarrage de KDM_MANAGER");
    Ajouter_Un_TexteInfo(std::to_string(int(FileReader->getNumber_of_file())) + " fichiers seront traités ...");
    Ajouter_Un_TexteInfo("Démarrage de KDM_LISTER");

/*****************************************************************************************************************************************/

    Info_Holder->setLayout(Info_Layout_Holder);
    Info_Layout_Holder->setSizeConstraint(QLayout::SetFixedSize);
    Scroll_info->setWidget(Info_Holder);

    Kdm_Manager_Layout->addWidget(m_Progress_Bar);



   m_Progress_Bar->setStyleSheet("QProgressBar {font-size : 12px; border : 2px solid black ;border-radius : 10px; background-color : lightblue ;padding: 2px;}"
                                 "QProgressBar:chunk { background: orange;margin-right : 2px; width: 10px;}");



     connect(Kdm_Manager_Bouton,SIGNAL(clicked()),this,SLOT(Gestion_Bouton()));




     Conteneur->setLayout(Kdm_Manager_Layout);


     return Conteneur;


}

QWidget* KDM_MANAGER::Creation_Interface_Graphique_Resultat()
{

    Timer->stop();
    QWidget *Conteneur = new QWidget;

    QVBoxLayout *Vertical_Layout = new QVBoxLayout;

    std::string Dossier_eff ;
    std::string KDM_Dep ;
    std::string KDM_Eff ;
    std::string KDM_Copier ;

    std::ostringstream oss;
    std::ostringstream oss1;
    std::ostringstream oss2;
    std::ostringstream oss3;

    oss1 << Cmb_KDM_copier;

    if(Cmb_KDM_copier > 0)
    {
       KDM_Copier = "J'ai copié " + oss1.str() + " KDMS \n";
    }
    else
    {
        KDM_Copier = "J'ai copié " + oss1.str() + " KDM \n";
    }

    oss2 << Cmb_KDM_Effacer;

    if(Cmb_KDM_Effacer > 0)
    {
       KDM_Eff = "J'ai effacé " + oss2.str() + " KDMS \n";
    }
    else
    {
        KDM_Eff = "J'ai effacé " + oss2.str() + " KDM \n";
    }

    oss3 << Cmb_KDM_Sauvegarder;

    if(Cmb_KDM_Sauvegarder > 0)
    {
       KDM_Dep = "J'ai sauvegardé " + oss3.str() + " KDMS \n";
    }
    else
    {
        KDM_Dep = "J'ai sauvegardé " + oss3.str() + " KDM \n";
    }

    oss << Cmb_Dossier_Effacer;

    if(Cmb_Dossier_Effacer > 0)
    {
       Dossier_eff = "J'ai supprimé " + oss.str() + " dossiers \n";
    }
    else
    {
        Dossier_eff = "J'ai supprimé " + oss.str() + " dossier \n";
    }



    std::string Texte = ("Action 1 : Vérification de la date de validité des KDMS         \n "
                         + KDM_Eff +
                         "Vérification terminée.\n\n"

                         "Action 2 : Copie des KDMS\n"
                         + KDM_Copier + KDM_Dep +
                         "Copie terminée.\n\n"

                         "Action 3 : Suppression des dossiers vides\n"
                         + Dossier_eff +
                         "Suppression terminée.\n\n"

                         "Merci d'avoir utilisé KDM_MANAGER.\n\n");


    QString T = Texte.c_str();


    QScrollArea *Scroll_Area = new QScrollArea();
    Scroll_Area->setWidget(Get_Resultat());
    Scroll_Area->size().setWidth(Get_Resultat()->size().width());
    Scroll_Area->setStyleSheet("background-color : black ;");

    KDM_Manager_return_back = new QPushButton("<-");
    KDM_Manager_return_back->setMaximumWidth(this->width() / 4);

    Kdm_Trier = new QHBoxLayout();
    Kdm_Trier->addWidget(new QLabel(T),0,Qt::AlignCenter);
    Kdm_Trier->addWidget(Scroll_Area);
    Kdm_Trier->setSpacing(10);



    Vertical_Layout->addWidget(KDM_Manager_return_back);
    Vertical_Layout->addLayout(Kdm_Trier);



    int PointX,PointY;

    PointX = (QApplication::primaryScreen()->availableGeometry().width()/2)-(Conteneur->size().width()/2);
    PointY = (QApplication::primaryScreen()->availableGeometry().height()/2)-(Conteneur->size().height()/2);
    Conteneur->move(PointX,PointY);

    if(m_Progress_Bar != nullptr)
    {
        m_Progress_Bar = new QProgressBar;
        m_Progress_Bar->setTextVisible(true);
    }
    else
    {
        delete m_Progress_Bar;
    }


    Conteneur->setLayout(Vertical_Layout);





    if(IS_Log_Activated)
    {
        Creation_Log();
    }


    connect(KDM_Manager_return_back,SIGNAL(clicked()),this,SLOT(Gestion_Bouton()));

    return Conteneur ;


}

void KDM_MANAGER::EffaceDossierVide()
{

    Ajouter_Un_TexteInfo("Suppression des dossiers vide ...");
    j=0;
    Wait::sleep(1);
    DirRep->Read_Directory_To_Delete_Empty_Folder(Folder_Path,this);



    if(Cmb_Dossier_Effacer == 0)
    {
        Ajouter_Un_TexteInfo("Aucun dossier vide à supprimer.");
    }

}

void KDM_MANAGER::TriKDM()
{
    Ajouter_Un_TexteInfo("Copies des KDMs en cours ...");
    Wait::sleep(1);
    DirRep->Read_Directory_To_Check_New_KDM(Folder_Path, this);

    if(Cmb_KDM_copier == 0)
    {
        Ajouter_Un_TexteInfo("Aucune KDM copiée");
    }

    Ajouter_Un_TexteInfo("Suppression des KDM obsolètes ...");
    Wait::sleep(1);
    DirRep->Read_Directory_To_Check_Validity(Folder_Path, this);
    if(Cmb_KDM_Effacer == 0)
    {
        Ajouter_Un_TexteInfo("Aucune KDM à supprimer.");
    }

}
void KDM_MANAGER::InitiateAll()
{
    DirRep = new Directory();
    FileReader = new fichiers();

    Timer = new QTimer(this);
    Timer->setInterval(10);


    Today = kdm::CurrentDateAndTime();

    Total_File_Number = FileReader->getNumber_of_file();
    Total_file_readed = 0 ;

}
void KDM_MANAGER::LaunchApp()
{


Timer->start();
    Ajouter_Un_TexteInfo("Initialisation du système en cours ...");
    Ajouter_Un_TexteInfo("Vérification de la date ...");


    InitiateAll();




    Ajouter_Un_TexteInfo(Today);


    j = 0;

    logiciel.Jour = kdm::DateMoisEtJour(Today.c_str(), 0);
    logiciel.Mois = kdm::DateMoisEtJour(Today.c_str(), 3);
    logiciel.Annee = kdm::DateAnnee(Today.c_str(), 6);


    if(Is_Sauvegarde_Activated)
    {
        QDir Sauvegarde_Directory("./Sauvegarde_KDM");
        if(Sauvegarde_Directory.exists() == false)
        {
            Ajouter_Un_TexteInfo("Création du dossier de sauvegarde de KDMS ...");
            Wait::sleep(1);
            if(Sauvegarde_Directory.mkdir("./Sauvegarde_KDM"))
            {
              Ajouter_Un_TexteInfo("Création du dossier de sauvegarde de KDMS OK");
            }
        }
    }

    m_Progress_Bar->setTextVisible(true);




    Ajouter_Un_TexteInfo("Préparation des fichiers en cours ...");




   TriKDM();
   EffaceDossierVide();
    Timer->stop();



    if(Fenetre_Actuelle != nullptr)
    {
        delete Fenetre_Actuelle;

        Fenetre_Actuelle = new QWidget;
    }




   Fenetre_Actuelle = Creation_Interface_Graphique_Resultat();
   Fenetre_Holder->addWidget(Fenetre_Actuelle);





}

void KDM_MANAGER::Creation_Log()
{

    std::ofstream Fichier_Log;

    if(m_Nouvelle_KDM.size() == 0 && Get_KDM_Supprimer_Size() == 0 && Get_Dossier_Supprimer_Size() == 0)
    {
        return;
    }
    else
    {
      Fichier_Log.open("App_Log.txt",std::ios::app);
    }

    Fichier_Log << "Le " << QDate::currentDate().toString("dddd dd MMMM yyyy").toStdString() << std::endl;

    if(!m_Nouvelle_KDM.empty())
    {
        for(unsigned int i = 0;i < m_Nouvelle_KDM.size()-1;i++)
        {
            Fichier_Log << "Nouvelle KDM triée pour le contenu : " << m_Nouvelle_KDM[i]->c_str() << std::endl;
        }
    }
    if(Get_KDM_Supprimer_Size() != 0)
    {
        for(unsigned int i = 0;i < Get_KDM_Supprimer_Size() - 1;i++)
        {
            Fichier_Log << "KDM supprimée : " << Get_Element_KDM_Supprimer(i).c_str() << std::endl;
        }
    }
    if(Get_Dossier_Supprimer_Size() != 0)
    {
        for(unsigned int i = 0;i < Get_Dossier_Supprimer_Size() - 1;i++)
        {
            Fichier_Log << "Dossier supprimé : " << Get_Element_Dossier_Supprimer(i).c_str() << std::endl;
        }
    }



    Fichier_Log.close();

    return;


}

QWidget* KDM_MANAGER::Get_Resultat()
{


    QWidget *Conteneur;
    Conteneur = new QWidget;
    Conteneur->setStyleSheet("background-color : black ;");

    std::vector<QLabel*> Zone_de_texte;

    QVBoxLayout *Layout;
    Layout = new QVBoxLayout(Conteneur);

    int nombre_de_label = 0;

    if(Get_KDM_Arrivant_A_Expiration_Size() == 0)
    {
        Zone_de_texte.push_back(new QLabel);

        Zone_de_texte[nombre_de_label]->setText("Aucune KDM arrive a expiration dans les 3 prochains jours.");
        Zone_de_texte[nombre_de_label]->setStyleSheet("color : white ;");
        Zone_de_texte[nombre_de_label]->setFont(QFont("MS Sans Serif Normal",10));

        Layout->addWidget(Zone_de_texte[nombre_de_label]);
        nombre_de_label++;
    }
    else
    {
        for(unsigned int i = 0; i < Get_KDM_Arrivant_A_Expiration_Size() ; i++)
        {
           Zone_de_texte.push_back(new QLabel);
           Zone_de_texte[nombre_de_label]->setText(Get_Element_KDM_Arrivant_A_Expiration(i).c_str());
           Zone_de_texte[nombre_de_label]->setStyleSheet("color : orange ;");
           Zone_de_texte[nombre_de_label]->setFont(QFont("MS Sans Serif Normal",10));

           Layout->addWidget(Zone_de_texte[nombre_de_label]);
           nombre_de_label++;
        }

    }

    if(Get_Nouvelle_KDM_Size() == 0)
    {
        Zone_de_texte.push_back(new QLabel);

        Zone_de_texte[nombre_de_label]->setText("Aucune nouvelle KDM.");
        Zone_de_texte[nombre_de_label]->setStyleSheet("color : white ;");
        Zone_de_texte[nombre_de_label]->setFont(QFont("MS Sans Serif Normal",10));

        Layout->addWidget(Zone_de_texte[nombre_de_label]);
        nombre_de_label++;
    }
    else
    {
        for(unsigned int i = 0; i < Get_Nouvelle_KDM_Size() ; i++)
        {
           Zone_de_texte.push_back(new QLabel);
           std::string texte = "Nouvelle KDM : " + Get_Nouvelle_KDM(i) ;
           Zone_de_texte[nombre_de_label]->setText(texte.c_str());
           Zone_de_texte[nombre_de_label]->setStyleSheet("color : green ;");
           Zone_de_texte[nombre_de_label]->setFont(QFont("MS Sans Serif Normal",10));

           Layout->addWidget(Zone_de_texte[nombre_de_label]);
           nombre_de_label++;
        }

    }

    if(Get_Dossier_Supprimer_Size() == 0)
    {
        Zone_de_texte.push_back(new QLabel);

        Zone_de_texte[nombre_de_label]->setText("Aucun dossier supprimé.");
        Zone_de_texte[nombre_de_label]->setStyleSheet("color : white ;");
        Zone_de_texte[nombre_de_label]->setFont(QFont("MS Sans Serif Normal",10));

        Layout->addWidget(Zone_de_texte[nombre_de_label]);
        nombre_de_label++;
    }
    else
    {
        for(unsigned int i = 0; i < Get_Dossier_Supprimer_Size() ; i++)
        {
           Zone_de_texte.push_back(new QLabel);
           Zone_de_texte[nombre_de_label]->setText(Get_Element_Dossier_Supprimer(i).c_str());
           Zone_de_texte[nombre_de_label]->setStyleSheet("color : red ;");
           Zone_de_texte[nombre_de_label]->setFont(QFont("MS Sans Serif Normal",10));

           Layout->addWidget(Zone_de_texte[nombre_de_label]);
           nombre_de_label++;
        }

    }


    //pour le debug des erreur si l'utilisateur le souhaite

    if(Get_Debug_State())
    {
        if(Get_erreur_handler_Size() == 0)
        {
            Zone_de_texte.push_back(new QLabel);

            Zone_de_texte[nombre_de_label]->setText("Aucune erreur.");
            Zone_de_texte[nombre_de_label]->setStyleSheet("color : blue ;");
            Zone_de_texte[nombre_de_label]->setFont(QFont("MS Sans Serif Normal",10));

            Layout->addWidget(Zone_de_texte[nombre_de_label]);
            nombre_de_label++;
        }
        else
        {
            for(unsigned int i = 0; i < Get_erreur_handler_Size() ; i++)
            {
               Zone_de_texte.push_back(new QLabel);
               Zone_de_texte[nombre_de_label]->setText(Get_erreur_handler(i).c_str());
               Zone_de_texte[nombre_de_label]->setStyleSheet("color : blue ;");
               Zone_de_texte[nombre_de_label]->setFont(QFont("MS Sans Serif Normal",10));

               Layout->addWidget(Zone_de_texte[nombre_de_label]);
               nombre_de_label++;
            }

        }
    }




    return Conteneur;

}



void KDM_MANAGER::Gestion_Bouton()
{

    if(QObject::sender() == Kdm_Manager_Bouton)
    {

        LaunchApp();

    }
    if(QObject::sender() == KDM_Manager_return_back)
    {

        delete Fenetre_Actuelle;
        Dossier_Supprimer.clear();
        m_Nouvelle_KDM.clear();
        KDM_Supprimer.clear();
        Kdm_Arrivant_A_Expiration.clear();


        Fenetre_Actuelle = Creation_Interface_Graphique();


        Fenetre_Holder->addWidget(Fenetre_Actuelle);

    }
}

void KDM_MANAGER::tick()
{

    QString percent_state = "";
    percent_state.clear();


   if(Total_file_readed > 0 && (Total_file_readed != (Total_File_Number*2)))
    {
       double Numb = (Total_file_readed/(Total_File_Number*2)) ;
        Numb = Numb * 100;



        if(m_Progress_Bar != NULL && Numb < 100)
        {
            m_Progress_Bar->setValue(Numb);
            percent_state = QString::number(Numb) + "%";
            m_Progress_Bar->setFormat(percent_state);
        }

    }


}

unsigned int KDM_MANAGER::getTotal_file_readed()
{
    return Total_file_readed;
}

void KDM_MANAGER::setTotal_file_readed(unsigned int newTotal_file_readed)
{
    Total_file_readed = newTotal_file_readed;
}


void KDM_MANAGER::Erreur_Log(std::string Erreur_string)
{

    std::ofstream Erreur_Log;


    Erreur_Log.open("Erreur_Log.txt",std::ios::app);

    if(Erreur_Log)
    {
       Erreur_Log << "Le " << QDate::currentDate().toString("dddd dd MMMM yyyy").toStdString() << std::endl;
       Erreur_Log << "ERREUR :  " << Erreur_string << std::endl;
    }






    Erreur_Log.close();

    return;


}





