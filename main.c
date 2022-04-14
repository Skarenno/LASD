#include "mainheader.h"

#ifndef STD_HEAD
    #define STD_HEAD "standard_header.h"
    #include STD_HEAD
#endif

int main(){
    FILE* Capi = fopen(C_PATH, "r+");
    FILE* Utenti = fopen(U_PATH, "r+");

    Clothes_Node* ClothesList_Head;
    User_Node* UserList_Head;

    char user[STRLEN];
    unsigned short int op_choice;
    bool quit = true;

    ClothesList_Head = Initialize_Clothes_Node(ClothesList_Head);
    ClothesList_Head = Read_Clothes_List(Capi, ClothesList_Head);

    UserList_Head = Initialize_User_Node(UserList_Head);
    UserList_Head = Read_User_List(Utenti, UserList_Head);

    
    while(quit){
    Utenti = Rewrite_User_File(UserList_Head);
    strcpy(user, FirstScreen(user));
    printf("\n------------%s -----------", user);
    User_Node* Current_User = FindUser(user, UserList_Head);

    op_choice = WelcomeScreen(Current_User);

        switch(op_choice){
            case 2:
                quit = false;
                break;

            case 3:
                user[0] = '\0';
                printf("\n\n***DISCONNESSIONE UTENTE***\n");
                printf("***************************\n\n");
                sleep(2);
                break;
        }
   
    }
}

