#ifndef G_UTENTI
    #define G_UTENTI "GestioneUtenti.c"
    #include G_UTENTI
#endif
#ifndef G_CAPI
    #define G_CAPI "GestioneCapi.c"
    #include G_CAPI
#endif

#ifndef STRUCTS 
    #define STRUCTS "structs.c"
    #include STRUCTS
#endif


void RegistraUtente();
int VerificaPassword(char* username, char* password);
char* Accesso(char* username, User_Node* Head);
char* FirstScreen(char* user, User_Node* Head);
FILE* Rewrite_User_File(User_Node* Head);
