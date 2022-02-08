#ifndef MAIN_H
#define MAIN_H

#ifndef WIN32
    #include <sys/types.h>
#endif // !WIN32

#include <QApplication>
#include <QPushButton>
#include <QSplashScreen>


#include <QDesktopWidget>
#include <QThread>
#include <stdio.h>
#include <stdlib.h>
#include <QScreen>
#include <fstream>

#include <stdio.h>
#include <string>
#include <fstream>



#define KDM_MANAGER_VERSION "KDM_MANAGER V 2.2"
#define KDM_LISTER_VERSION  "KDM_LISTER V 1.0"
#define FichierConfiguration "Config.cfs"



class Wait : public QThread
{
public:
    static void sleep(unsigned long secs) { QThread::sleep(secs); }
};



class resolution_Ecran
{
public :
    static QRect Get_Resolution_Ecran()
    {

        return qApp->desktop()->availableGeometry();

    }
};

#endif


