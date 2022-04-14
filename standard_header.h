#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <malloc.h>
#include <unistd.h>


#define STRLEN 20
#define U_PATH "./Files/UTENTI.txt"
#define C_PATH "./Files/CAPI.txt"
#define N_TAGLIE 4

#ifndef STRUCTS 
    #define STRUCTS "structs.c"
    #include STRUCTS
#endif