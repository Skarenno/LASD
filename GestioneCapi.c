#ifndef STD_HEAD
    #define STD_HEAD "standard_header.h"
    #include STD_HEAD
#endif


struct __capo* LoadCapo(FILE* file, struct __capo* array, int arr_index, char* name){
    char tok[2] = ":";
    char* str_token;
    char str_temp[STRLEN];
    short unsigned int disp_taglie;

    strcpy(array[arr_index].name, name);

    for(int i = 0; i < N_TAGLIE; i++){
        fscanf(file, "%s", str_temp);
        str_token = strtok(str_temp, tok);
        sscanf(strtok(NULL, tok), "%hu", &disp_taglie);

        switch (i){
        case 0:
            array[arr_index].S = disp_taglie;
            break;
        
        case 1:
            array[arr_index].M = disp_taglie;
            break;

        case 2:
            array[arr_index].L = disp_taglie;
            break;

        default:
            break;
        }
    }

    array[arr_index].code = arr_index;
    fscanf(file, "%f", &array[arr_index].price);
    return array;
}

TreeNode* OrganizeClothes(TreeNode* Clothes){
    FILE* Capi = fopen(C_PATH, "r");

    if(!IsUsable(Capi)){
        printf("\nCLOTHES DATABASE ERROR, EXITING!!\n");
        sleep(2);
        exit(EXIT_FAILURE);
    }

    struct __capo *arr_capi = (struct __capo*)calloc(ARRLEN, sizeof(struct __capo));
    int index = 0;

    char clothe_name[STRLEN];
    
    while (!feof(Capi)){
        fscanf(Capi, "%s", clothe_name);
        arr_capi = LoadCapo(Capi, arr_capi, index, clothe_name);
        index += 1;
    }
    
    StringSort(arr_capi, index);
    Clothes = WriteTree(Clothes, arr_capi, index);
  
    fclose(Capi);
    return Clothes;
}

void PrintClothe(TreeNode* Clothe){
    printf("CodArticolo: %d. %s -- S:%hu M:%hu L:%hu --- Prezzo: %.2f\n", Clothe->capo.code, 
    Clothe->capo.name, Clothe->capo.S, Clothe->capo.M, Clothe->capo.L, Clothe->capo.price);
}

void FindClothes(TreeNode* Clothes, char* choice){
    choice[0] = toupper(choice[0]);

    if(Clothes != NULL){
        FindClothes(Clothes->left, choice);
        if(strstr(Clothes->capo.name, choice) != NULL){
            PrintClothe(Clothes);
        }
        FindClothes(Clothes->right, choice);
    }
    return;
}

TreeNode* SelectMerch (TreeNode* Clothes, int code){
    if(Clothes->capo.code == code)
        return Clothes;

    TreeNode* Merch = Clothes;

    if(Clothes->left != NULL)
        Clothes = SelectMerch(Clothes->left, code);
    if((Merch->capo.code != code) && (Merch->right != NULL)){
        Merch = SelectMerch(Merch->right, code);
        if(Merch->capo.code == code)
            return Merch;
    }

    return Clothes;    
}

void Buy(User_Node* User, TreeNode* Merch){
    char size;
    bool correct = false;

    printf("Si è selezionato: ");
    PrintClothe(Merch);
    printf("Immettere la taglia desiderata: ");
    scanf(" %c", &size);

    size = toupper(size);
    // check taglia
      switch (size){
            case 'S':
                if(Merch->capo.S <= 0){
                    printf("----TAGLIA NON DISPONIBILE---");
                    return;
                }
                else{
                    if(User->user.balance > Merch->capo.price){
                        User->user.balance <= Merch->capo.price;
                        Merch->capo.S -= 1;
                    }
                }
                break;
            
            case 'M':
                if(Merch->capo.M <= 0){
                    printf("----TAGLIA NON DISPONIBILE---");
                    return;
                }
                else{
                    if(User->user.balance > Merch->capo.price){
                        User->user.balance <= Merch->capo.price;
                        Merch->capo.M -= 1;
                    }
                }
                break;

            case 'L':
                if(Merch->capo.L <= 0){
                    printf("----TAGLIA NON DISPONIBILE---");
                    return;
                }
                else{
                    if(User->user.balance > Merch->capo.price){
                        User->user.balance <= Merch->capo.price;
                        Merch->capo.L -= 1;
                    }
                }
                break;

            default:
                printf("Taglia non valida");
                return;
        }
}

FILE* PrintInFile(FILE* file, struct __capo clothe){
    fprintf(file, "\n%s S:%hu M:%hu L:%hu %f", clothe.name, clothe.S, clothe.M, clothe.L, clothe.price);
    return file;
}

void Write(TreeNode* Clothes, FILE* file){
    if(Clothes == NULL)
        return;

    file = PrintInFile(file, Clothes->capo);
    fseek(file, 0, SEEK_END);
    Write(Clothes->left, file);
    Write(Clothes->right, file);

    return;
}

void Rewrite_Clothes_File(TreeNode* Clothes){

    if(!Clothes)
        return;
    

    char new_line;

    FILE* W_capi = fopen(C_PATH, "w+");
    fprintf(W_capi, "%s S:%hu M:%hu L:%hu %f", Clothes->capo.name, Clothes->capo.S, 
                   Clothes->capo.M, Clothes->capo.L, Clothes->capo.price);
    Write(Clothes->left, W_capi);
    Write(Clothes->right, W_capi);

    fclose(W_capi);

    return;
}


void BuyMenu(User_Node* User, TreeNode* Clothes){

    char cat_choice[STRLEN];
    int cod_merch;
    
    

    while(true){
        printf("Che categoria si vuole visualizzare?\n");

        for(int i = 0; i < N_CATEGORIES; i++)
            printf("%s/", categories[i]);
        
        printf("\nImmettere categoria (exit per uscire): ");
        scanf("%s", cat_choice);

        if(strcmp(cat_choice, "exit") == 0)
            return;

        printf("\n\n --------------\n");
        FindClothes(Clothes, cat_choice);
        printf("\n\n --------------\n");

        printf("Imettere il codice dell'articolo da acquistare (-1 per cambiare categoria): ");
        scanf("%d", &cod_merch);

        if(cod_merch == -1)
            break;

        TreeNode* SelectedClothe = Initialize_Tree_Node(SelectedClothe);
        SelectedClothe = SelectMerch(Clothes, cod_merch);

        if(SelectedClothe != NULL){
            Buy(User, SelectedClothe);
        }

        Rewrite_Clothes_File(Clothes);
    }
}