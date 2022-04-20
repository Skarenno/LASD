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

TreeNode* RemoveClothe(TreeNode* Clothes){
    char clothe[STRLEN];
    int code;
    int selection;

    TreeNode* Selected;

    printf("\nInserire il nome del capo da rimuovere: ");
    scanf("%s", clothe);
    printf("SONO STATI TROVATI I SEGUENTI CAPI\n");
    FindClothes(Clothes, clothe);

    printf("Inserire il codice del capo da rimuovere (-1 per uscire o se non vengono mostrati capi): ");
    scanf("%d", &code);

    if(isdigit(code)){
        printf("--VALORE ERRATO---");
        return Clothes;
    }

    if(code == -1){
        // ESCI
    }

    Selected = SelectMerch(Clothes, code);

    printf("Si è selezionato: ");
    PrintClothe(Selected);

    printf("(1) Rimozione totale del capo\n(2) Rimozione di determinate taglie\nImmettere scelta: ");
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
    }
    
}