#include "gestions_des_informations.h"

Gestions_des_informations::Gestions_des_informations(std::string File_Path,std::string File_Name)
{
    Chemin_Du_Fichier = File_Path;
    Nom_Du_Fichier = File_Name;
    Today = kdm::CurrentDateAndTime();
    Nom_du_Film = kdm::Get_Movie_Name(File_Path);
    Num_Projecteur = kdm::Get_Server_Number(File_Path) ;
    Date_debut_validite = kdm::Get_Start_Validity_Date(File_Path) ;
    Date_Fin_Validite = kdm::Get_End_Validity_Date(File_Path) ;
    Type_De_Contenu = kdm::Get_The_Movie_Type(File_Path) ;
    Jour_restant_de_validite = kdm::Get_Diff_Time(Date_Fin_Validite,Today) ;
    Approche_De_La_Fin_De_Validite = kdm::CheckDate(Date_Fin_Validite,Today) ;
}
