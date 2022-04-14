#ifndef STD_HEAD
    #define STD_HEAD "standard_header.h"
#endif

#include STD_HEAD


int VerificaPassword(char* username, char* password){

    FILE* Utenti = fopen(U_PATH, "r+");
    if(!Utenti){
        printf("Impossibile accedere al \"database Utenti\"\n");
        exit(EXIT_FAILURE);
    }

    printf("INSERITI: %s - %s\n", username, password);
    char* req_username = (char*)calloc(sizeof(char), STRLEN);
    char* req_password = (char*)calloc(sizeof(char), STRLEN);

    while(fscanf(Utenti, "%s", req_username) != EOF){
        fscanf(Utenti, "%s", req_password);  
        printf("trying: %s - %s\n", req_username, req_password); 
        
        if(strcmp(username, req_username) == 0){
            if(strcmp(password, req_password) == 0){
                // USERNAME E PASSWORD CORRETTI
                fclose(Utenti);
                return 0;
            }
            else{
                // PASSWORD ERRATA
                fclose(Utenti);
                return 1;
            }
        }
        //UTENTE NON PRESENTE
    }
    fclose(Utenti);
    return 2;
 }

void RegistraUtente(){
    bool registered;
    char n_username[STRLEN];
    char ptr_username[STRLEN];
    char buffer[STRLEN];

    FILE* file = fopen(U_PATH, "r+");
    
    printf("\nInserire nome utente da registrare (\"exit\" per uscire): ");
    while(true){
        registered = false;
        scanf("%s", n_username);
        
        if(strcmp(n_username, "exit") == 0){
            fclose(file);
            printf("---REGISTRAZIONE ANNULLATA---\n\n");
            return;
        }
        fseek(file, 0, SEEK_SET);
        
        while(fscanf(file, "%s", ptr_username) != EOF && !registered){
            if(strcmp(n_username, ptr_username) == 0){
                printf("Utente già registrato con questo username. Inserirne un altro( \"exit\" per uscire): ");
                registered = true;
            }
            fscanf(file, "%s", buffer);
        }

        if(!registered){
            char password[STRLEN];
            printf("Inserire password: ");
            scanf("%s", password);

            fprintf(file, "\n%s %s", n_username, password);
            fclose(file);

            printf("---UTENTE REGISTRATO CON SUCCESSO---\n");
            break;
        }
    }
    return;
}

char* Accesso(char* username){
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
        int verification_code = VerificaPassword(username, password);

        exit_check = true;
        switch(verification_code){
            case 0:
                printf("---T'APPOOOOOO---\n\n");
                break;

            case 1:
                printf("---PASSWORD ERRATA---\n\n");
                exit_check = false;
                break;

            case 2:
                printf("Utente non trovato, si prega di registrarsi. Desidera registrarsi? (y/n): ");
                scanf(" %c", &req_c);

                if(req_c == 'y')
                    RegistraUtente();
                if(req_c == 'n'){
                    printf("---RITORNO AL MENÚ INIZIALE---\n\n");
                }
                username[0] = '\0';

                break;
        }
    }
    return username;
}

void FirstScreen(char* user){
    short unsigned int r_action;

    while(true){

        printf("Selezionare azione (1. Accesso, 2. Registrazione): ");
        scanf("%hu", &r_action);

        if(r_action == 1){
            strcpy(user, Accesso(user));
            if(user[0] != '\0')
                break;
        }
        if(r_action == 2)
            RegistraUtente();
    }

}