#include "GestioneUtenti.c"
#include "GestioneCapi.c"

#ifndef STRUCTS 
    #define STRUCTS "structs.c"
    #include STRUCTS
#endif


Clothes_Node* Initialize_Clothes_Node(Clothes_Node* Head);

void RegistraUtente();
int VerificaPassword(char* username, char* password);
char* Accesso(char* username);
char* FirstScreen(char* user);

Clothes_Node* Read_List(FILE* file, Clothes_Node* Head);