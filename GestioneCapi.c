#ifndef STD_HEAD
    #define STD_HEAD "standard_header.h"
    #include STD_HEAD
#endif

unsigned short int DecideCategory (char* name){
    if(strstr(name, "Maglietta") == NULL){
        if(strstr(name, "Felpa") == NULL){
            if(strstr(name, "Scarpe") == NULL){
                printf("\nNO CATEGORY\n");
            }
            return 2;
        }
        return 1;
    }
    return 0;
}

FILE* LoadCapo(FILE* file, struct __capo* category, int arr_index, char* name){
    char tok[2] = ":";
    char* str_token;
    char str_temp[STRLEN];
    short unsigned int disp_taglie;

    strcpy(category[arr_index].name, name);
    for(int i = 0; i < N_TAGLIE; i++){
        fscanf(file, "%s", str_temp);
        str_token = strtok(str_temp, tok);
        sscanf(strtok(NULL, tok), "%hu", &disp_taglie);

        switch (i){
        case 0:
            category[arr_index].S = disp_taglie;
            break;
        
        case 1:
            category[arr_index].M = disp_taglie;
            break;

        case 2:
            category[arr_index].L = disp_taglie;
            break;

        default:
            break;
        }
    }

    fscanf(file, "%f", &category[arr_index].price);
    return file;
}

void OrganizeClothes(TreeNode* Clothes[]){
    FILE* Capi = fopen(C_PATH, "r");

    struct __capo maglie[ARRLEN];
    struct __capo felpe[ARRLEN];
    struct __capo scarpe[ARRLEN];

    int ind_maglie = 0;
    int ind_felpe = 0;
    int ind_scarpe = 0;

    char temp_str[STRLEN];
    
    while (!feof(Capi)){
        fscanf(Capi, "%s", temp_str);
        unsigned short int category = DecideCategory(temp_str);
        switch(category){
            case 0:
                Capi = LoadCapo(Capi, maglie, ind_maglie, temp_str);
                ind_maglie += 1;
                break;

            case 1:
                Capi = LoadCapo(Capi, felpe, ind_felpe, temp_str);
                ind_felpe += 1;
                break;

            case 2:
                Capi = LoadCapo(Capi, scarpe, ind_scarpe, temp_str);
                ind_scarpe += 1;
                break;
        }
    }

    StringSort(maglie, ind_maglie);
    StringSort(felpe, ind_maglie);
    StringSort(scarpe, ind_maglie);

    Clothes[0] = WriteTree(Clothes[0], maglie, ind_maglie);
    Clothes[1] = WriteTree(Clothes[1], felpe, ind_felpe);
    Clothes[2] = WriteTree(Clothes[2], scarpe, ind_scarpe);


}