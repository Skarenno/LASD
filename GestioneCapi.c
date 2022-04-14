#ifndef STD_HEAD
    #define STD_HEAD "standard_header.h"
#endif

#include STD_HEAD


Node* Read_List(FILE* file, Node* Head){
    if (file == NULL){
        file = (FILE*)malloc(sizeof(FILE));
    }

    const char tok[2] = ":";
    char* str_token;
    char str_temp[STRLEN];

    unsigned short int num_taglia;

    file = fopen(C_PATH, "r+");
    
    if(!file){
        printf("Impossibile accedere al \"database Capi\"\n");
        exit(EXIT_FAILURE);
    }

    while (fscanf(file, "%s", Head->capo.nome) != EOF){
        for(int i = 0; i < N_TAGLIE; i++){
            fscanf(file, "%s", str_temp);
            str_token = strtok(str_temp, tok);
            sscanf(strtok(NULL, tok), "%hu", num_taglia);

            printf("num_ taglia");
        }
    }
    
}