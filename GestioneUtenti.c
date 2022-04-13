#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#define STRLEN 20
#define U_PATH "./Files/UTENTI.txt"


void VerificaPassword(char* username, char* password){

    FILE* Utenti = fopen(U_PATH, "r+");

    if(!Utenti){
        printf("Impossibile accedere al \"database\"\n");
        return;
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
                printf("USERNAME E PASSWORD CORRETTI\n");
                return;
            }
            else{
                printf("PASSWORD ERRATA");
                return;
            }
        }
    }
    printf("Utente non trovato, si prega di registrarsi.\n");
    return;
 }

 char* Accesso(char* username){
     
     char password[STRLEN];

     printf("Inserire username: ");
     scanf("%s", username);
     printf("\nInserire password: ");
     scanf("%s", password);
     printf("\n");

    VerificaPassword(username, password);
    return username;
}