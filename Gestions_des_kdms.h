#ifndef GESTIONS_DES_KDMS_H
#define GESTIONS_DES_KDMS_H

#ifndef WIN32
    #include <sys/types.h>
#endif // !WIN32


#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>

#include <QDebug>




class KDM_MANAGER;
#include "KDM_Manager.h"



class kdm
{
    public:
    kdm();//constructeur//
    ~kdm();//destructeur//

    //Fonction de gestion de la date//
    static int DateMoisEtJour(const char *STR, int debut);
    static int DateAnnee(const char *STR, int debut);
    static std::string GetMonthInLetter(int Mois);
    static std::string GetDateToWrite(std::string Start_Date, std::string End_Date);
    static bool CheckDate(std::string End_Date, std::string Today);
    static int Get_Diff_Time(std::string End_Date, std::string Today);
    static const std::string CurrentDateAndTime();
    static const std::string EnglishDate_To_FrenchDate(std::string Date);

    //Fonction de lecture de kdm permettant de recuperer les informations//
    static bool Verification_Of_Integrity_Of_KDM(std::string File_Name);
    static std::string Get_Movie_Name(std::string &FileName);//Est ce une KDM//
    static std::string Get_End_Validity_Date(std::string &FileName);
    static std::string Get_Start_Validity_Date(std::string &FileName);
    static std::string Get_Server_Number(std::string &FileName);
    static std::string Get_The_Movie_Type(std::string &FileName);
    static std::string Get_Movie_Language(std::string &FileName);
    static std::string Get_Movie_Audio(std::string &FileName);
    static bool Is_Ocap(std::string &FileName);

    static std::string Get_Projecteur_Name(std::string Numero_de_serveur);





    void Ajouter_Element_Dossier_Supprimer(std::string String);
    void Ajouter_Element_KDM_Supprimer(std::string String);
    void Modif_Nom_Du_Film(std::string String);

    private :

        std::string Month;
        static const int Jour_Dans_Le_Mois[12] ;




};

#endif




