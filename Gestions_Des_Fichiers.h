#ifndef GESTIONS_DES_FICHIERS_H
#define GESTIONS_DES_FICHIERS_H

#ifndef WIN32
    #include <sys/types.h>
#endif // !WIN32

#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>

#include <QDir>


#include "Gestions_Des_Projecteurs.h"
#include "Gestions_des_kdms.h"



class fichiers
{
    public:
    fichiers();
    ~fichiers();

    static std::string Renommer_Le_Fichier_De_Sortie(std::string Folder_To_Create_Path,std::string &FilePath,std::string &FileName);
    static bool CopieDeFichier(std::string &Source, std::string &Destination);
    static bool IsFIleExist(int x);
    static bool Skip(std::string  &Filename);

    void GetNumberOfFile(std::string *Folder_Name);



    static void handle_Old_Conf_file();

    double getNumber_of_file() const;
    void setNumber_of_file(double newNumber_of_file);

private :

    double Number_of_file;
};

#endif

