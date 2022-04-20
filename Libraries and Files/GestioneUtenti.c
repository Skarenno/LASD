#ifndef STD_HEAD
    #define STD_HEAD "standard_header.h"
    #include STD_HEAD
#endif

void Rewrite_User_File(User_Node* Head){
    User_Node* Cursor = Initialize_User_Node(Cursor);
    Cursor = Head;

    FILE* file = fopen(U_PATH, "w+");
    if(!file){
        printf("AOO");
        exit(EXIT_FAILURE);
    }
    while(Cursor){
        if(Cursor->user.username[0] != '\0')
            fprintf(file, "%s %s %.2f\n", Cursor->user.username, Cursor->user.password, Cursor->user.balance);
            Cursor = Cursor->next;
    }

    fclose(file);
}

int VerificaPassword(User_Node* Head, char* username, char* password){
        User_Node* Cursor = Initialize_User_Node(Cursor);
        Cursor = Head;

        while(Cursor){
            if(strcmp(Cursor->user.username, username) == 0 ){
                if(strcmp(Cursor->user.password, password) == 0)
                    return 0;
                else
                    return 1;
            }
            Cursor = Cursor->next;
        }

    return 2;
 }

void RegistraUtente( User_Node* Head){
    User_Node* Cursor = Initialize_User_Node(Cursor);

    bool registered;
    char n_username[STRLEN];
    char ptr_username[STRLEN];
    
    printf("\nInserire nome utente da registrare (\"exit\" per uscire): ");
    while(true){
        Cursor = Head;
        registered = false;

        scanf("%s", n_username);
        
        if(strcmp(n_username, "exit") == 0){
            printf("---REGISTRAZIONE ANNULLATA---\n\n");
            return;
        }
        
        while(Cursor){
            if(Cursor->user.username[0] != '\0' && strcmp(Cursor->user.username, n_username) == 0){
                registered = true;
                printf("---NOME UTENTE NON DISPONIBILE---\n Inserire un nuovo nome utente: ");
                break;
            }
            Cursor = Cursor->next;
        }
    

        if(!registered){
            printf("Inserire password: ");
            Cursor = InsertNode(Head, Cursor);
            scanf("%s", Cursor->user.password);

            strcpy(Cursor->user.username, n_username);
            Rewrite_User_File(Head);
            printf("---UTENTE REGISTRATO CON SUCCESSO---\n");
            return;
        }
    }
}
    

char* Accesso(char* username, User_Node* Head){
    char password[STRLEN];
    bool exit_check = false;
    char req_c;

    while(!exit_check){
        fflush(stdin);

        printf("Inserire username: ");
        scanf("%s", username);
        printf("Inserire password: ");
        scanf("%s", password);
        printf("\n");
        int verification_code = VerificaPassword(Head, username, password);

        exit_check = true;
        switch(verification_code){
            case 0:
                break;

            case 1:
                printf("---PASSWORD ERRATA---\n\n");
                exit_check = false;
                break;

            case 2:
                printf("Utente non trovato, si prega di registrarsi. Desidera registrarsi? (y/n): ");
                scanf(" %c", &req_c);

                if(req_c == 'y')
                    RegistraUtente(Head);
                if(req_c == 'n'){
                    printf("---RITORNO AL MENÚ INIZIALE---\n\n");
                }
                username[0] = '\0';

                break;
        }
    }
    return username;
}

char* FirstScreen(char* user, User_Node* Head){
    short unsigned int r_action;

    while(true){

        printf("Selezionare azione (1. Accesso, 2. Registrazione, 3. Chiusura programma): ");
        scanf("%hu", &r_action);

        if(r_action == 1){
            strcpy(user, Accesso(user, Head));
            if(user[0] != '\0')
                return user;;
        }
        else if(r_action == 2){
            RegistraUtente(Head);
            Rewrite_User_File(Head);
        }
        else if(r_action == 3)
            exit(EXIT_SUCCESS);
        else
            printf("Valore non valido\n");
    }

}

float GetBalance(char* user){
    FILE* Utenti = fopen(U_PATH, "r");
    
    char req_username[STRLEN];
    char buff[STRLEN];
    float balance;

     while(fscanf(Utenti, "%s", req_username) != EOF){
        fscanf(Utenti, "%s", buff);  
        fscanf(Utenti, "%f", &balance);

        if(strcmp(user, req_username) == 0)
            return balance;
    }

    return 0.0;
}

void PrintAdminOptions(){
    printf("\n0. Rimuovere capi\n");
    printf("1. Aggiungere capi\n");
    printf("2. Inserire un nuovo admin\n");
}

void PrintOptions(){
    printf("\n0. Prelevare denaro\n");
    printf("1. Aggiungere credito al conto virtuale\n");
    printf("2. Effettuare un acquisto\n");
    printf("3. Uscire\n");
    printf("Selezionare un azione: ");
}

float Withdraw(float balance){
    float op_balance;

    if(balance <= 0){
        printf("Non si dispone di credito. Si prega di selezionare un'altra opzione da quelle sopra: ");
        return balance;
    }

    printf("Quanto si desidera prelevare? (Saldo attuale: %.2f) ", balance);
    scanf("%f", &op_balance);

    if(op_balance > balance){
        printf("\n\n--- Operazione non possibile. Riselezionare operazione: ");
        return balance;
    }

    balance -= op_balance;
    return balance;
}

float Load (float balance){
    bool retry = true;
    float op_balance = 0;
    char req_c;

    while(retry){
        printf("Di quanto si vuole ricaricare il conto? ");
        scanf("%f", &op_balance);

        if(op_balance < 0){
            printf("Importo non valido, si vuole riprovare? (y/n): ");
            scanf(" %c", &req_c);
                        
            switch (req_c){
                case 'y':
                    break;

                case 'n':
                    retry = false;
                    break;
                 
                default:
                    printf("Selezione non valida.\n");
            }
        }
        else{
            balance += op_balance;
            return balance;
        }
    }
}



void  WelcomeScreen(User_Node* User){
    unsigned short int req_action;
    


    printf("\n*************\n");
    printf("*           *\n");
    printf("*  WELCOME  *\n");
    printf("*           *\n");
    printf("*************\n");
    printf("*************\n");

    printf("---||Hai effettutato l'accesso come \"%s\", il tuo saldo equivale a %.2f||---\n\n", User->user.username, User->user.balance);
    printf("Si possono eseguire le seguenti operazioni: ");
}

User_Node* Read_User_List (FILE* file, User_Node* Head){
    if(Head->next == NULL)
        Head->next = Initialize_User_Node(Head);

    if(!feof(file)){
        fscanf(file, "%s %s %f", Head->user.username, Head->user.password, &Head->user.balance);
        Head->next = Read_User_List(file, Head->next);
    }
    else{
        free(Head);
        return NULL;
    }
    
    return Head;   
}

