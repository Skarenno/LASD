#ifndef MAIN_H
    #define MAIN_H "./Libraries and Files/mainheader.h"
    #include MAIN_H
#endif

#ifndef STD_HEAD
    #define STD_HEAD "./Libraries and Files/standard_header.h"
    #include STD_HEAD
#endif

int main(){

    char user[STRLEN];
    char choice;
    unsigned short int op_choice;
    float old_balance;
    bool quit = true;
    bool disconnect = false;

    FILE* Utenti = fopen(U_PATH, "r+");
    FILE* Waitings = fopen(W_PATH, "r+");
    FILE* Capi = fopen(C_PATH, "r+");

    User_Node* UserList_Head, *Current_User;
    TreeNode* Clothes;
    WaitingNode* Waitings_Head;

    if(!IsUsable(Utenti)){
        printf("\nUSER DATABASE ERROR, EXITING!!");
        sleep(2);
        exit(EXIT_FAILURE);
    }

    if(!IsUsable(Capi)){
        printf("\nCLOTHES DATABASE ERROR, EXITING!!\n");
        sleep(2);
        exit(EXIT_FAILURE);
    }

    UserList_Head = Initialize_User_Node(UserList_Head);
    UserList_Head = Read_User_List(Utenti, UserList_Head);

    Clothes = Initialize_Tree_Node(Clothes);
    Clothes = Read_Clothes_File(Clothes, Capi);

    Waitings_Head = Initialize_Waiting_Node(Waitings_Head);
    Waitings_Head = Read_Waiting_List(Waitings, Waitings_Head);

    fclose(Capi);
    fclose(Waitings);
    fclose(Utenti);

    while(quit){
        strcpy(user, FirstScreen(user, UserList_Head));

        Current_User = Initialize_User_Node(Current_User);
        Current_User = FindUser(user, UserList_Head);
        
        WelcomeScreen(Current_User);
        disconnect = false;

        while (!disconnect){
            PrintOptions();
            fflush(stdin);
            scanf("%hu", &op_choice);
            if(isdigit(op_choice) == 0){
                switch(op_choice){

                    case 0:
                        old_balance = Current_User->user.balance;
                        Current_User->user.balance = Withdraw(Current_User->user.balance);

                        if(old_balance != Current_User->user.balance){
                        printf("\n\n--- OPERAZIONE ESEGUITA CON SUCCESSO. NUOVO SALDO ----> %.2f ---\n", Current_User->user.balance);
                        Rewrite_User_File(UserList_Head);
                        printf("Che altra operazione si vuole effettuare? ");
                        break;
                    }
                    
                    case 1:
                        Current_User->user.balance = Load(Current_User->user.balance);
                        printf("\n\n--- OPERAZIONE ESEGUITA CON SUCCESSO. NUOVO SALDO ----> %.2f\n", Current_User->user.balance);
                        Rewrite_User_File(UserList_Head);
                        printf("Che altra operazione si vuole effettuare?");
                        break;

                    case 2:
                        Waitings_Head = SearchWaiting(Current_User, Clothes, Waitings_Head);
                        Waitings_Head = BuyMenu(Current_User, Clothes, Waitings_Head);
                        Rewrite_Clothes_File(Clothes);
                        Rewrite_Waiting_File(Waitings_Head);
                        Rewrite_User_File(UserList_Head);

                        printf("Si vuole eseguire altre operazioni? (y/n): ");
                        scanf(" %c", &choice);
                        if(choice == 'n')  
                            disconnect = true;
                        break;

                    case 3:
                        user[0] = '\0';
                        disconnect = true;
                        printf("\n\n***DISCONNESSIONE UTENTE***\n");
                        printf("***************************\n\n");
                        sleep(1);
                        break;
                }
            }
            else{
                printf("Operazione non valida. Selezionare nuova operazione");
            }
            Rewrite_Clothes_File(Clothes);
            Rewrite_User_File(UserList_Head);
        } 
    }  
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