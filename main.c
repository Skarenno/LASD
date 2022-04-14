#include "mainheader.h"

void WelcomeScreen();

int main(){
    FILE* Capi = fopen(C_PATH, "r+");
    Node* Head_Capi;
    char user[STRLEN];

    Head_Capi = Initialize_Node(Head_Capi);

    FirstScreen(user);
    Head_Capi = Read_List(Capi, Head_Capi);
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