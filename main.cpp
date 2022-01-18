/*
 * KDM_Manager est un logiciel creer dans le but de simplifier
 * le travail du projectionniste du circuit itinérant.
 *
 * Il permet en quelques clics et secondes de pouvoir trier la totalité des KDMs
 * par type de contenu et numéro de serveur.
 *
 * Logiciel créer par Oiselet Alain Résident à Magny saint médard en France
 *
 *
 * */


#include "main.h"
#include "mainwindow.h"

#include <QTimer>




int main(int argc, char *argv[])
{

    QApplication app(argc,argv);

    QSplashScreen *SplashScreen=new QSplashScreen;
    SplashScreen->setPixmap(QPixmap(":/Images/Splashscreen7"));





    Main_Window *M_Window;
    M_Window = new Main_Window;

    M_Window->setEnabled(false);
    SplashScreen->show();

    SplashScreen->finish(M_Window);

    QTimer::singleShot(25000, SplashScreen, SLOT(hide()));

    M_Window->setEnabled(true);

    M_Window->show();

    delete SplashScreen;


    return app.exec();

}

