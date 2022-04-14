#ifndef STD_HEAD
    #define STD_HEAD "standard_header.h"
    #include STD_HEAD
#endif



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

Node* Initialize_Node(Node* Head){
    Head = (Node*)malloc(sizeof(Node));
    Head->next = NULL;
    Head->prev = NULL;

    return Head;
}