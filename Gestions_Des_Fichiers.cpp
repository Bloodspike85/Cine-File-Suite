#include "Gestions_Des_Fichiers.h"

#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

fichiers::fichiers()
{
    Number_of_file = 0;
    GetNumberOfFile(new std::string("."));
}
fichiers::~fichiers()
{

}
bool fichiers::IsFIleExist(int x)
{
	if (x == 1)
        return true;
	else
        return false;
}

bool fichiers::Skip(std::string  &Filename)
{

    if (Filename == "libgcc_s_dw2-1.dll"  || Filename ==  "libstdc++-6.dll"
        || Filename ==  "libwinpthread-1.dll"|| Filename ==  "Qt5Core.dll"
        || Filename ==  "Qt5Gui.dll"|| Filename ==  "Qt5Widgets.dll"
        || Filename ==  "KDM_MANAGER.exe"|| Filename ==  "LDS.proj"
            || Filename ==  "QKDM_MANAGER.exe" || Filename == "Cine_File_Suite.exe"
            || Filename == "Makefile" || Filename == "Cine_File_Suite.o")
    { return true; }
    else
    {
        return false;
    }

}

void fichiers::GetNumberOfFile(std::string *Folder_Name)
{

    std::vector <std::string*> File_handler = Directory::Get_Content_Of_Folder(Folder_Name);

    if(File_handler.empty())
    {
       std::cout << "ERREUR dans la methode de recupération du nombre de fichiers." << std::endl;
    }
    else
    {

        for(unsigned int i = 0; i < File_handler.size() ;i++)
        {

            std::cout << *File_handler[i] << std::endl;

            if(File_handler[i]->compare(".") == 0 || File_handler[i]->compare("..") == 0)
            {
                continue;
            }


            if(File_handler[i]->find('.') != std::string::npos)//fichier
            {
                Number_of_file++;

            }
            if(File_handler[i]->find('.') == std::string::npos) //Dossiers
            {

                std::string Nom_Du_Dossier = File_handler[i]->c_str();
                std::string Chemin_Du_Dossier = *Folder_Name + PathSeparator + File_handler[i]->c_str();
                qApp->processEvents();

                GetNumberOfFile(&Chemin_Du_Dossier);

            }

        }
    }


}

std::string fichiers::Renommer_Le_Fichier_De_Sortie(std::string Folder_To_Create_Path,std::string &FilePath,std::string &FileName)
{

    qDebug() << "On renome le fichier " << FileName.c_str() ;
    std::string Nouveau_Nom = "";
    std::string Ancien_Nom = FileName ;
    std::string Folder_Path = FilePath.substr(0,FilePath.size() - (FileName.size() + 1));

    ProjecteurCheck CheckProj;
    CheckProj.GetServeurNumber();

    std::string NumeroDeProjecteur="";

    QDir Repertoire_Du_Fichier(Folder_Path.c_str());
    QFileInfoList File_Info = Repertoire_Du_Fichier.entryInfoList();



    for(unsigned int k =0 ; k < CheckProj.Get_Serveur_Name_Size()-1;k++)
    {
            if (kdm::Get_Server_Number(FilePath).compare(CheckProj.Get_Element_Liste_Projecteur(k)) == 0)
            {

                std::ostringstream oss;
                oss << k + 1;
                NumeroDeProjecteur = "_pour_le_projecteur_" + oss.str();

            }
    }

    if(File_Info.size() > 2)
    {
        if(kdm::Get_Movie_Language(FilePath) != "AUTRES")
        {
            if(kdm::Get_Movie_Audio(FilePath) != "AUTRES")
            {
                Nouveau_Nom =  kdm::Get_Movie_Name(FilePath) + "_" + kdm::Get_Movie_Language(FilePath) + "_" + kdm::Get_Movie_Audio(FilePath) + "_Valable_du" + kdm::GetDateToWrite(kdm::Get_Start_Validity_Date(FilePath),kdm::Get_End_Validity_Date(FilePath)) + NumeroDeProjecteur + ".xml";

            }
            else
            {
                Nouveau_Nom =  kdm::Get_Movie_Name(FilePath) + "_" + kdm::Get_Movie_Language(FilePath) + "_Valable_du" + kdm::GetDateToWrite(kdm::Get_Start_Validity_Date(FilePath),kdm::Get_End_Validity_Date(FilePath)) + NumeroDeProjecteur + ".xml";

            }

        }
        else
        {
            if(kdm::Get_Movie_Audio(FilePath) != "AUTRES")
            {
                Nouveau_Nom =  kdm::Get_Movie_Name(FilePath) + "_" + kdm::Get_Movie_Audio(FilePath) + "_Valable_du" + kdm::GetDateToWrite(kdm::Get_Start_Validity_Date(FilePath),kdm::Get_End_Validity_Date(FilePath)) + NumeroDeProjecteur + ".xml";

            }
            else
            {
                Nouveau_Nom =  kdm::Get_Movie_Name(FilePath) + "_Valable_du" + kdm::GetDateToWrite(kdm::Get_Start_Validity_Date(FilePath),kdm::Get_End_Validity_Date(FilePath)) + NumeroDeProjecteur + ".xml";

            }

        }
        std::string Path_To_Test = Folder_To_Create_Path + QString(Repertoire_Du_Fichier.separator()).toStdString() + Nouveau_Nom ;
        if(Repertoire_Du_Fichier.exists(Path_To_Test.c_str()))
        {
            int Numero_De_Fichier = 1;
            std::string Numero="" ;
            std::ostringstream Numero_Holder;
            Numero_Holder << Numero_De_Fichier;
            Numero = Numero_Holder.str();
            if(kdm::Get_Movie_Language(FilePath) != "AUTRES")
            {
                if(kdm::Get_Movie_Audio(FilePath) != "AUTRES")
                {
                    Nouveau_Nom =  kdm::Get_Movie_Name(FilePath) + "_" + kdm::Get_Movie_Language(FilePath) + "_" + kdm::Get_Movie_Audio(FilePath) + "_Valable_du" + kdm::GetDateToWrite(kdm::Get_Start_Validity_Date(FilePath),kdm::Get_End_Validity_Date(FilePath)) + NumeroDeProjecteur +"_(" + Numero + ").xml";

                }
                else
                {
                    Nouveau_Nom =  kdm::Get_Movie_Name(FilePath) + "_" + kdm::Get_Movie_Language(FilePath) + "_Valable_du" + kdm::GetDateToWrite(kdm::Get_Start_Validity_Date(FilePath),kdm::Get_End_Validity_Date(FilePath)) + NumeroDeProjecteur +"_(" + Numero + ").xml";

                }


            }
            else
            {
                if(kdm::Get_Movie_Audio(FilePath) != "AUTRES")
                {
                    Nouveau_Nom =  kdm::Get_Movie_Name(FilePath) + "_" + kdm::Get_Movie_Audio(FilePath) + "_Valable_du" + kdm::GetDateToWrite(kdm::Get_Start_Validity_Date(FilePath),kdm::Get_End_Validity_Date(FilePath)) + NumeroDeProjecteur +"_(" + Numero + ").xml";

                }
                else
                {
                    Nouveau_Nom =  kdm::Get_Movie_Name(FilePath) + "_Valable_du" + kdm::GetDateToWrite(kdm::Get_Start_Validity_Date(FilePath),kdm::Get_End_Validity_Date(FilePath)) + NumeroDeProjecteur +"_(" + Numero + ").xml";

                }

            }

            Path_To_Test = Folder_To_Create_Path + QString(Repertoire_Du_Fichier.separator()).toStdString() + Nouveau_Nom ;
            while(Repertoire_Du_Fichier.exists(Path_To_Test.c_str()))
            {

                Numero_De_Fichier++;
                Numero_Holder.str("");
                Numero_Holder.clear();
                Numero_Holder << Numero_De_Fichier;
                Numero = "" ;
                Numero = Numero_Holder.str();
                if(kdm::Get_Movie_Language(FilePath) != "AUTRES")
                {
                    if(kdm::Get_Movie_Audio(FilePath) != "AUTRES")
                    {
                        Nouveau_Nom =  kdm::Get_Movie_Name(FilePath) + "_" + kdm::Get_Movie_Language(FilePath) + "_" + kdm::Get_Movie_Audio(FilePath) + "_Valable_du" + kdm::GetDateToWrite(kdm::Get_Start_Validity_Date(FilePath),kdm::Get_End_Validity_Date(FilePath)) + NumeroDeProjecteur +"_(" + Numero + ").xml";

                    }
                    else
                    {
                        Nouveau_Nom =  kdm::Get_Movie_Name(FilePath) + "_" + kdm::Get_Movie_Language(FilePath) + "_Valable_du" + kdm::GetDateToWrite(kdm::Get_Start_Validity_Date(FilePath),kdm::Get_End_Validity_Date(FilePath)) + NumeroDeProjecteur +"_(" + Numero + ").xml";

                    }


                }
                else
                {
                    if(kdm::Get_Movie_Audio(FilePath) != "AUTRES")
                    {
                        Nouveau_Nom =  kdm::Get_Movie_Name(FilePath) + "_" + kdm::Get_Movie_Audio(FilePath) + "_Valable_du" + kdm::GetDateToWrite(kdm::Get_Start_Validity_Date(FilePath),kdm::Get_End_Validity_Date(FilePath)) + NumeroDeProjecteur +"_(" + Numero + ").xml";

                    }
                    else
                    {
                        Nouveau_Nom =  kdm::Get_Movie_Name(FilePath) + "_Valable_du" + kdm::GetDateToWrite(kdm::Get_Start_Validity_Date(FilePath),kdm::Get_End_Validity_Date(FilePath)) + NumeroDeProjecteur +"_(" + Numero + ").xml";

                    }

                }

                Path_To_Test = Folder_To_Create_Path + QString(Repertoire_Du_Fichier.separator()).toStdString() + Nouveau_Nom ;
            }
            qDebug() << "Le nouveau nom est "  << Nouveau_Nom.c_str() ;
            return Nouveau_Nom ;



        }
        else
        {
            qDebug() << "Le nouveau nom est "  << Nouveau_Nom.c_str() ;
            return Nouveau_Nom;
        }


    }
    else
    {
        if(kdm::Get_Movie_Language(FilePath) != "AUTRES")
        {
            if(kdm::Get_Movie_Audio(FilePath) != "AUTRES")
            {
                Nouveau_Nom =  kdm::Get_Movie_Name(FilePath) + "_" + kdm::Get_Movie_Language(FilePath) + "_" + kdm::Get_Movie_Audio(FilePath) + "_Valable_du" + kdm::GetDateToWrite(kdm::Get_Start_Validity_Date(FilePath),kdm::Get_End_Validity_Date(FilePath)) + NumeroDeProjecteur + ".xml";

            }
            else
            {
                Nouveau_Nom =  kdm::Get_Movie_Name(FilePath) + "_" + kdm::Get_Movie_Language(FilePath) + "_Valable_du" + kdm::GetDateToWrite(kdm::Get_Start_Validity_Date(FilePath),kdm::Get_End_Validity_Date(FilePath)) + NumeroDeProjecteur +".xml";

            }

        }
        else
        {
            if(kdm::Get_Movie_Audio(FilePath) != "AUTRES")
            {
                Nouveau_Nom =  kdm::Get_Movie_Name(FilePath) + "_" + kdm::Get_Movie_Audio(FilePath) + "_Valable_du" + kdm::GetDateToWrite(kdm::Get_Start_Validity_Date(FilePath),kdm::Get_End_Validity_Date(FilePath)) + NumeroDeProjecteur +".xml";

            }
            else
            {
                Nouveau_Nom =  kdm::Get_Movie_Name(FilePath) + "_Valable_du" + kdm::GetDateToWrite(kdm::Get_Start_Validity_Date(FilePath),kdm::Get_End_Validity_Date(FilePath)) + NumeroDeProjecteur +".xml";

            }

        }
        qDebug() << "Le nouveau nom est "  << Nouveau_Nom.c_str() ;
        return Nouveau_Nom;
    }


}

bool fichiers::CopieDeFichier(std::string &Source, std::string &Destination)
{
    ifstream SRC(Source);
    ofstream DST(Destination);
	std::string A = "";

	if (SRC)
	{
		//Ouverture ok//
	}
	else
	{
        qDebug() << "Le fichier source ne peut etre ouvert." << strerror(errno);

        return false;
	}
	if (DST)
	{
		//Ouverture ok//
	}
	else
	{
        qDebug() << "Le fichier destination ne peut etre cree." << Destination.c_str() << " " << strerror(errno) ;

        return false;
	}

	while(std::getline(SRC,A))
    {
        DST << A << std::endl;
    }

	SRC.close();
    DST.close();

    return true;
}




void fichiers::handle_Old_Conf_file()
{
    std::ifstream AncienFichier;

    AncienFichier.open("LDS.proj");
    if(AncienFichier)
    {
        std::ofstream NouveauFichier;
        std::cout << "Gestion de l'ancien fichiers de configuration en cours" << std::endl;
        NouveauFichier.open(FichierConfiguration);
        if(NouveauFichier)
        {
            std::string Memo;
            while(std::getline(AncienFichier,Memo))
            {
                NouveauFichier << "Serveur " << Memo << std::endl;
            }
            AncienFichier.close();
            NouveauFichier.close();
            std::remove("LDS.proj");
        }
    }
    else
    {
        std::cout << "Il n'éxiste pas d'ancien fichiers de configuration." << std::endl;
        std::cout << "Vérification du nouveau fichier de configuration" << std::endl;

        std::ifstream NouveauFichier;
        NouveauFichier.open(FichierConfiguration);

        Wait::sleep(5);
        if(NouveauFichier.is_open())
        {
             std::cout << "Fichier de configuration trouvée" << std::endl;
             NouveauFichier.close();

        }
        else
        {
             std::cout << "Aucun fichier de configuration." << std::endl;
             std::cout << "Préparation pour la création du fichier de configuration" << std::endl;
        }
    }

}

double fichiers::getNumber_of_file() const
{
    return Number_of_file;
}

void fichiers::setNumber_of_file(double newNumber_of_file)
{
    Number_of_file = newNumber_of_file;
}


