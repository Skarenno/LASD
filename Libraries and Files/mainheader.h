#ifndef G_UTENTI
    #define G_UTENTI "GestioneUtenti.c"
    #include G_UTENTI
#endif
#ifndef G_WAITING
    #define G_WAITING "GestioneWaiting.c"
    #include G_WAITING
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
int VerificaPassword(User_Node* Head, char* username, char* password);
char* Accesso(char* username, User_Node* Head);
char* FirstScreen(char* user, User_Node* Head);

WaitingNode* SearchWaiting(User_Node* User, TreeNode* Clothes, WaitingNode* List);