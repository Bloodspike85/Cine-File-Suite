#ifndef KDM_LISTER_H
#define KDM_LISTER_H


#include <dirent.h>
#ifndef WIN32
    #include <sys/types.h>
#endif // !WIN32

#include <vector>
#include <stdio.h>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <iostream>
#include <sstream>
#include <QApplication>
#include <QLabel>
#include <QLayout>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QScrollArea>
#include <QPainter>
#include <QPushButton>

#include "structure.h"

#include "Gestions_des_kdms.h"
#include "Gestions_Des_Projecteurs.h"
#include "Gestions_Des_Fichiers.h"
#include "Gestions_Des_Dossiers.h"
#include "message_box.h"
#include "main.h"




class KDM_Lister : public QWidget
{
    Q_OBJECT
public:
    KDM_Lister(QWidget *Fenetre_Principal);
    ~KDM_Lister();

    QWidget* Creation_Interface_Graphique();
    void Ajouter_KDM(std::string A,std::string B,std::string C,std::string D,int E,bool F);
    void Lister_Les_KDM(std::string *Nom_Dossier);

    QWidget* Creer_Liste();


public slots:

    void Impression();
    void Actualiser();

private :

    Mon_Logiciel Logi;
    Message_Box *Box = nullptr;

    QMenuBar *Liste_Menu = nullptr;

    QMenu *ListerFichier = nullptr;
    QAction *Imprimer = nullptr;
    QAction *QuitApp = nullptr;

    QScrollArea *M_Scroller = nullptr;
    QWidget *Liste = nullptr;

    QVBoxLayout *Verticale_Layout = nullptr;
    QHBoxLayout *Horizontal_Layout = nullptr;
    QGridLayout *Grille = nullptr;

    QPushButton *Imprimer_Liste = nullptr;
    QPushButton *Actualiser_Liste = nullptr;
    QPushButton *Quitter = nullptr;





    std::vector<Base_de_donnee* > m_Kdm_Lister;
    bool Date_Fin_De_Validite;
    std::string Aujourdhui;
};

#endif
