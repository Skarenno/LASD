#ifndef STD_HEAD
    #define STD_HEAD "standard_header.h"
    #include STD_HEAD
#endif
#ifndef STRUCTS 
    #define STRUCTS "structs.c"
    #include STRUCTS
#endif
#ifndef G_CAPI
    #define G_CAPI "GestioneCapi.c"
    #include G_CAPI
#endif

void Rewrite_Admin_File(User_Node* Head){
    User_Node* Cursor = Initialize_User_Node(Cursor);
    Cursor = Head;

    FILE* file = fopen(AU_PATH, "w+");
    if(!file){
        printf("AOO");
        exit(EXIT_FAILURE);
    }
    while(Cursor){
        if(Cursor->user.username[0] != '\0')
            fprintf(file, "%s %s %.2f\n", Cursor->user.username, Cursor->user.password, Cursor->user.balance);
            Cursor = Cursor->next;
    }

    fclose(file);
}

TreeNode* ChangeSizes(TreeNode* Clothe, char size, int choice){
    size = toupper(size);
    int quantity = 0;

    printf("Di quanto si vuole aggiungere/rimuovere? ");
    scanf("%d", &quantity);

    switch (size){
        case 'S':
            if(choice == 2){
                if (Clothe->capo.S >= quantity){
                    Clothe->capo.S -= quantity;
                }
                else{
                    Clothe->capo.S = 0;
                }
                printf("\n RIMOZIONE EFFETTUATA");
            }
            if(choice == 1){
                Clothe->capo.S += quantity;
            }
            break;

        case 'M':
            if(choice == 2){
                if (Clothe->capo.M >= quantity){
                    Clothe->capo.M -= quantity;
                }
                else{
                    Clothe->capo.M = 0;
                }
                printf("\n RIMOZIONE EFFETTUATA");
            }
            if(choice == 1){
                Clothe->capo.M += quantity;
            }
            break;

        case 'L':
            if(choice == 2){
                if (Clothe->capo.L >= quantity){
                    Clothe->capo.L -= quantity;
                }
                else{
                    Clothe->capo.L = 0;
                }
                printf("\n RIMOZIONE EFFETTUATA");
            }
            if(choice == 1){
                Clothe->capo.L += quantity;
            }
            break;
        default:
            printf("\n\n --- TAGLIA NON VALIDA ---\n\n");
            break;
    }

    return Clothe;
}


TreeNode* ChangeClothes(TreeNode* Clothes){
    char clothe[STRLEN];
    char size;
    int code;
    int selection;
    int choice;

    TreeNode* Selected;

    printf("\nInserire il nome del capo da rimuovere: ");
    scanf("%s", clothe);
    printf("SONO STATI TROVATI I SEGUENTI CAPI\n");
    FindClothes(Clothes, clothe);

    printf("Inserire il codice del capo da modificare (-1 per uscire o se non vengono mostrati capi): ");
    scanf("%d", &code);

    if(isdigit(code)){
        printf("--VALORE ERRATO---");
        return Clothes;
    }

    if(code == -1){
        return Clothes;
    }

    Selected = SelectMerch(Clothes, code);

    printf("Si è selezionato: ");
    PrintClothe(Selected);

    printf("(1) [Rimozione totale del capo]\n(2) [Cambiare determinate taglie]\nImmettere scelta: ");
    scanf("%d", &selection);

    if(isdigit(selection)){
        printf("VALORE IMPOSSIBILE");
        return Clothes;
    }

    switch(selection){
        case 1:
            Clothes = DeleteLeaf(Clothes, Selected->capo);
            Rewrite_Clothes_File(Clothes);
            printf("\n\n----CAPO RIMOSSO----\n\n");

            break;

        case 2:
            printf("Si vuole aggiungere (1) o rimuovere (2) taglie? (-1 per tornare indietro) -");
            scanf("%d", &choice);
            printf("Che taglia si vuole cambiare? (S/M/L) -");
            scanf(" %c", &size);
            Selected = ChangeSizes(Selected, size, choice);
            Rewrite_Clothes_File(Clothes);
            break;

        default:
            printf("\nSelezione non valida.");
            break;
    }

    return Clothes;
}


TreeNode* AddClothe(TreeNode* Clothes){
    struct __capo clothe;

    printf("Inserire nome capo: ");
    scanf("%s", clothe.name);
    printf("Numero di taglie S: ");
    scanf("%hu", &clothe.S);
    printf("Numero di taglie M: ");
    scanf("%hu", &clothe.M);
    printf("Numero di taglie L: ");
    scanf("%hu", &clothe.L);
    printf("\nPrezzo del capo: ");
    scanf("%f", &clothe.price);

    if(isdigit(clothe.S) || isdigit(clothe.M) || isdigit(clothe.L) || isdigit(clothe.price)){
        printf("\n\nVALORI IMPOSSIBILI\n\n");
        return Clothes;
    }

    printf("\n CAPO INSERITO CORRETTAMENTE\n");
    Clothes = InsertLeaf(Clothes, clothe);
    return Clothes;
}
