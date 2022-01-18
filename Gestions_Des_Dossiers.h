#ifndef GESTIONS_DES_DOSSIERS_H
#define GESTIONS_DES_DOSSIERS_H


#ifndef WIN32
    #include <sys/types.h>
#endif // !WIN32

#include "dirent.h"

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>


#include <QString>
#include <QCheckBox>
#include <QDir>



class Gestions_des_informations;
#include "gestions_des_informations.h"

class KDM_MANAGER;
#include "KDM_Manager.h"



const char PathSeparator =
#ifdef WIN32
                            '\\';
#else
                            '/';
#endif






class Directory
{

    public:
        Directory();//constructeur//
        ~Directory();//destructeur//



        void Read_Directory_To_Check_Validity(std::string *Folder_Name,KDM_MANAGER *m_kdm_Manager) ;
        void Read_Directory_To_Check_New_KDM(std::string *Folder_Name,KDM_MANAGER *m_kdm_Manager) ;
        void Read_Directory_To_Delete_Empty_Folder(std::string *Folder_Name,KDM_MANAGER *m_kdm_Manager) ;

        bool Verificaton_Validite_KDM(std::string File_Path , std::string File_Name , KDM_MANAGER *m_KDM_Manager);
        void Copie_Nouvelle_KDM(std::string File_Path , std::string File_Name , KDM_MANAGER *m_KDM_Manager);

        static bool Skip_Projector_Folder(std::string  FolderName);

        static std::string CreateDifferentFolder(std::string File_Path,std::string File_Name);

        static std::vector <std::string*> Get_Content_Of_Folder(std::string *Folder_Name);





     private:

        std::vector < Gestions_des_informations* > KDM_INFO_HOLDER;



};

#endif //GESTIONS_DES_DOSSIERS_H


