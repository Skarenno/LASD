#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <unistd.h>

#include "structs.c"
#include "GestioneUtenti.c"


int main(){
    char user[STRLEN];
    strcpy(user, Accesso(user));
    printf("Welcome %s\n", user);
}