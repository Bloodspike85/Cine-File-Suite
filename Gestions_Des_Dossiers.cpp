#include "Gestions_Des_Dossiers.h"
#include "Gestions_des_kdms.h"
#include "Gestions_Des_Fichiers.h"
#include "structure.h"
#include "main.h"
#include "Gestions_Des_Projecteurs.h"
#include <QApplication>


Directory::Directory()
{


}
Directory::~Directory()
{

}



void Directory::Read_Directory_To_Check_Validity(std::string *Folder_Name,KDM_MANAGER *m_kdm_Manager)
{

    std::vector <std::string*> File_handler = Get_Content_Of_Folder(Folder_Name);

    if(File_handler.empty())
    {
       m_kdm_Manager->Ajouter_Un_erreur_handler("Problème dans la lecture de dossier dans la fonction Read_Directory_To_Check_Validity : " + *Folder_Name);
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

                m_kdm_Manager->setTotal_file_readed(m_kdm_Manager->getTotal_file_readed() + 1);
                std::string Nom_Du_Fichier = File_handler[i]->c_str();
                std::string Chemin_Du_Fichier = *Folder_Name + PathSeparator + File_handler[i]->c_str();


                m_kdm_Manager->Ajouter_Un_TexteInfo(std::string("Traitement de " + Nom_Du_Fichier));
                std::cout << "Traitement de " + Nom_Du_Fichier << std::endl;

                if(Nom_Du_Fichier.find(".xml") != std::string::npos && kdm::Verification_Of_Integrity_Of_KDM(Chemin_Du_Fichier))
                {
                    //Si c'est un fichier xml et que le test est bon alors c'est une kdm valable

                    if(kdm::Get_Movie_Name(Chemin_Du_Fichier) != "ERREUR" && kdm::Get_Start_Validity_Date(Chemin_Du_Fichier) != "ERREUR" &&
                       kdm::Get_End_Validity_Date(Chemin_Du_Fichier) != "ERREUR" && kdm::Get_Server_Number(Chemin_Du_Fichier) != "ERREUR")
                    {
                        qDebug() << "Le fichier " << Nom_Du_Fichier.c_str() << "est une KDM" ;
                        //On verifie si la date de la KDM est encore valide

                        if(!Verificaton_Validite_KDM(Chemin_Du_Fichier,Nom_Du_Fichier,m_kdm_Manager))
                        {
                            continue ;
                        }



                    }
                    else
                    {

                        qDebug() << kdm::Get_Movie_Name(Chemin_Du_Fichier).c_str()  ;
                        qDebug() << kdm::Get_Start_Validity_Date(Chemin_Du_Fichier).c_str() ;
                        qDebug() << kdm::Get_End_Validity_Date(Chemin_Du_Fichier).c_str() ;
                        qDebug() << kdm::Get_Server_Number(Chemin_Du_Fichier).c_str() ;

                        m_kdm_Manager->Ajouter_Un_erreur_handler("Le fichier : " + Chemin_Du_Fichier + " présente une erreur");


                    }

                }


            }
            if(File_handler[i]->find('.') == std::string::npos) //Dossiers
            {

                std::string Nom_Du_Dossier = File_handler[i]->c_str();
                std::string Chemin_Du_Dossier = *Folder_Name + PathSeparator + File_handler[i]->c_str();
                qApp->processEvents();

                Read_Directory_To_Check_Validity(&Chemin_Du_Dossier,m_kdm_Manager);

            }

        }
    }



}

void Directory::Read_Directory_To_Check_New_KDM(std::string *Folder_Name, KDM_MANAGER *m_kdm_Manager)
{


    std::vector <std::string*> File_handler = Get_Content_Of_Folder(Folder_Name);

    if(File_handler.empty())
    {
       m_kdm_Manager->Ajouter_Un_erreur_handler("Problème dans la lecture de dossier dans la fonction Read_Directory_To_Check_Validity");
    }
    else
    {
        for(unsigned int i = 0; i < File_handler.size() ;i++)
        {


            std::cout << File_handler[i] << std::endl;

            if(File_handler[i]->compare(".") == 0 ||File_handler[i]->compare("..") == 0)
            {
                continue;
            }

            if(File_handler[i]->find('.') != std::string::npos)//fichier
            {
                m_kdm_Manager->setTotal_file_readed(m_kdm_Manager->getTotal_file_readed() + 1);
                std::string Nom_Du_Fichier = File_handler[i]->c_str();
                std::string Chemin_Du_Fichier = *Folder_Name + PathSeparator + File_handler[i]->c_str();

                m_kdm_Manager->Ajouter_Un_TexteInfo(std::string("Traitement de " + Nom_Du_Fichier));
                std::cout << "Traitement de " + Nom_Du_Fichier << std::endl;

                if(Nom_Du_Fichier.find(".xml") != std::string::npos && kdm::Verification_Of_Integrity_Of_KDM(Chemin_Du_Fichier))
                {
                    //Si c'est un fichier xml et que le test est bon alors c'est une kdm valable

                    if(kdm::Get_Movie_Name(Chemin_Du_Fichier) != "ERREUR" && kdm::Get_Start_Validity_Date(Chemin_Du_Fichier) != "ERREUR" &&
                       kdm::Get_End_Validity_Date(Chemin_Du_Fichier) != "ERREUR" && kdm::Get_Server_Number(Chemin_Du_Fichier) != "ERREUR")
                    {
                        qDebug() << "Le fichier " << Nom_Du_Fichier.c_str() << "est une KDM" ;
                        //On copie la nouvelle KDM
                         Copie_Nouvelle_KDM(Chemin_Du_Fichier,Nom_Du_Fichier,m_kdm_Manager);




                    }

                }
                else
                {
                    std::cout << "Erreur avec " << Nom_Du_Fichier << std::endl;
                    qDebug() << kdm::Get_Movie_Name(Chemin_Du_Fichier).c_str() ;
                    if(kdm::Get_Movie_Name(Chemin_Du_Fichier).compare("ERREUR") != 0 && fichiers::Skip(Nom_Du_Fichier))
                    {
                        m_kdm_Manager->Ajouter_Un_TexteInfo(std::string("Le fichier " + Nom_Du_Fichier + " n'est pas une vrai KDM."));



                        if(QFile::remove(Chemin_Du_Fichier.c_str()))
                        {
                            qDebug() << new std::string("Suppression de " + Nom_Du_Fichier + " OK") ;
                        }
                        else
                        {
                            m_kdm_Manager->Ajouter_Un_erreur_handler("Impossible de supprimer : " + Nom_Du_Fichier);
                        }


                    }
                    else
                    {
                       qDebug() << "Le fichier " << Nom_Du_Fichier.c_str() << " n'est pas une KDM." ;
                    }


                }



            }
            if(File_handler[i]->find('.') == std::string::npos)//Dossiers
            {

                std::string Nom_Du_Dossier = File_handler[i]->c_str();
                std::string Chemin_Du_Dossier = *Folder_Name + PathSeparator + File_handler[i]->c_str();
                qApp->processEvents();

                if(!Skip_Projector_Folder(Nom_Du_Dossier))
                {
                   Read_Directory_To_Check_New_KDM(&Chemin_Du_Dossier,m_kdm_Manager);
                }








            }

        }
    }



}

bool Directory::Verificaton_Validite_KDM(std::string File_Path , std::string File_Name , KDM_MANAGER *m_KDM_Manager)
{
    qDebug() << "Vérification de la date de validité" ;
    //On regarde combien de jour il reste à la validite de la KDM

    qDebug() << File_Path.c_str() ;
    qDebug() << File_Name.c_str() ;

    /************************************************************************************/

    if(kdm::CheckDate(kdm::Get_End_Validity_Date(File_Path),kdm::CurrentDateAndTime()))
    {
    //On verifie si la case pour la sauvegarde des kdm est coché

        if(m_KDM_Manager->Get_Sauvegarde_State() && !Skip_Projector_Folder(File_Name))
        {
            std::string Temp="Sauvegarde_KDM";
            Temp="Sauvegarde_KDM" + QString(QDir::separator()).toStdString() + File_Name;
            fichiers::CopieDeFichier(File_Path, Temp);
            m_KDM_Manager->Incrementation_KDM_Sauvegarder();
        }

        std::string Temporary_File = "";
        std::stringstream Convertion;
        bool Already_Exist = false;

        qDebug() << "Elle est encore valable pour " << kdm::Get_Diff_Time(kdm::Get_End_Validity_Date(File_Path),kdm::CurrentDateAndTime()) << " jours" ;
        if(kdm::Get_Diff_Time(kdm::Get_End_Validity_Date(File_Path),kdm::CurrentDateAndTime()) <= 3)
        {
            if(kdm::Get_Diff_Time(kdm::Get_End_Validity_Date(File_Path),kdm::CurrentDateAndTime()) > 0)
            {
                Convertion << kdm::Get_Diff_Time(kdm::Get_End_Validity_Date(File_Path),kdm::CurrentDateAndTime());
                Temporary_File = "La KDM du " + kdm::Get_The_Movie_Type(File_Path) + " " + kdm::Get_Movie_Name(File_Path) + " arrive a expiration dans " + Convertion.str() + " jours.";
            }
            else
            {
                Temporary_File = "La KDM du " + kdm::Get_The_Movie_Type(File_Path) + " " + kdm::Get_Movie_Name(File_Path) + " arrive a expiration aujourd'hui.";

            }
            if(m_KDM_Manager->Get_KDM_Arrivant_A_Expiration_Size() > 0)
            {
                //std::cout << Temporary_File << std::endl ;
                for(unsigned int i = 0 ; i < m_KDM_Manager->Get_KDM_Arrivant_A_Expiration_Size() ; i++)
                {

                    if(m_KDM_Manager->Get_Element_KDM_Arrivant_A_Expiration(i).compare(Temporary_File.c_str()) == 0)
                    {
                        //std::cout << "Textes identitque" << std::endl;
                        Already_Exist = true;
                    }
                }
                if(Already_Exist == false)
                {
                    m_KDM_Manager->Ajouter_Une_KDM_Arrivant_A_Expiration(Temporary_File);
                }
            }
            else
            {
                m_KDM_Manager->Ajouter_Une_KDM_Arrivant_A_Expiration(Temporary_File);
            }


        }
       /***************************************************************************************/

        /************************************************************************************/

        return true;



    }
    else
    {
        std::cout << "suppression de la KDM de " << kdm::Get_Movie_Name(File_Path) << " Car la date n est plus valide" << std::endl;
        m_KDM_Manager->Incrementation_KDM_Effacer();
        m_KDM_Manager->Ajouter_Une_KDM_Supprimer(File_Name);
        std::string Temporaire = "KDM supprimé pour le film : ";
        Temporaire.append(kdm::Get_Movie_Name(File_Path));
        Temporaire.append(" -> ");
        Temporaire.append(kdm::Get_Projecteur_Name(kdm::Get_Server_Number(File_Path)));
        m_KDM_Manager->Ajouter_Un_TexteInfo(Temporaire);
        std::remove(File_Path.c_str());
        qApp->processEvents();

        return false;
    }

}

void Directory::Copie_Nouvelle_KDM(std::string File_Path , std::string File_Name , KDM_MANAGER *m_KDM_Manager)
{
    //On sauvegarde la KDM avec un nouveau nom et si la copie a fonctionner on supprime le fichier originel


    QDir File_To_Remove;
    qDebug() << "Copie de la nouvelle KDM" ;
    std::string Lieu_De_Copie = Directory::CreateDifferentFolder(File_Path.c_str(),File_Name.c_str());
    if(fichiers::CopieDeFichier(File_Path, Lieu_De_Copie))
    {

        m_KDM_Manager->Incrementation_KDM_Copier();
        m_KDM_Manager->Ajouter_Une_Nouvelle_KDM(kdm::Get_Movie_Name(File_Path) + " => " + kdm::Get_Projecteur_Name(kdm::Get_Server_Number(File_Path)) );
        std::string Temporaire = "KDM copiée pour le film : ";
        Temporaire.append(kdm::Get_Movie_Name(File_Path));
        Temporaire.append(" -> ");
        Temporaire.append(kdm::Get_Projecteur_Name(kdm::Get_Server_Number(File_Path)));
        m_KDM_Manager->Ajouter_Un_TexteInfo(Temporaire);
        if(File_To_Remove.remove(File_Path.c_str()))
        {
            qDebug() << "Le fichier a été supprimé." ;
        }
        else
        {
            qDebug() << "Le fichier n'as pas pu être supprimé." ;
            m_KDM_Manager->Ajouter_Un_erreur_handler("Le fichier " + File_Path + " n'as pas été supprimer.");
        }
        qApp->processEvents();
    }
    else
    {
        //std::cout << "Le lieu de copie est : " << LieuDeCopie << std::endl;
        //std::cout << "Le nom du fichier est : "<<MemoName[i]<<std::endl;

    }
}

void Directory::Read_Directory_To_Delete_Empty_Folder(std::string *Folder_Name, KDM_MANAGER *m_kdm_Manager)
{

    std::cout << "Fonction eraseAllEmptyFolder "<< std::endl;

    std::vector <std::string*> File_handler = Get_Content_Of_Folder(Folder_Name);

    QDir Directory_Reader;

    if(File_handler.empty())
    {
        m_kdm_Manager->Incrementation_Dossier_Effacer();
        std::string Temporaire = "Dossier supprimé : ";
        Temporaire.append(*Folder_Name);
        m_kdm_Manager->Ajouter_Un_TexteInfo(Temporaire);

        m_kdm_Manager->Ajouter_Un_Dossier_Supprimer(Temporaire);


        std::cout << "Dossier " << *Folder_Name << " supprimer" << std::endl;
        Directory_Reader.rmdir(Folder_Name->c_str());
        qApp->processEvents();
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

            if(File_handler[i]->find('.') == std::string::npos)
            {
                   std::string Chemin_Du_Dossier = *Folder_Name + PathSeparator + File_handler[i]->c_str();


                   Read_Directory_To_Delete_Empty_Folder(&Chemin_Du_Dossier,m_kdm_Manager);



            }
        }

    }


}

bool Directory::Skip_Projector_Folder(std::string  FolderName)
{

    for(unsigned int i = 0; i < ProjecteurCheck::GetListOfServer() ; i++)
    {
        std::string Projecteur_Number = "Projecteur_";

        std::stringstream Conv;
        Conv << i+1;

        Projecteur_Number.append(Conv.str());

        if(FolderName.compare(Projecteur_Number))
        {
            return true;
        }
    }

    if (FolderName == "Sauvegarde_KDM" || FolderName == "Makefile"
     || FolderName == "Serveur_Inconnu"|| FolderName == "Collect"|| FolderName == "Archive" || FolderName == "Cine_File_Suite")
    { return true; }
	else
	{
        return false;
	}

}

std::string Directory::CreateDifferentFolder(std::string File_Path,std::string File_Name)
{


    //On creer le nouveau dossier avec le chemin complet si le dossier n'éxiste pas encore;

    QDir Directory_To_Create;
    std::string Nouveau_Chemin = "" ;
    std::string Nouveau_Nom_Du_Fichier = "";
    std::string Lieu_De_Copie = "" ;

    ProjecteurCheck CheckProj;
    CheckProj.GetServeurNumber();


    for(unsigned int i =0 ;i < CheckProj.Get_Serveur_Name_Size()  ;i++)
    {

            if (kdm::Get_Server_Number(File_Path).compare(CheckProj.Get_Element_Liste_Projecteur(i)) == 0)
        {


            std::string NumServeur ;
            std::ostringstream oss;
            oss << i + 1;
            NumServeur = oss.str();


            Nouveau_Chemin =  Directory_To_Create.currentPath().toStdString() + QString(Directory_To_Create.separator()).toStdString() + "Projecteur_" + NumServeur + QString(Directory_To_Create.separator()).toStdString() + kdm::Get_The_Movie_Type(File_Path) + QString(Directory_To_Create.separator()).toStdString() + kdm::Get_Movie_Name(File_Path);
            if(!Directory_To_Create.exists(Nouveau_Chemin.c_str()))
            {
                if(Directory_To_Create.mkpath(Nouveau_Chemin.c_str()))
                {
                    qDebug() << "Dossier créer : " << Nouveau_Chemin.c_str();
                }
            }


            Nouveau_Nom_Du_Fichier = fichiers::Renommer_Le_Fichier_De_Sortie(Nouveau_Chemin,File_Path,File_Name);
            Lieu_De_Copie = Nouveau_Chemin + QString(Directory_To_Create.separator()).toStdString() + Nouveau_Nom_Du_Fichier;


            return Lieu_De_Copie;
        }

    }


        Nouveau_Chemin = Directory_To_Create.currentPath().toStdString() + QString(Directory_To_Create.separator()).toStdString() + "Serveur_Inconnu" + QString(Directory_To_Create.separator()).toStdString() + kdm::Get_The_Movie_Type(File_Path) + QString(Directory_To_Create.separator()).toStdString() + kdm::Get_Movie_Name(File_Path);
        if(!Directory_To_Create.exists(Nouveau_Chemin.c_str()))
        {
            if(Directory_To_Create.mkpath(Nouveau_Chemin.c_str()))
            {
                qDebug() << "Dossier créer : " << Nouveau_Chemin.c_str();
            }
        }
        Lieu_De_Copie = Nouveau_Chemin + QString(Directory_To_Create.separator()).toStdString() + File_Name;



    return Lieu_De_Copie;
}



std::vector <std::string*> Directory::Get_Content_Of_Folder(std::string *Folder_Name)
{
    struct dirent *diread;

    DIR *Directory_Reader;

    std::vector <std::string*> File_handler;
    std::string Temporaire = "";


     if ((Directory_Reader = opendir(Folder_Name->c_str())) != nullptr)
     {
          while ((diread = readdir(Directory_Reader)) != nullptr)
          {
                Temporaire = diread->d_name;
                if(Temporaire.compare(".") == 0 || Temporaire.compare("..") == 0)
                {
                    continue;
                }
                else
                {
                   File_handler.push_back(new std::string (diread->d_name));
                }

                Temporaire.clear();

          }

            closedir (Directory_Reader);

      }

     return File_handler;
}



