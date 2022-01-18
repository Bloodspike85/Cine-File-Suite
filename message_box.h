#ifndef MESSAGE_BOX_H
#define MESSAGE_BOX_H

#ifndef WIN32
    #include <sys/types.h>
#endif // !WIN32

#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include <QImage>
#include <QInputDialog>
#include <QLabel>
#include <QMessageBox>
#include <fstream>
#include <sstream>
#include <iostream>
#include <strings.h>
#include <QLayout>


enum{OFF=0,ON=1};
class Message_Box : public QWidget
{

    Q_OBJECT

  public :
    Message_Box(QString Title,QString Text,int Taille_Text,int Bouton_ON_OFF) ;// Constructeur///
    Message_Box(){initialisation_a_null();}
    ~Message_Box() ;// Destructeur//
    void SetText(QString NewText);
    void SetSecondText(QString NewText);
    void SetTitle(QString NewTitle);

    void initialisation_a_null()
    {
        Bouton_OK = nullptr;
        text = nullptr;
        Secondtext = nullptr;
        Layout = nullptr;

    }


public slots:

   private :
    QPushButton *Bouton_OK = nullptr;
    QLabel *text = nullptr;
    QLabel *Secondtext = nullptr;

    QVBoxLayout *Layout = nullptr;

    int Hauteur_Fenetre;
    int Largeur_Fenetre;



};

#endif


