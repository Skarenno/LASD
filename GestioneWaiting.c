#ifndef STD_HEAD
    #define STD_HEAD "standard_header.h"
    #include STD_HEAD
#endif


WaitingNode* Read_Waiting_List(FILE* file, WaitingNode* Head){
    if(Head->next == NULL)
        Head->next = Initialize_Waiting_Node(Head);

    if(!feof(file)){
        fscanf(file, "%s %s %c", Head->waiter.name, Head->waiter.clothe, &Head->waiter.size);
        Head->next = Read_Waiting_List(file, Head->next);
    }
    else{
        free(Head);
        return NULL;
    }
    
    return Head;     
}

FILE* Rewrite_Waiting_File(WaitingNode* Head){
    WaitingNode* Cursor = Initialize_Waiting_Node(Cursor);
    Cursor = Head;

    FILE* file = fopen(W_PATH, "w+");

    while(Cursor){
        if(Cursor->waiter.name [0] != '\0')
            fprintf(file, "%s %s %c\n", Cursor->waiter.name, Cursor->waiter.clothe, Cursor->waiter.size);
            Cursor = Cursor->next;
    }

    fseek(file, 0, SEEK_SET);
    return file;
}

WaitingNode* RemoveWaiting(WaitingNode* Head, WaitingNode* Node){
    WaitingNode* Cur = Initialize_Waiting_Node(Cur);
    WaitingNode* Prev = Initialize_Waiting_Node(Prev);

    Cur = Head;

    while (Cur){
        if(strcmp(Cur->waiter.clothe, Node->waiter.clothe) == 0 && strcmp(Cur->waiter.name, Node->waiter.name) == 0){
            if(Cur == Head){
                Cur = Head->next;
                free(Head);
                return Cur;
            }

            Prev->next = Cur->next;
            free(Cur);
            return Head;
        }
        Prev = Cur;
        Cur = Cur->next;
    }
    return Head;
    
}

WaitingNode* WriteNode (char* name, char* clothe_name, char size){
    WaitingNode* New = Initialize_Waiting_Node(New);
    strcpy(New->waiter.name, clothe_name);
    strcpy(New->waiter.name, name);
    New->waiter.size = size;

    return New;
}

WaitingNode* AddWaiting(WaitingNode* List, char* name, char* clothe_name, char size){
    WaitingNode* Cur = Initialize_Waiting_Node(Cur);
    Cur->next = List;

    strcpy(Cur->waiter.name, name);
    strcpy(Cur->waiter.clothe, clothe_name);
    Cur->waiter.size = size;

    return Cur;
}
