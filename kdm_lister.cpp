/*TODO
* Modifier l'affichage dans le fichier HTML (tout aparait en orange
* Modifier le code HTML avec du JS?









*/



#include "kdm_lister.h"
#include "QTime"



KDM_Lister::KDM_Lister(QWidget *Fenetre_Principal):QWidget()
{
    std::cout << "***********************" << std::endl;
    std::cout << "Création de KDM LISTER " << std::endl;
    std::cout << "***********************" << std::endl;


    Aujourdhui = "";
    Date_Fin_De_Validite = false;


    Fenetre_Principal->layout()->addWidget(Creation_Interface_Graphique());

}



KDM_Lister::~KDM_Lister()
{

    qDebug() << "Suppression de KDM LISTER ... \n";
    if(m_Kdm_Lister.size() > 0)
    {
        m_Kdm_Lister.clear();
        //TODO destruct a structure
        //delete &m_Kdm_Lister;

    }
    if(Box != nullptr)delete Box;


    if(Imprimer != nullptr)delete Imprimer;
    if(QuitApp != nullptr)delete QuitApp;
    if(ListerFichier != nullptr)delete ListerFichier;
    if(Liste_Menu != nullptr)delete Liste_Menu;


    if(Actualiser_Liste != nullptr)delete Actualiser_Liste;
    if(Quitter != nullptr)delete Quitter;


    if(Grille != nullptr)delete Grille;

    if(Liste != nullptr)delete Liste;


    if(M_Scroller != nullptr)delete M_Scroller;

    if(Verticale_Layout != nullptr)delete Verticale_Layout;


   qDebug() << "Suppression de KDM LISTER OK \n";


}

QWidget* KDM_Lister::Creation_Interface_Graphique()
{

    QWidget *Conteneur = new QWidget();


    Verticale_Layout = new QVBoxLayout;



    Horizontal_Layout = new QHBoxLayout;

    Liste_Menu = new QMenuBar;

    ListerFichier = Liste_Menu->addMenu("&Fichier");
    Imprimer = new QAction("Imprimer");
    QuitApp = new QAction("Quitter");
    ListerFichier->addAction(Imprimer);
    ListerFichier->addAction(QuitApp);

    M_Scroller = new QScrollArea;
    M_Scroller->setVisible(true);

    std::string *Folder_Path = new std::string(QCoreApplication::applicationDirPath().toStdString());
    Lister_Les_KDM(Folder_Path);


    Liste = new QWidget;
    Liste = Creer_Liste();
    M_Scroller->setWidget(Liste);

    Imprimer_Liste = new QPushButton("Imprimer la liste");
    Imprimer_Liste->setFont(QFont("Matura MT Script Capitals Normal",10,QFont::Bold));
    Imprimer_Liste->setStyleSheet("border : 2px solid grey ;border-radius: 10px;padding : 5px;background-color: orange;");

    Actualiser_Liste = new QPushButton("Actualiser la liste");
    Actualiser_Liste->setFont(QFont("Matura MT Script Capitals Normal",10,QFont::Bold));
    Actualiser_Liste->setStyleSheet("border : 2px solid grey ;border-radius: 10px;padding : 5px;background-color: orange;");

    Quitter = new QPushButton("Quitter");
    Quitter->setFont(QFont("Matura MT Script Capitals Normal",10,QFont::Bold));
    Quitter->setStyleSheet("border : 2px solid grey ;border-radius: 10px;padding : 5px;background-color: orange;");

    Verticale_Layout->addWidget(Liste_Menu);
    Verticale_Layout->addWidget(M_Scroller);

    Horizontal_Layout->addWidget(Imprimer_Liste);
    Horizontal_Layout->addWidget(Actualiser_Liste);
    Horizontal_Layout->addWidget(Quitter);

    Verticale_Layout->addLayout(Horizontal_Layout);


    connect(Imprimer,SIGNAL(triggered(bool)),this,SLOT(Impression()));
    connect(QuitApp,SIGNAL(triggered(bool)),qApp,SLOT(quit()));
    connect(Imprimer_Liste,SIGNAL(clicked()),this,SLOT(Impression()));
    connect(Actualiser_Liste,SIGNAL(clicked()),this,SLOT(Actualiser()));
    connect(Quitter,SIGNAL(clicked()),qApp,SLOT(quit()));

    setLayout(Verticale_Layout);

    return Conteneur;
}

void KDM_Lister::Ajouter_KDM(std::string A,std::string B,std::string C,std::string D,int E,bool F)
{
    std::cout << A <<" "<< B <<" "<< C <<" "<< D << std::endl;
    m_Kdm_Lister.push_back(new Base_de_donnee(A,B,C,D,E,F));
}

QWidget* KDM_Lister::Creer_Liste()
{  

#define DEBUT_TABLEAU "background-color : #5d8aa8 ; color : white ;border : 2px solid black; padding : 10px; text-align : center ;font-size : 14px;"
#define INTERIEUR_TABLEAU "border : 2px solid black;background-color : white ;padding : 10px; text-align : center ;font-size : 14px;"
#define INTERIEUR_TABLEAU_PROCHE_FIN_DE_VALIDITE_ORANGE "background-color : #d2691e ; border : 2px solid black; padding : 10px; text-align : center ;font-size : 14px;"
#define INTERIEUR_TABLEAU_PROCHE_FIN_DE_VALIDITE_ROUGE "background-color : #ff4040 ; border : 2px solid black; padding : 10px; text-align : center ;font-size : 14px;"

    std::cout << "Création de la liste" << std::endl;

    QWidget *Conteneur;
    Conteneur = new QWidget;

    unsigned int Nombre_De_Projecteur = ProjecteurCheck::GetActiveServeurNumber();

    //std::cout << ProjecteurCheck::GetActiveServeurNumber() << std::endl;

    if(Nombre_De_Projecteur > 0)
    {



        Conteneur->setStyleSheet("background-color : white;");

        std::vector < std::vector < QLabel * > > Base_Element;

        std::vector < QLabel * > Temp_Element;

        for(unsigned int i =0;i< Nombre_De_Projecteur ;i++)
        {

            if(!Temp_Element.empty())
            {
                Temp_Element.clear();
            }

            for(unsigned int j =0;j < 4;j++)
            {
                Temp_Element.push_back(new QLabel);
                Temp_Element[j]->setAlignment(Qt::AlignCenter);
                Temp_Element[j]->setStyleSheet("border-style: outset;border-width: 0.5px;border-color: black;");
                Temp_Element[j]->setFont(QFont("Matura MT Script Capitals Normal",10));
            }

            Base_Element.push_back(Temp_Element);



        }


        std::vector < std::vector < QLabel * > > KDM_Lister_Label;
        std::vector < QLabel * > Temp_KDM_Lister_Label;

        for(unsigned int i = 0 ; i< m_Kdm_Lister.size();i++)
        {
            if(!Temp_KDM_Lister_Label.empty())
            {
                Temp_KDM_Lister_Label.clear();
            }

            for(unsigned int j =0;j< 4;j++)
            {
              Temp_KDM_Lister_Label.push_back(new QLabel());
              Temp_KDM_Lister_Label[j]->setAlignment(Qt::AlignCenter);
              Temp_KDM_Lister_Label[j]->setStyleSheet("border-style: outset;border-width: 0.5px;border-color: black;");
              Temp_KDM_Lister_Label[j]->setFont(QFont("Matura MT Script Capitals Normal",10));

            }


            KDM_Lister_Label.push_back(Temp_KDM_Lister_Label);


        }




        Grille = new QGridLayout(Conteneur);
        Grille->setSpacing(0);
        unsigned int placement = 0;


        for(unsigned int i =0;i< Nombre_De_Projecteur ;i++)
        {

                Base_Element[i][0]->setText("     Nom Contenu    ");
                Base_Element[i][1]->setText("     Projecteur    ");
                Base_Element[i][2]->setText("  Debut de validité ");
                Base_Element[i][3]->setText("   Fin de validité  ");
                Base_Element[i][0]->setStyleSheet(DEBUT_TABLEAU);
                Base_Element[i][1]->setStyleSheet(DEBUT_TABLEAU);
                Base_Element[i][2]->setStyleSheet(DEBUT_TABLEAU);
                Base_Element[i][3]->setStyleSheet(DEBUT_TABLEAU);
                if(i !=0)
                {
                    placement = (i*6);
                }
                else
                {
                    placement = 0;
                }
                Grille->addWidget(Base_Element[i][0],0,int(placement) );
                Grille->addWidget(Base_Element[i][1],0,int(placement) + 1);
                Grille->addWidget(Base_Element[i][2],0,int(placement) + 2);
                Grille->addWidget(Base_Element[i][3],0,int(placement) + 3);
                Grille->addWidget(new QLabel,0,int(placement) + 4);


        }


        //On laisse un espace entre 3 et 5//


        int Place = 1;
        int numprojecteur = 0;



        std::cout << m_Kdm_Lister.size() << std::endl;

        for(unsigned int i = 0 ; i< m_Kdm_Lister.size();i++)
        {

            if(i != 0)
            {
                if(m_Kdm_Lister[i]->Num_Projecteur != m_Kdm_Lister[i - 1]->Num_Projecteur )
                {

                    numprojecteur++;
                    Place = 1;
                }
            }
            KDM_Lister_Label[i][0]->setText(m_Kdm_Lister[i]->Nom_du_Film.c_str());
            KDM_Lister_Label[i][1]->setText(m_Kdm_Lister[i]->Num_Projecteur.c_str());
            KDM_Lister_Label[i][2]->setText(m_Kdm_Lister[i]->Date_debut_validite.c_str());
            KDM_Lister_Label[i][3]->setText(m_Kdm_Lister[i]->Date_Fin_Validite.c_str());

            if(m_Kdm_Lister[i]->Approche_De_La_Fin_De_Validite == true)
            {
                if(m_Kdm_Lister[i]->Jour_restant_de_validite >= 3 && m_Kdm_Lister[i]->Jour_restant_de_validite <= 5)
                {
                    KDM_Lister_Label[i][0]->setStyleSheet(INTERIEUR_TABLEAU_PROCHE_FIN_DE_VALIDITE_ORANGE);
                    KDM_Lister_Label[i][1]->setStyleSheet(INTERIEUR_TABLEAU_PROCHE_FIN_DE_VALIDITE_ORANGE);
                    KDM_Lister_Label[i][2]->setStyleSheet(INTERIEUR_TABLEAU_PROCHE_FIN_DE_VALIDITE_ORANGE);
                    KDM_Lister_Label[i][3]->setStyleSheet(INTERIEUR_TABLEAU_PROCHE_FIN_DE_VALIDITE_ORANGE);
                }
                else if(m_Kdm_Lister[i]->Jour_restant_de_validite >= 0 && m_Kdm_Lister[i]->Jour_restant_de_validite <= 3)
                {
                    KDM_Lister_Label[i][0]->setStyleSheet(INTERIEUR_TABLEAU_PROCHE_FIN_DE_VALIDITE_ROUGE);
                    KDM_Lister_Label[i][1]->setStyleSheet(INTERIEUR_TABLEAU_PROCHE_FIN_DE_VALIDITE_ROUGE);
                    KDM_Lister_Label[i][2]->setStyleSheet(INTERIEUR_TABLEAU_PROCHE_FIN_DE_VALIDITE_ROUGE);
                    KDM_Lister_Label[i][3]->setStyleSheet(INTERIEUR_TABLEAU_PROCHE_FIN_DE_VALIDITE_ROUGE);
                }
                else
                {
                    KDM_Lister_Label[i][0]->setStyleSheet(INTERIEUR_TABLEAU);
                    KDM_Lister_Label[i][1]->setStyleSheet(INTERIEUR_TABLEAU);
                    KDM_Lister_Label[i][2]->setStyleSheet(INTERIEUR_TABLEAU);
                    KDM_Lister_Label[i][3]->setStyleSheet(INTERIEUR_TABLEAU);
                }
            }




            Grille->addWidget(KDM_Lister_Label[i][0],Place,numprojecteur * 6);
            Grille->addWidget(KDM_Lister_Label[i][1],Place,(numprojecteur * 6)+1);
            Grille->addWidget(KDM_Lister_Label[i][2],Place,(numprojecteur * 6)+2);
            Grille->addWidget(KDM_Lister_Label[i][3],Place,(numprojecteur * 6)+3);

            Place++;
        }

        return Conteneur;
    }
    else
    {
        Grille = new QGridLayout;
        Grille->addWidget(new QLabel("Aucune KDM trouvée."));
        Conteneur->setLayout(Grille);
    }



 return Conteneur;
}

void KDM_Lister::Lister_Les_KDM(std::string *Nom_Dossier)
{

    std::vector <std::string*> File_handler = Directory::Get_Content_Of_Folder(Nom_Dossier);



        Aujourdhui = kdm::CurrentDateAndTime();
        Logi.Jour = kdm::DateMoisEtJour(Aujourdhui.c_str(), 0);
        Logi.Mois = kdm::DateMoisEtJour(Aujourdhui.c_str(), 3);
        Logi.Annee = kdm::DateAnnee(Aujourdhui.c_str(), 6);

        if(File_handler.empty())
        {
            std::cout << "ERROR file handler vide" << std::endl;
        }
        else
        {
            for(unsigned int i = 0; i < File_handler.size() ;i++)
            {

                //std::cout << "file handler : " << *File_handler[i]<< std::endl;

                if(File_handler[i]->compare(".") == 0 || File_handler[i]->compare("..") == 0 || File_handler[i]->compare("Sauvegarde_KDM") == 0)
                {
                    continue;
                }

                if(File_handler[i]->find('.') != std::string::npos) // C'est un fichier//
                {

                    std::string Nouveau_Fichier = *File_handler[i];

                    std::string Chemin_Fichier;

                    Chemin_Fichier = *Nom_Dossier + PathSeparator + *File_handler[i];


                    if(Nouveau_Fichier.find(".xml") != std::string::npos && kdm::Verification_Of_Integrity_Of_KDM(Chemin_Fichier))
                    {
                        if(kdm::Get_Movie_Name(Chemin_Fichier) != "ERREUR" && kdm::Get_Start_Validity_Date(Chemin_Fichier) != "ERREUR" &&
                           kdm::Get_End_Validity_Date(Chemin_Fichier) != "ERREUR" && kdm::Get_Server_Number(Chemin_Fichier) != "ERREUR" &&
                           kdm::CheckDate(kdm::Get_End_Validity_Date(Chemin_Fichier),kdm::CurrentDateAndTime()) && kdm::Get_Server_Number(Chemin_Fichier) != "INCONNU")
                        {

                           std::cout << "OK" << std::endl;
                           Ajouter_KDM((kdm::Get_Movie_Name(Chemin_Fichier) + "_" + kdm::Get_Movie_Language(Chemin_Fichier) + "_" + kdm::Get_Movie_Audio(Chemin_Fichier)),
                                       (kdm::Get_Projecteur_Name(kdm::Get_Server_Number(Chemin_Fichier)) + "(" + kdm::Get_Server_Number(Chemin_Fichier) + ")"),
                                       kdm::EnglishDate_To_FrenchDate(kdm::Get_Start_Validity_Date(Chemin_Fichier)),
                                       kdm::EnglishDate_To_FrenchDate(kdm::Get_End_Validity_Date(Chemin_Fichier)),
                                       kdm::Get_Diff_Time(kdm::Get_End_Validity_Date(Chemin_Fichier),kdm::CurrentDateAndTime()),
                                       kdm::CheckDate(kdm::Get_End_Validity_Date(Chemin_Fichier),kdm::CurrentDateAndTime()));
                        }
                        else
                        {
                            std::cout << "NOPE" << std::endl;
                            continue;
                        }
                    }


                }
                if(File_handler[i]->find('.') == std::string::npos) //C'est un dossier
                {
                    std::string *Nouveau_Nom_Repertoire = new std::string(*Nom_Dossier + PathSeparator + *File_handler[i]);


                    Lister_Les_KDM(Nouveau_Nom_Repertoire);

                }
            }

        }




}


void KDM_Lister::Impression()
{

#define HTML_DEBUT_TABLEAU "<td style=\"background-color : #5d8aa8 ; color : white ;border : 2px solid black; padding : 10px; text-align : center ;font-size : 14px;\">"
#define HTML_INTERIEUR_TABLEAU "<td style=\"border : 2px solid black;background-color : white ;padding : 10px; text-align : center ;font-size : 14px;\">"
#define HTML_INTERIEUR_TABLEAU_PROCHE_FIN_DE_VALIDITE_ORANGE "<td style=\" background-color : #d2691e ; border : 2px solid black; padding : 10px; text-align : center ;font-size : 14px;\">"
#define HTML_INTERIEUR_TABLEAU_PROCHE_FIN_DE_VALIDITE_ROUGE "<td style=\" background-color : #ff4040 ; border : 2px solid black; padding : 10px; text-align : center ;font-size : 14px;\">"

    std::ofstream Impression_Liste;
    std::remove("Liste_de_KDM.html");
    Impression_Liste.open("Liste_de_KDM.html");

    if(!Impression_Liste.is_open())
    {
        std::cout << "Erreur de creation de la liste." << std::endl;
        Box = new Message_Box("Erreur","Erreur lors de la creation du fichier",10,ON);
        Box->show();
    }
    else
    {
        Impression_Liste << "<!DOCTYPE html>" << std::endl;
        Impression_Liste << "<html>" << std::endl;
        Impression_Liste << "<head>" << std::endl;
        Impression_Liste << "<meta charset=\"utf-8\"/>" << std::endl;
        Impression_Liste << "<title> Liste KDM </title>" << std::endl;
        Impression_Liste << "</head>" << std::endl;
        Impression_Liste << "<body>" << std::endl;


        Impression_Liste << " <h1> Relevé des KDM du " << QDate::currentDate().toString(" dddd dd MMMM yyyy ").toStdString() << QTime::currentTime().toString("'à 'hh:mm:ss").toStdString() << "</h1>" << std::endl;


        Impression_Liste << "<table>"
                            "<tr>"
                             << HTML_DEBUT_TABLEAU << "Nom du contenu</td>"
                             << HTML_DEBUT_TABLEAU << "Numero du projecteur</td>"
                             << HTML_DEBUT_TABLEAU << "Date de debut de validite</td>"
                             << HTML_DEBUT_TABLEAU << "Date de fin de validite</td> "
                            "</tr>"
                            << std::endl;
        if(m_Kdm_Lister.size() > 0 )
        {
            for(unsigned int i =0; i < m_Kdm_Lister.size();i++)
            {
                if(i != 0)
                {
                    if(m_Kdm_Lister[i]->Num_Projecteur != m_Kdm_Lister[i-1]->Num_Projecteur)
                    {
                        Impression_Liste << "</table> <br /> <br />"<<std::endl;

                        Impression_Liste << "<table>"
                                            "<tr>"
                                             << HTML_DEBUT_TABLEAU << "Nom du contenu</td>"
                                             << HTML_DEBUT_TABLEAU << "Numero du projecteur</td>"
                                             << HTML_DEBUT_TABLEAU << "Date de debut de validite</td>"
                                             << HTML_DEBUT_TABLEAU << "Date de fin de validite</td> "
                                            "</tr>"
                                            << std::endl;
                }
                    if(m_Kdm_Lister[i]->Approche_De_La_Fin_De_Validite == true)
                    {

                                            if(m_Kdm_Lister[i]->Jour_restant_de_validite >= 3 && m_Kdm_Lister[i]->Jour_restant_de_validite <= 5)
                                             {
                                                Impression_Liste << "<tr>"
                                                << HTML_INTERIEUR_TABLEAU_PROCHE_FIN_DE_VALIDITE_ORANGE << m_Kdm_Lister[i]->Nom_du_Film << "</td>"
                                                << HTML_INTERIEUR_TABLEAU_PROCHE_FIN_DE_VALIDITE_ORANGE <<  m_Kdm_Lister[i]->Num_Projecteur << "</td>"
                                                << HTML_INTERIEUR_TABLEAU_PROCHE_FIN_DE_VALIDITE_ORANGE <<  m_Kdm_Lister[i]->Date_debut_validite << "</td>"
                                                << HTML_INTERIEUR_TABLEAU_PROCHE_FIN_DE_VALIDITE_ORANGE << m_Kdm_Lister[i]->Date_Fin_Validite << "</td>"
                                                "</tr>" << std::endl;
                                            }
                                            else if(m_Kdm_Lister[i]->Jour_restant_de_validite >= 0 && m_Kdm_Lister[i]->Jour_restant_de_validite <= 3)
                                            {
                                                Impression_Liste << "<tr>"
                                                << HTML_INTERIEUR_TABLEAU_PROCHE_FIN_DE_VALIDITE_ROUGE << m_Kdm_Lister[i]->Nom_du_Film << "</td>"
                                                << HTML_INTERIEUR_TABLEAU_PROCHE_FIN_DE_VALIDITE_ROUGE <<  m_Kdm_Lister[i]->Num_Projecteur << "</td>"
                                                << HTML_INTERIEUR_TABLEAU_PROCHE_FIN_DE_VALIDITE_ROUGE <<  m_Kdm_Lister[i]->Date_debut_validite << "</td>"
                                                << HTML_INTERIEUR_TABLEAU_PROCHE_FIN_DE_VALIDITE_ROUGE << m_Kdm_Lister[i]->Date_Fin_Validite << "</td>"
                                                "</tr>" << std::endl;

                                            }
                                            else
                                            {
                                                Impression_Liste << "<tr>"
                                                                    << HTML_INTERIEUR_TABLEAU << m_Kdm_Lister[i]->Nom_du_Film << "</td>"
                                                                    << HTML_INTERIEUR_TABLEAU <<  m_Kdm_Lister[i]->Num_Projecteur << "</td>"
                                                                    << HTML_INTERIEUR_TABLEAU <<  m_Kdm_Lister[i]->Date_debut_validite << "</td>"
                                                                    << HTML_INTERIEUR_TABLEAU << m_Kdm_Lister[i]->Date_Fin_Validite << "</td>"
                                                                    "</tr>" << std::endl;
                                            }

                    }
                    else
                    {
                        Impression_Liste << "<tr>"
                                            << HTML_INTERIEUR_TABLEAU << m_Kdm_Lister[i]->Nom_du_Film << "</td>"
                                            << HTML_INTERIEUR_TABLEAU <<  m_Kdm_Lister[i]->Num_Projecteur << "</td>"
                                            << HTML_INTERIEUR_TABLEAU <<  m_Kdm_Lister[i]->Date_debut_validite << "</td>"
                                            << HTML_INTERIEUR_TABLEAU << m_Kdm_Lister[i]->Date_Fin_Validite << "</td>"
                                            "</tr>" << std::endl;
                    }



            }

        }

     }



        Box = new Message_Box("Fichier creer","Impression terminée",10,ON);
        Box->show();
           Impression_Liste << "</table>" << std::endl;
           Impression_Liste << "</body>" << std::endl;
           Impression_Liste << "</html>" << std::endl;




    }

    return ;


}

void KDM_Lister::Actualiser()
{
    if(m_Kdm_Lister.size() > 0)
    {
        while(m_Kdm_Lister.size() != 0)
        {
          m_Kdm_Lister.pop_back();
        }
    }

    std::string *Folder_Path = new std::string(QCoreApplication::applicationDirPath().toStdString());
    Lister_Les_KDM(Folder_Path);

    delete Liste;
    Liste = new QWidget;
    Liste = Creer_Liste();
    M_Scroller->setWidget(Liste);
}
