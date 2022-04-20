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
    TreeNode* Clothes = NULL;

    char username[STRLEN];
    char password[STRLEN];
    int verification_code;

    bool user_connected = false;
    bool disconnect;
    bool quit = false;

    char conf_char;
    int op_choice;

    FILE* Admins = fopen(AU_PATH, "r+");
    FILE* Capi = fopen (C_PATH, "r+");


    if(!IsUsable(Admins)){
        printf("\nADMIN DATABASE ERROR\nDATABSE VUOTO O IRRAGIUNGIBILE\n");
        if(!feof(Admins)){
            fprintf(Admins, "user password 0.0");
            printf("AGGIUNTA \"user\" e \"password\"");
            sleep(1);
        }
        printf("\nEXITING\n");
        sleep(2);
        exit(EXIT_FAILURE);
    }

    Admin_List = Initialize_User_Node(Admin_List);
    Admin_List = Read_User_List(Admins, Admin_List);

    if(IsUsable(Capi)){
        Clothes = Initialize_Tree_Node(Clothes);
        Clothes = Read_Clothes_File(Clothes, Capi);
    }

    fclose(Admins);
    fclose(Capi);


    while(!quit){

        while(!user_connected){
            disconnect = false;
            printf("Si vuole accedere? (y/n) ");
            scanf(" %c", &conf_char);

            if(conf_char == 'n'){
                quit = true;
                disconnect = true;
                break;
            }

            printf("Inserire username: ");
            scanf("%s", username);
            printf("Inserire password: ");
            scanf("%s", password);

            verification_code = VerificaPassword(Admin_List, username, password);
            switch (verification_code){
            case 0:
                Current_Admin = FindUser(username, Admin_List);
                user_connected = true;
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

        while(!disconnect){
            op_choice = 0;
            fflush(stdin);
            printf("Ciao %s, indica l'azione che vuoi svolgere", Current_Admin->user.username);
            PrintAdminOptions();

            if(op_choice != 1 && op_choice != 3){
                if(Clothes == NULL){
                    printf("\nATTENZIONE: ATTUALMENTE NON SONO PRESENTI CAPI\n");
            }
            
            printf("Immettere azione: ");
            scanf("%d", &op_choice);

            
            }
            switch(op_choice){
                case 0:
                    Clothes = ChangeClothes(Clothes);
                    break;
                
                case 1:
                    Register(Admin_List);
                    Rewrite_Admin_File(Admin_List);
                    break;

                case 2:
                    Clothes = AddClothe(Clothes);
                    Rewrite_Clothes_File(Clothes);
                    break;
                case 3:
                    printf("******************\n**DISCONNESSIONE**\n");
                    user_connected = false;
                    disconnect = true;
                    sleep(1);
                    break;
            }
        }
    }   

    return 0;
}