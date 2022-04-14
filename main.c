#include "mainheader.h"

void WelcomeScreen();

int main(){
    char user[STRLEN];
    FirstScreen(user);
    Node* Head_Capi;
    Head_Capi = Read_List(NULL, Head_Capi);
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