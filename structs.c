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
    float prezzo;
}Capo;


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

void PrintAvailables(Node* Head){

    if(!Head)
        return;
    
    printf("%s in vendita a %.2f.", Head->capo.nome, Head->capo.prezzo);
    printf(" --TAGLIE DISPONIBILI: S-%d M-%d L-%d XL-%d\n", Head->capo.S, Head->capo.M, Head->capo.L, Head->capo.XL);
    PrintAvailables(Head->next);
    return;
}