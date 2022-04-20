#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <malloc.h>
#include <unistd.h>
#include <ctype.h>
#include <math.h>

#define N_CATEGORIES 3
#define N_TAGLIE 3
#define STRLEN 100
#define ARRLEN 200


#define U_PATH  "./Libraries and Files/Files/UTENTI.txt"
#define C_PATH  "./Libraries and Files/Files/CAPI.txt"
#define W_PATH  "./Libraries and Files/Files/WAITING.txt"
#define AU_PATH "./Libraries and Files/Files/ADMIN.txt"

const char* categories[N_CATEGORIES] = {"Maglia", "Felpa", "Scarpe"};

#ifndef STRUCTS 
    #define STRUCTS "structs.c"
    #include STRUCTS
#endif