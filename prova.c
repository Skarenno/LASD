#include "structs.c"
#include "GestioneUtenti.c"

void WelcomeScreen();

int main(){
    char user[STRLEN];
    FirstScreen(user);
    WelcomeScreen(user);
}

void WelcomeScreen(char* user){

    printf("\n*************\n");
    printf("*           *\n");
    printf("*  WELCOME  *\n");
    printf("*           *\n");
    printf("*************\n");
    printf("*************\n");

    printf("Hai effettutato l'accesso come \"%s\"\n", user);
}