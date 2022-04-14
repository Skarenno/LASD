#include "GestioneUtenti.c"
#include "GestioneCapi.c"
#include "structs.c"

void RegistraUtente();
int VerificaPassword(char* username, char* password);
char* Accesso(char* username);
void FirstScreen(char* user);