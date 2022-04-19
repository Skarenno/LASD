#ifndef STD_HEAD
    #define STD_HEAD "standard_header.h"
    #include STD_HEAD
#endif

#ifndef G_WAITING
    #define G_WAITING "GestioneWaiting.c"
    #include G_WAITING
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
    Clothes = NULL;
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

WaitingNode* IsInStock(TreeNode* Clothes, WaitingNode* List, WaitingNode* Waited){

    bool is_stocked = false;

    if(Clothes != NULL){
        List = IsInStock(Clothes->left, List, Waited);
        if(strcmp(Clothes->capo.name, Waited->waiter.clothe) == 0){
            switch(Waited->waiter.size){
                case 'S':
                    if(Clothes->capo.S > 0){
                        printf("-- AGGIORNAMENTO -> %s  Taglia S:%hu\n", Clothes->capo.name, Clothes->capo.S);  
                        is_stocked = true;
                    }
                    break;

                case 'M':
                    if(Clothes->capo.M > 0){
                        printf("-- AGGIORNAMENTO -> %s  Taglia M: %hu\n", Clothes->capo.name, Clothes->capo.M);
                        is_stocked = true;
                    }
                    break;

                case 'L':
                    if(Clothes->capo.L > 0){
                        printf("-- AGGIORNAMENTO -> %s  Taglia L: %hu\n", Clothes->capo.name, Clothes->capo.L);
                        is_stocked = true;
                    }
                    break;

                default:
                    break;
            }

            if(is_stocked)
                List = RemoveWaiting(List, Waited);
        }
        List = IsInStock(Clothes->right, List ,Waited);
    }

    return List;
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

WaitingNode* Buy(User_Node* User, TreeNode* Merch, WaitingNode* List){
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
                    printf("\nAggiungo il capo alla lista d'attesa\n");
                    sleep(1);
                    List = AddWaiting(List, User->user.username, Merch->capo.name, 'S');
                    return List;
                }
                else{
                    if(User->user.balance > Merch->capo.price){
                        User->user.balance <= Merch->capo.price;
                        Merch->capo.S -= 1;
                        correct = true;
                        printf("\n--- ACQUISTO EFFETTUATO CON SUCCESSO ---");
                    }
                }
                break;
            
            case 'M':
                if(Merch->capo.M <= 0){
                    printf("----TAGLIA NON DISPONIBILE---");
                    printf("\nAggiungo il capo alla lista d'attesa\n");
                    sleep(1);
                    return List;
                    List = AddWaiting(List, User->user.username, Merch->capo.name, 'M');
                }
                else{
                    if(User->user.balance > Merch->capo.price){
                        User->user.balance <= Merch->capo.price;
                        Merch->capo.M -= 1;
                        correct = true;
                        printf("\n--- ACQUISTO EFFETTUATO CON SUCCESSO ---");

                    }
                }
                break;

            case 'L':
                if(Merch->capo.L <= 0){
                    printf("----TAGLIA NON DISPONIBILE---");
                    printf("\nAggiungo il capo alla lista d'attesa\n");
                    sleep(1);
                    List = AddWaiting(List, User->user.username, Merch->capo.name, 'L');
                    return List;
                }
                else{
                    if(User->user.balance > Merch->capo.price){
                        User->user.balance <= Merch->capo.price;
                        Merch->capo.L -= 1;
                        printf("\n--- ACQUISTO EFFETTUATO CON SUCCESSO ---");
                    }
                }
                break;

            default:
                printf("Taglia non valida");
                return List;
        }

    return List;
}

FILE* PrintInFile(FILE* file, struct __capo clothe){
    fprintf(file, "\n%s S:%hu M:%hu L:%hu %f", clothe.name, clothe.S, clothe.M, clothe.L, clothe.price);
    return file;
}

void WriteClothesInFile(TreeNode* Clothes, FILE* file){
    if(Clothes == NULL)
        return;

    file = PrintInFile(file, Clothes->capo);
    fseek(file, 0, SEEK_END);
    WriteClothesInFile(Clothes->left, file);
    WriteClothesInFile(Clothes->right, file);

    return;
}

void Rewrite_Clothes_File(TreeNode* Clothes){

    if(!Clothes)
        return;
    

    char new_line;

    FILE* W_capi = fopen(C_PATH, "w+");
    fprintf(W_capi, "%s S:%hu M:%hu L:%hu %f", Clothes->capo.name, Clothes->capo.S, 
                   Clothes->capo.M, Clothes->capo.L, Clothes->capo.price);
    WriteClothesInFile(Clothes->left, W_capi);
    WriteClothesInFile(Clothes->right, W_capi);

    fclose(W_capi);

    return;
}


WaitingNode* BuyMenu(User_Node* User, TreeNode* Clothes, WaitingNode* List){

    char cat_choice[STRLEN];
    int cod_merch;
    bool quit = false;

    while(!quit){
        printf("\n\nChe categoria di capo si vuole visualizzare?\n");

        for(int i = 0; i < N_CATEGORIES; i++)
            printf("%s/", categories[i]);
        
        printf("\nImmettere categoria (exit per uscire): ");
        scanf("%s", cat_choice);

        if(strcmp(cat_choice, "exit") == 0)
            return List;

        printf("\n\n --------------\n");
        FindClothes(Clothes, cat_choice);
        printf(" --------------\n\n");

        while(true){
            printf("Imettere il codice dell'articolo da acquistare (-1 per cambiare categoria): ");
            scanf("%d", &cod_merch);

            if(cod_merch == -1)
                break;

            TreeNode* SelectedClothe = Initialize_Tree_Node(SelectedClothe);
            SelectedClothe = SelectMerch(Clothes, cod_merch);

            if(User->user.balance < SelectedClothe->capo.price){
                printf("Non si dispone di abbastanza denaro\n");
                return List;
            }

            if(SelectedClothe != NULL){
                List = Buy(User, SelectedClothe, List);
            }

            Rewrite_Clothes_File(Clothes);
        }
    }
    return List;
}