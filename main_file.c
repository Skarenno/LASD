#include "mainheader.h"

void WelcomeScreen(char* user);

int main(){
    FILE* Capi = fopen(C_PATH, "r+");
    Node* Head_Capi;
    char user[STRLEN];
    Head_Capi = Initialize_Node(Head_Capi);

    FirstScreen(user);
    Head_Capi = Read_List(Capi, Head_Capi);
    WelcomeScreen(user);
    PrintList(Head_Capi);
}

void WelcomeScreen(char* user){

    printf("\n*************\n");
    printf("*           *\n");
    printf("*  WELCOME  *\n");
    printf("*           *\n");
    printf("*************\n");
    printf("*************\n");

    printf("Hai effettutato l'accesso come \"%s\", il tuo saldo equivale a %.2f", user, GetBalance(user));

}