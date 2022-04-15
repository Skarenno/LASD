#ifndef MAIN_H
    #define MAIN_H "mainheader.h"
    #include MAIN_H
#endif
#ifndef STD_HEAD
    #define STD_HEAD "standard_header.h"
    #include STD_HEAD
#endif


int main(){
    FILE* Capi = fopen(C_PATH, "r+");
    FILE* Utenti = fopen(U_PATH, "r+");

    char user[STRLEN];
    unsigned short int op_choice;
    bool quit = true;

    User_Node* UserList_Head, *Current_User;

    UserList_Head = Initialize_User_Node(UserList_Head);
    UserList_Head = Read_User_List(Utenti, UserList_Head);

    TreeNode** ClothesCategories;
    ClothesCategories = (TreeNode**)malloc(sizeof(TreeNode*));
    OrganizeClothes(ClothesCategories);

    while(quit){
        Utenti = Rewrite_User_File(UserList_Head);
        strcpy(user, FirstScreen(user, UserList_Head));
        
        Current_User = Initialize_User_Node(Current_User);
        Current_User = FindUser(user, UserList_Head);

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
    Utenti = Rewrite_User_File(UserList_Head);
}

