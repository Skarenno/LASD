#ifndef MAIN_H
    #define MAIN_H "./Libraries and Files/mainheader.h"
    #include MAIN_H
#endif

#ifndef STD_HEAD
    #define STD_HEAD "./Libraries and Files/standard_header.h"
    #include STD_HEAD
#endif


int main(){

    User_Node* Admin_List, *Current_Admin;
    TreeNode* Clothes;

    char username[STRLEN];
    char password[STRLEN];
    int verification_code;
    bool connect = false;
    char conf_char;
    unsigned short int op_choice;

    FILE* Admins = fopen(AU_PATH, "r+");
    FILE* Capi = fopen (C_PATH, "r+");


    if(!IsUsable(Admins)){
        printf("\nADMIN DATABASE ERROR, EXITING");
        sleep(2);
        exit(EXIT_FAILURE);
    }

    Admin_List = Initialize_User_Node(Admin_List);
    Admin_List = Read_User_List(Admins, Admin_List);

    Clothes = Initialize_Tree_Node(Clothes);
    Clothes = Read_Clothes_File(Clothes, Capi);

    fclose(Admins);
    fclose(Capi);


    while(!connect){
        printf("Si vuole accedere? (y/n) ");
        scanf(" %c", &conf_char);

        if(conf_char == 'n'){
            printf("Uscita dal programma");
            exit(EXIT_SUCCESS);
        }

        printf("Inserire username: ");
        scanf("%s", username);
        printf("Inserire password: ");
        scanf("%s", password);

        verification_code = VerificaPassword(Admin_List, username, password);
        switch (verification_code){
        case 0:
            Current_Admin = FindUser(username, Admin_List);
            connect = true;
            break;
        
        case 1:
            printf("Password Errata\n\n");
            break;

        case 2:
            printf("Utente non trovato\n\n");
            break;
        default:  
            break;
        }
    }

    while(true){
        printf("Ciao %s, che azione vuoi svolgere?", Current_Admin->user.username);
        PrintAdminOptions();
        scanf("%hu", &op_choice);

        switch(op_choice){
            case 0:
                Clothes = RemoveClothe(Clothes);
                break;
            
            case 1:
                //Aggiungi
                break;

            case 2:
                //RegistraAdmin
                break;

            default:
                break;
        }
    }

}