#include "GestioneUtenti.c"
#include "GestioneCapi.c"

void RegistraUtente();
int VerificaPassword(char* username, char* password);
char* Accesso(char* username);
void FirstScreen(char* user);

Node* Read_List(FILE* file, Node* Head);