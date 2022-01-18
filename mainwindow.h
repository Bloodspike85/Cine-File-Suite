#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#ifndef WIN32
    #include <sys/types.h>
#endif // !WIN32

#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include <QImage>
#include <QSlider>
#include <QInputDialog>
#include <QLabel>
#include <QMessageBox>
#include <QCheckBox>
#include <QGroupBox>
#include <QLayout>
#include <QTabWidget>
#include <QScrollArea>
#include <QScrollBar>
#include <QScreen>

#include <fstream>
#include <sstream>
#include <strings.h>
#include <ios>


#include "Cine_File_Suite.h"
#include "Gestions_Des_Projecteurs.h"


class Main_Window : public QWidget
{

    Q_OBJECT

  public :
    Main_Window() ;// Constructeur//
    ~Main_Window() ;// Destructeur//

public slots:


   private :

         ProjecteurCheck *Proj = nullptr;

         Cine_File_Suite *Main_APP;

         QHBoxLayout *Main_App_Layout;








};

#endif
