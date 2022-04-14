#ifndef STD_HEAD
    #define STD_HEAD "standard_header.h"
#endif

#include STD_HEAD

typedef struct capo{
    unsigned short int S;
    unsigned short int M;
    unsigned short int L;
    unsigned short int XL;
    char nome[STRLEN];
    double prezzo;
} Capo;


typedef struct nodo{
    Capo capo;
    struct nodo* next;
    struct nodo* prev;
}Node;

