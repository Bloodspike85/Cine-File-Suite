#ifndef GESTIONS_DES_INFORMATIONS_H
#define GESTIONS_DES_INFORMATIONS_H

#ifndef WIN32
    #include <sys/types.h>
#endif // !WIN32

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>


class kdm;
#include "Gestions_des_kdms.h"




class Gestions_des_informations
{

public  :

    Gestions_des_informations(std::string File_Path,std::string File_Name);
    ~Gestions_des_informations();

    std::string Get_Nom_Du_Film(){return Nom_du_Film ;}
    std::string Get_Numero_Projecteur(){return Num_Projecteur ;}
    std::string Get_Date_Debut_Validite(){return Date_debut_validite ;}
    std::string Get_Date_Fin_Validite(){return Date_Fin_Validite ;}
    std::string Get_Type_De_Contenu(){return Type_De_Contenu;}
    int Get_Jour_Restant_De_Validite(){return Jour_restant_de_validite ;}
    bool get_Proche_De_La_Fin_De_Validite(){return Approche_De_La_Fin_De_Validite ;}



private:

    std::string Chemin_Du_Fichier;
    std::string Nom_Du_Fichier;
    std::string Today;
    std::string Nom_du_Film;
    std::string Num_Projecteur;
    std::string Date_debut_validite;
    std::string Date_Fin_Validite;
    std::string Type_De_Contenu;
    int Jour_restant_de_validite;
    bool Approche_De_La_Fin_De_Validite;

};

#endif
