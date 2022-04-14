#ifndef STD_HEAD
    #define STD_HEAD "standard_header.h"
#endif


#include STD_HEAD
#include "structs.c"

Node* Read_List(FILE* file, Node* Head){
    
    if(!Head->next){
        Head->next = Initialize_Node(Head);
    }

    const char tok[2] = ":";
    char* str_token;
    char str_temp[STRLEN];

    unsigned short int num_taglia;
    
    if(!file){
        printf("Impossibile accedere al \"database Capi\"\n");
        exit(EXIT_FAILURE);
    }

    if(!feof(file)){
        fscanf(file, "%s", Head->capo.nome);
        for(int i = 0; i < N_TAGLIE; i++){
            fscanf(file, "%s", str_temp);
            str_token = strtok(str_temp, tok);
            sscanf(strtok(NULL, tok), "%hu", &num_taglia);

            switch(i){
                case 0:
                    Head->capo.S = num_taglia;
                    break;
                case 1:
                    Head->capo.M = num_taglia;
                    break;
                case 2:
                    Head->capo.L = num_taglia;
                    break;
                case 3:
                    Head->capo.XL = num_taglia;
                    break;
            }
        }

        fscanf(file, "%lf", &Head->capo.prezzo);
        Head->next = Read_List(file, Head->next);

        if(Head->next)
            Head->next->prev = Head;
        return Head;
    }
    else{
        free(Head);
        return NULL;
    }
    
}