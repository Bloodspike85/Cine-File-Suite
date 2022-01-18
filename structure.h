#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <dirent.h>
#ifndef WIN32
    #include <sys/types.h>
#endif // !WIN32

#include <stdio.h>
#include <string>
#include <fstream>
#include <sstream>

#include "main.h"


struct Base_de_donnee
{


    std::string Nom_du_Film;
    std::string Num_Projecteur;
    std::string Date_debut_validite;
    std::string Date_Fin_Validite;
    int Jour_restant_de_validite;
    bool Approche_De_La_Fin_De_Validite;
   Base_de_donnee(std::string A,std::string B,std::string C,std::string D,int jour_restant,bool Validite)
   {

       Nom_du_Film = A;
       Num_Projecteur = B;
       Date_debut_validite = C;
       Date_Fin_Validite = D;
       Jour_restant_de_validite = jour_restant;
       Approche_De_La_Fin_De_Validite = Validite;

       std::ifstream Liste_De_Serveur;
       Liste_De_Serveur.open(FichierConfiguration);
       std::string Temp;
       std::vector < std::string*> Liste_serveur;

       if(Liste_De_Serveur)
       {
           while(!Liste_De_Serveur.eof())
           {
               std::getline(Liste_De_Serveur,Temp);
               Liste_serveur.push_back(new std::string(Temp.c_str()));

               Temp = "";
           }
       }
       if(Liste_serveur.size() != 0)
       {
           for(unsigned int i =0;i <Liste_serveur.size();i++)
           {


               if(Liste_serveur[i]->compare("Serveur") == 0)
               {

                   if(*Liste_serveur[i] == B)
                   {
                       std::stringstream Conv;
                       Conv << i+1;
                       Temp = Conv.str();
                       Num_Projecteur = "Projecteur_" + Temp;
                       break;
                   }
                   else
                   {
                       Num_Projecteur = B;
                   }

               }

           }
       }



   }

};

struct Mon_Logiciel
{
    int Jour;
    int Mois;
    int Annee;

    int JourKDMDebut;
    int MoisKDMDebut;
    int AnneeKDMDebut;

    int JourKDMFin;
    int MoisKDMFin;
    int AnneeKDMFin;

    std::string DateDeFinDeValidite;
    std::string DateDeDebutDeValidite;
    DIR *Repertoire = nullptr;
    std::ifstream File1;

    std::string NomDossierPrincipal;
    std::string CheminPourRepertoire;
    std::string NomDossierDestination;
    std::string NomDuFilm;
    std::string NumeroDuServeur;
    std::string TypeDeContenu;

    int NombreDeDossier;
    int compteurforfile;
    int NbrDeFichiersOK;
};


#endif // STRUCTURE_H
