#ifndef MAIN_H
    #define MAIN_H "mainheader.h"
    #include MAIN_H
#endif
#ifndef STD_HEAD
    #define STD_HEAD "standard_header.h"
    #include STD_HEAD
#endif

int main(){

    char user[STRLEN];
    unsigned short int op_choice;
    bool quit = true;
    FILE* Utenti = fopen(U_PATH, "r+");
    FILE* Waitings = fopen(W_PATH, "r+");

    User_Node* UserList_Head, *WaitingList, *Current_User;
    TreeNode* Clothes;
    WaitingNode* Waitings_Head;

    if(!IsUsable(Utenti)){
        printf("\nUSER DATABASE ERROR, EXITING!!");
        sleep(2);
        exit(EXIT_FAILURE);
    }
    UserList_Head = Initialize_User_Node(UserList_Head);
    UserList_Head = Read_User_List(Utenti, UserList_Head);


    Clothes = Initialize_Tree_Node(Clothes);
    Clothes = OrganizeClothes(Clothes);

    Waitings_Head = Initialize_Waiting_Node(Waitings_Head);
    Waitings_Head = Read_Waiting_List(Waitings, Waitings_Head);

    fclose(Waitings);

    while(quit){
        Utenti = Rewrite_User_File(UserList_Head);
        strcpy(user, FirstScreen(user, UserList_Head));
        
        Current_User = Initialize_User_Node(Current_User);
        Current_User = FindUser(user, UserList_Head);

        op_choice = WelcomeScreen(Current_User, Waitings_Head);

        switch(op_choice){
            case 2:
                Waitings_Head = SearchWaiting(Current_User, Clothes, Waitings_Head);
                Waitings_Head = BuyMenu(Current_User, Clothes, Waitings_Head);
                Waitings = Rewrite_Waiting_File(Waitings_Head);

                Utenti = Rewrite_User_File(UserList_Head);
                break;

            case 3:
                user[0] = '\0';
                printf("\n\n***DISCONNESSIONE UTENTE***\n");
                printf("***************************\n\n");
                sleep(2);
                break;
        }
   
    }
    Rewrite_Clothes_File(Clothes);
    Utenti = Rewrite_User_File(UserList_Head);
}


WaitingNode* SearchWaiting(User_Node* User, TreeNode* Clothes, WaitingNode* List){
    WaitingNode* WaitedClothe = Initialize_Waiting_Node(WaitedClothe);
    WaitedClothe = List;

    while(WaitedClothe != NULL){
        if(strcmp(User->user.username, WaitedClothe->waiter.name) == 0)
            List = IsInStock(Clothes, List, WaitedClothe); 

        WaitedClothe = WaitedClothe->next;
    }

    free(WaitedClothe);
    return List;
}