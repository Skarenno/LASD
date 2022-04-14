#ifndef STRLEN
    #define STRLEN 20
#endif

#include <stdio.h>
#include <malloc.h>


typedef struct clothe{
    unsigned short int S;
    unsigned short int M;
    unsigned short int L;
    unsigned short int XL;
    char nome[STRLEN];
    float prezzo;
}Clothe;

typedef struct clothes_node{
    Clothe capo;
    struct clothes_node* next;
    struct clothes_node* prev;
}Clothes_Node;

Clothes_Node* Initialize_Clothes_Node(Clothes_Node* Head){
    Head = (Clothes_Node*)malloc(sizeof(Clothes_Node));
    Head->next = NULL;
    Head->prev = NULL;

    return Head;
}

void PrintAvailables(Clothes_Node* Head){
    if(!Head)
        return;
    
    printf("%s in vendita a %.2f.", Head->capo.nome, Head->capo.prezzo);
    printf(" --TAGLIE DISPONIBILI: S-%d M-%d L-%d XL-%d\n", Head->capo.S, Head->capo.M, Head->capo.L, Head->capo.XL);
    PrintAvailables(Head->next);
    return;
}






typedef struct user{
    char username[STRLEN];
    char password[STRLEN];
    float balance;
}User;

typedef struct user_node{
    User user;
    struct user_node* next;
}User_Node;


User_Node* Initialize_User_Node(User_Node* Head){
    Head = (User_Node*)malloc(sizeof(User_Node));
    Head->next = NULL;

    return Head;
}



User_Node* FindUser(char* username, User_Node* Head){
    if(strcmp(Head->user.username, username) == 0)
        return Head;
    
    if(Head->next)
        FindUser(username, Head->next);

    return NULL;
}