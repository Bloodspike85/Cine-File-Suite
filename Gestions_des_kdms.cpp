#include <string>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <QTime>
#include <QTimer>


#include "Gestions_des_kdms.h"
#include "Gestions_Des_Dossiers.h"
#include "Gestions_Des_Fichiers.h"
#include "Gestions_Des_Projecteurs.h"
#include "main.h"



kdm::kdm()
{

}
kdm::~kdm()
{

}

/******************************************* Gestions des dates **************************************************/
const std::string kdm::CurrentDateAndTime()
{
    QString Date = QDate::currentDate().toString("dd/MM/yyyy");

    return Date.toStdString();
}

int kdm::DateAnnee(const char *STR, int debut) // STATIC
{
    int Chiffre = 0;

    int unite = 0, dizaine = 0, cent = 0, mille = 0;

    mille = STR[debut] - '0';
    cent = STR[debut + 1] - '0';
    dizaine = STR[debut + 2] - '0';
    unite = STR[debut + 3] - '0';

    dizaine *= 10;
    cent *= 100;
    mille *= 1000;

    Chiffre = (mille + cent + dizaine + unite);

    return Chiffre;

}
int kdm::DateMoisEtJour(const char *STR, int debut) // STATIC
{
    int Chiffre = 0;
    int unite = 0, dizaine = 0;

    dizaine = STR[debut] - '0';
    unite = STR[debut + 1] - '0';

    dizaine *= 10;

    Chiffre = (dizaine + unite);

    return Chiffre;

}

std::string kdm::GetMonthInLetter(int Mois) // STATIC
{
    std::string Month = "";
    switch(Mois)
    {
    case 1 :
        Month = "Janvier";
        break;
    case 2 :
        Month = "Fevrier";
        break;
    case 3 :
        Month = "Mars";
        break;
    case 4 :
        Month = "Avril";
        break;
    case 5 :
        Month = "Mai";
        break;
    case 6 :
        Month = "Juin";
        break;
    case 7 :
        Month = "Juillet";
        break;
    case 8 :
        Month = "Aout";
        break;
    case 9 :
        Month = "Septembre";
        break;
    case 10 :
        Month = "Octobre";
        break;
    case 11 :
        Month = "Novembre";
        break;
    case 12 :
        Month = "Decembre";
        break;
    }

    return Month;
}

const std::string kdm::EnglishDate_To_FrenchDate(std::string Date) // STATIC
{
    //Type de date annee-mois-jour a tranformer en jour_mois_annee
    std::string French_Date = "" ;

    if(Date[2] == '/')
    {
        std::string Jour = Date.substr(0,2);
        std::string Mois = Date.substr(3,4);
        std::string Annee = Date.substr(6,9);

        French_Date = Jour + "_" + GetMonthInLetter(atoi(Mois.c_str())) + "_" + Annee;
    }
    else
    {
        std::string Jour = Date.substr(8,9);
        std::string Mois = Date.substr(5,6);
        std::string Annee = Date.substr(0,4);

        French_Date = Jour + "_" + GetMonthInLetter(atoi(Mois.c_str())) + "_" + Annee;
    }

    return  French_Date;

}

std::string kdm::GetDateToWrite(std::string Start_Date, std::string End_Date) // STATIC
{

    int End_Day , End_Month , End_Year ;
    int Start_Day , Start_Month , Start_Year ;

    End_Day  = DateMoisEtJour(End_Date.c_str() , 8);
    End_Month  = DateMoisEtJour(End_Date.c_str() , 5);
    End_Year = DateAnnee(End_Date.c_str() , 0);

    Start_Day  = DateMoisEtJour(Start_Date.c_str() , 8);
    Start_Month  = DateMoisEtJour(Start_Date.c_str() , 5);
    Start_Year = DateAnnee(Start_Date.c_str() , 0);


    std::string Temp0 = "";
    std::string Temp5 = "";
    std::string Temp6 = "";
    std::stringstream *Temp1;
    std::stringstream *Temp2;
    std::stringstream *Temp3;
    std::stringstream *Temp4;

    Temp1 = new std::stringstream();
    Temp2 = new std::stringstream();
    Temp3 = new std::stringstream();
    Temp4 = new std::stringstream();
    std::string DtoPrint = "";
    std::string MtoPrint = "";
    std::string YtoPrint = "";
    MtoPrint = GetMonthInLetter(End_Month);

    Temp1->clear();

    *Temp1 << End_Day;
    if(End_Day <=9)
    {
         DtoPrint = "0" +Temp1->str();
    }
    else
    {
        DtoPrint = Temp1->str();
    }

    *Temp2 << End_Year;
    YtoPrint = Temp2->str();
    Temp1->clear();

    Temp0 = "_" + DtoPrint +"_" + MtoPrint +"_" + YtoPrint ;

    *Temp3 << Start_Day;
    if(Start_Day <=9)
    {
         DtoPrint = "0" +Temp3->str();
    }
    else
    {
        DtoPrint = Temp3->str();
    }
    *Temp4 << Start_Year;
    YtoPrint = Temp4->str();

    MtoPrint = GetMonthInLetter(Start_Month);
    Temp5 = "_" + DtoPrint +"_" + MtoPrint +"_" + YtoPrint ;

    Temp6 = Temp5 + "_au" + Temp0;

    Temp0 = Temp6;


    delete Temp1;
    delete Temp2;
    delete Temp3;
    delete Temp4;

    return Temp0;
}

/***************************************** Recuperation des elements des KDM ********************************************/


bool kdm::Verification_Of_Integrity_Of_KDM(std::string File_Name)
{
    /*On verifie que les elements standart d'une KDM apparaisse bien
     * Le numero de serveur
     * Le nom du film
     * la date de validite de fin et de debut
     */

    std::ifstream Fichier_A_Tester(File_Name);

    if(Fichier_A_Tester)
    {
        std::string Temporaire = "";
        while (std::getline(Fichier_A_Tester,Temporaire))
        {
            if (Temporaire.find("<X509SubjectName>") != std::string::npos)//Si c'est une KDM//
            {

                 while (std::getline(Fichier_A_Tester,Temporaire))
                 {
                     if (Temporaire.find("<ContentTitleText>") != std::string::npos)//Si c'est une KDM//
                     {

                          while (std::getline(Fichier_A_Tester,Temporaire))
                          {
                              if (Temporaire.find("<ContentKeysNotValidBefore>") != std::string::npos)//Si c'est une KDM//
                              {

                                   while (std::getline(Fichier_A_Tester,Temporaire))
                                   {
                                       if (Temporaire.find("<ContentKeysNotValidAfter>") != std::string::npos)//Si c'est une KDM//
                                       {
                                           //std::cout << "KDM valide" << std::endl;
                                           return true ;


                                       }
                                   }


                              }
                          }


                     }
                 }


            }
        }
    }
    else
    {
        return false ;
    }

    return  false ;
}

std::string kdm::Get_Movie_Name(std::string &FileName)
{

    std::ifstream Fichier_A_Tester(FileName);


    if(Fichier_A_Tester)
    {
        std::string Temporaire = "";
        std::string Nom_Du_Film = "";

        while (std::getline(Fichier_A_Tester,Temporaire))
        {
            if (Temporaire.find("<ContentTitleText>") != std::string::npos)//Si c'est une KDM//
            {

                for (unsigned int i = 0; i<Temporaire.size(); i++)
                {
                    if (Temporaire[i] == '>')
                    {
                        i++;
                        for (unsigned int j = i; j< Temporaire.size(); j++)
                        {
                            if (Temporaire[j] == '_')
                            {
                                Nom_Du_Film = Temporaire.substr(i, j - i);
                                Fichier_A_Tester.close();
                                return Nom_Du_Film;
                            }

                        }
                    }
                }
            }
        }
    }

    return std::string("ERREUR");
}



std::string kdm::Get_Start_Validity_Date(std::string &FileName)
{


    std::ifstream Fichier_A_Tester(FileName);

    if(Fichier_A_Tester)
    {
        std::string Temporaire = "";
        std::string Date_De_Debut_De_Validite_Du_Film = "";

        while (std::getline(Fichier_A_Tester, Temporaire))
        {
            if (Temporaire.find("<ContentKeysNotValidBefore>") != std::string::npos)
            {
                for (unsigned int i = 0; i<Temporaire.size(); i++)
                {
                    if (Temporaire[i] == '>')
                    {
                        i++;
                        for (unsigned int j = 0; j<Temporaire.size(); j++)
                        {
                            if (Temporaire[j] == 'T')
                            {
                                Date_De_Debut_De_Validite_Du_Film = Temporaire.substr(i, j - i);
                                //Dsearch->JourKDMDebut  = DateMoisEtJour(Dsearch->DateDeDebutDeValidite.c_str(), 8);
                                //Dsearch->MoisKDMDebut  = DateMoisEtJour(Dsearch->DateDeDebutDeValidite.c_str(), 5);
                                //Dsearch->AnneeKDMDebut = DateAnnee(Dsearch->DateDeDebutDeValidite.c_str(), 0);
                                //Dsearch->File1.close();

                                return Date_De_Debut_De_Validite_Du_Film;
                            }

                        }
                        break;
                    }
                }
            }
        }

     }

    return std::string("ERREUR");



}


std::string kdm::Get_End_Validity_Date(std::string &FileName)
{


    std::ifstream Fichier_A_Tester(FileName);

    if(Fichier_A_Tester)
    {
        std::string Temporaire = "";
        std::string Date_De_Fin_De_Validite_Du_Film = "";

        while (std::getline(Fichier_A_Tester, Temporaire))
        {
            if (Temporaire.find("<ContentKeysNotValidAfter>") != std::string::npos)
            {
                for (unsigned int i = 0; i<Temporaire.size(); i++)
                {
                    if (Temporaire[i] == '>')
                    {
                        i++;
                        for (unsigned int j = 0; j<Temporaire.size(); j++)
                        {
                            if (Temporaire[j] == 'T')
                            {
                                Date_De_Fin_De_Validite_Du_Film = Temporaire.substr(i, j - i);
                                //Dsearch->JourKDMDebut  = DateMoisEtJour(Dsearch->DateDeDebutDeValidite.c_str(), 8);
                                //Dsearch->MoisKDMDebut  = DateMoisEtJour(Dsearch->DateDeDebutDeValidite.c_str(), 5);
                                //Dsearch->AnneeKDMDebut = DateAnnee(Dsearch->DateDeDebutDeValidite.c_str(), 0);
                                //Dsearch->File1.close();

                                return Date_De_Fin_De_Validite_Du_Film;
                            }

                        }
                        break;
                    }
                }
            }
        }

     }

    return std::string("ERREUR");



}

std::string kdm::Get_The_Movie_Type(std::string &FileName)
{

    std::ifstream Fichier_A_Tester(FileName);

    if(Fichier_A_Tester)
    {
        std::string Temporaire = "";
        std::string Type_De_Contenu = "";

        while (std::getline(Fichier_A_Tester, Temporaire))
        {
            if (Temporaire.find("<ContentTitleText>") != std::string::npos)
            {
                if (Temporaire.find("FTR") != std::string::npos)//Si c'est un film//
                {

                    return "Films";
                }
                else if (Temporaire.find("SHR") != std::string::npos)//Si c'est un court metrage//
                {

                    return "Court_Metrage";
                }
                else
                {

                    return "AUTRES";
                }
            }
        }

     }

    return std::string("ERREUR");


}

std::string kdm::Get_Server_Number(std::string &FileName)
{
    std::vector < std::string*> Liste_serveur;

    std::ifstream Liste_De_Serveur;
    Liste_De_Serveur.open(FichierConfiguration);

    std::ifstream Fichier_A_Tester(FileName);
    std::string Numero_Du_Serveur = "" ;
    std::string Memo;

    if(!Fichier_A_Tester)
    {
     std::cout << "Error pour récuperer le numéro de serveur de :" << FileName << " :" << strerror(errno) << std::endl;
     return std::string("ERREUR") ;
    }
    else
    {
        if(Liste_De_Serveur)
        {
            while(!Liste_De_Serveur.eof())
            {
                std::getline(Liste_De_Serveur,Memo);
                std::string LineHeader = "";
                std::stringstream GetLineHeader(Memo.c_str());

                GetLineHeader >> LineHeader;

                if(LineHeader.compare("Serveur") == 0)
                {
                    GetLineHeader >> LineHeader;
                   Liste_serveur.push_back(new std::string(LineHeader.c_str()));
                }


                Memo = "";
            }
        }
        Liste_De_Serveur.close();


        while (std::getline(Fichier_A_Tester,Memo))
        {
            if (Memo.find("<X509SubjectName>") != std::string::npos)
            {

                for(unsigned int i=0;i < Liste_serveur.size() ; i++)
                {

                        if (Memo.find(*Liste_serveur[i]) != std::string::npos)
                    {
                        Numero_Du_Serveur = *Liste_serveur[i];


                        return Numero_Du_Serveur;
                    }
                }


            }
        }

        Numero_Du_Serveur = "INCONNU";

        return Numero_Du_Serveur;


    }


}


std::string kdm::Get_Movie_Language(std::string &FileName)
{

    std::ifstream Fichier_A_Tester(FileName);

    if(Fichier_A_Tester)
    {
        std::string Temporaire = "";
        std::string Nom_Du_Film = "";

        while (std::getline(Fichier_A_Tester,Temporaire))
        {
            if (Temporaire.find("<ContentTitleText>") != std::string::npos)//Si c'est une KDM//
            {

                if (Temporaire.find("FR-") != std::string::npos)//Francais/
                {

                    return "FR";
                }
                else if (Temporaire.find("EN-") != std::string::npos)//Anglais//
                {

                    return "EN";
                }
                else if (Temporaire.find("ES-") != std::string::npos)//Espagnol//
                {

                    return "ES";
                }
                else
                {

                    return "AUTRES";
                }
            }
        }
    }

    return std::string("ERREUR");





}

std::string kdm::Get_Movie_Audio(std::string &FileName)
{

    std::ifstream Fichier_A_Tester(FileName);

    if(Fichier_A_Tester)
    {
        std::string Temporaire = "";
        std::string Nom_Du_Film = "";

        while (std::getline(Fichier_A_Tester,Temporaire))
        {
            if (Temporaire.find("<ContentTitleText>") != std::string::npos)//Si c'est une KDM//
            {

                if (Temporaire.find("_51_") != std::string::npos || Temporaire.find("_51-") != std::string::npos)
                {

                    return "51";
                }
                else if (Temporaire.find("_71_") != std::string::npos || Temporaire.find("_71-") != std::string::npos)
                {

                    return "EN";
                }
                else
                {

                    return "AUTRES";
                }
            }
        }
    }

    return std::string("ERREUR");





}





std::string kdm::Get_Projecteur_Name(std::string Numero_de_serveur)
{

    std::ifstream Liste_De_Serveur;
    Liste_De_Serveur.open(FichierConfiguration);
    std::string Temp;
    std::string Num_Projecteur;
    std::vector < std::string*> Liste_serveur;

    if(Liste_De_Serveur)
    {
        while(!Liste_De_Serveur.eof())
        {
            std::getline(Liste_De_Serveur,Temp);
            std::string LineHeader = "";
            std::stringstream GetLineHeader(Temp.c_str());

            GetLineHeader >> LineHeader;


            if(LineHeader.compare("Serveur") == 0)
            {
                GetLineHeader >> LineHeader;
               Liste_serveur.push_back(new std::string(LineHeader.c_str()));
            }


            Temp = "";
        }
    }
    if(Liste_serveur.size() != 0)
    {
        for(unsigned int i =0;i <Liste_serveur.size();i++)
        {

                if(Numero_de_serveur.compare(*Liste_serveur[i]) == 0)
                {
                    std::stringstream Conv;
                    Conv << i+1;
                    Temp = Conv.str();
                    Num_Projecteur = "Projecteur_" + Temp;
                    break;
                }
                else
                {
                    Num_Projecteur = Numero_de_serveur;
                }



        }
    }

    Liste_De_Serveur.close();
    Liste_serveur.clear();
    return Num_Projecteur;
}


bool kdm::CheckDate(std::string End_Date, std::string Today)
{
    int End_Day , End_Month , End_Year ;
    int Today_Day , Today_Month , Today_Year ;

    End_Day  = DateMoisEtJour(End_Date.c_str() , 8);
    End_Month  = DateMoisEtJour(End_Date.c_str() , 5);
    End_Year = DateAnnee(End_Date.c_str() , 0);

    Today_Day = DateMoisEtJour(Today.c_str(), 0);
    Today_Month = DateMoisEtJour(Today.c_str(), 3);
    Today_Year = DateAnnee(Today.c_str(), 6);


    if(End_Year > Today_Year)//Si c'est une année future on es ok
    {
        //kdm ok//
        return true;
    }
    else if(End_Year == Today_Year)//Si c'est l'année en cours
    {
        if(End_Month > Today_Month)//Si c'est un mois future on es ok
        {
           //KDM ok

            return true;
        }
        else if(End_Month == Today_Month)//Si c'est le mois en cours
        {
            if(End_Day > Today_Day)//Si c'est un jour future
            {
                //KDM ok

                return true;
            }
            else if(End_Day == Today_Day)//Si c'est aujourd'hui
            {
                //KDM ok

                return true;
            }
            else
            {
                return false;

            }
        }
        else
        {
            return false;
        }

    }
    else
    {
        return false;
    }
}

int kdm::Get_Diff_Time(std::string End_Date, std::string Today)
{
    int End_Day , End_Month , End_Year ;
    int Today_Day , Today_Month , Today_Year ;
    int Jour_de_l_an = 0;

    End_Day  = DateMoisEtJour(End_Date.c_str() , 8);
    End_Month  = DateMoisEtJour(End_Date.c_str() , 5);
    End_Year = DateAnnee(End_Date.c_str() , 0);

    Today_Day = DateMoisEtJour(Today.c_str(), 0);
    Today_Month = DateMoisEtJour(Today.c_str(), 3);
    Today_Year = DateAnnee(Today.c_str(), 6);

    int Jour_Dans_Le_Mois[12];

    Jour_Dans_Le_Mois[0] = 31;
    Jour_Dans_Le_Mois[1] = 28;
    Jour_Dans_Le_Mois[2] = 31;
    Jour_Dans_Le_Mois[3] = 30;
    Jour_Dans_Le_Mois[4] = 31;
    Jour_Dans_Le_Mois[5] = 30;
    Jour_Dans_Le_Mois[6] = 31;
    Jour_Dans_Le_Mois[7] = 31;
    Jour_Dans_Le_Mois[8] = 30;
    Jour_Dans_Le_Mois[9] = 31;
    Jour_Dans_Le_Mois[10] = 30;
    Jour_Dans_Le_Mois[11] = 31;

    //Sommes nous dans une année bisectiles?
    for(int i = 2016 ; i <= 2100 ; i+=4)
    {
        Jour_de_l_an = 365;
        if( Today_Year == i)
        {
            Jour_Dans_Le_Mois[1] = 29;
            Jour_de_l_an = 366;
            break;
        }

    }


    int Jour_Separant_Les_KDM = 0;

    //On calcul a combien de jour dans l'année nous sommes
    int Jour_Actuel = 0;


    if(Today_Month != 1)//Si on est pas le mois de janvier
    {
        for(int i = 0; i < Today_Month-1 ; i++)
        {
            Jour_Actuel += Jour_Dans_Le_Mois[i];
        }
    }

    Jour_Actuel += Today_Day;

    //On calcul a combien de jour la date de fin de validité de la KDM est

    int Jour_Fin_KDM = 0;

    if(Today_Year == End_Year)
    {
        if(End_Month != 1)
        {
            for(int i = 0; i < End_Month-1 ; i++)
            {
                Jour_Fin_KDM += Jour_Dans_Le_Mois[i];
            }
        }


        Jour_Fin_KDM += End_Day;
        Jour_Separant_Les_KDM = (Jour_Fin_KDM - Jour_Actuel);
    }
    else
    {
        //on calcul combien de jour il y a jour nous separant du jour de l'an
        int NewYear = 0;
        NewYear = Jour_de_l_an - Jour_Actuel;

        //Puis on ajoute le nombre de jour pour l'année suivante
        //Si le mois est le mois de janvier on ajoute directement le nombre de jour
        //Sinon on ajoute que les jours de fin de la kdm

        if(End_Month != 1)
        {
            for(int i = 0; i < End_Month-1 ; i++)
            {
                Jour_Fin_KDM += Jour_Dans_Le_Mois[i];
            }

        }

        Jour_Fin_KDM += End_Day;

        Jour_Fin_KDM += NewYear ;

        //on addition le tout afin de trouver combien de jour il reste

        Jour_Separant_Les_KDM = Jour_Fin_KDM + NewYear;
    }


    return Jour_Separant_Les_KDM;

}





