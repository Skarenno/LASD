#ifndef G_UTENTI
    #define G_UTENTI "GestioneUtenti.c"
    #include G_UTENTI
#endif
#ifndef G_WAITING
    #define G_WAITING "GestioneWaiting.c"
    #include G_WAITING
#endif
#ifndef G_CAPI
    #define G_CAPI "GestioneCapi.c"
    #include G_CAPI
#endif
#ifndef STRUCTS 
    #define STRUCTS "structs.c"
    #include STRUCTS
#endif
#ifndef G_ADMIN
    #define G_ADMIN "GestioneAdmin.c"
    #include G_ADMIN
#endif

/*************************************************************************************************************************/

WaitingNode* SearchWaiting(User_Node* User, TreeNode* Clothes, WaitingNode* List);

// STRUCTS.C

    /**** TREE ****/
    TreeNode* Initialize_Tree_Node(TreeNode* Node);
    TreeNode* WriteLeaf(TreeNode* leaf, struct __capo capo);
    TreeNode* InsertLeaf (TreeNode* Root, struct __capo capo);
    TreeNode* MinimumValue(TreeNode* Leaf);
    TreeNode* DeleteLeaf (TreeNode* Root, struct __capo capo);
    TreeNode* WriteTree(TreeNode* Root, struct __capo* capi, int index);
    void FreeTree(TreeNode* Root);

    void PrintInOrder(TreeNode* Root);


    /*** USERS LISTS ****/
    User_Node* Initialize_User_Node(User_Node* Node);
    User_Node* FindUser(char* username, User_Node* Head);
    User_Node* InsertNode(User_Node* Head, User_Node* NewNode);
    void FreeList(User_Node* Head);

    /**** WAITINGS ****/
    WaitingNode* Initialize_Waiting_Node(WaitingNode* Node);


    /**** OTHERS ****/
    bool IsUsable(FILE* file);
    void StringSort(struct __capo *array, int length);


// GESTIONEUTENTI.C

    void Rewrite_User_File(User_Node* Head);
    User_Node* Read_User_List (FILE* file, User_Node* Head);
    int VerificaPassword(User_Node* Head, char* username, char* password);
    void Register( User_Node* Head);
    char* Accesso(char* username, User_Node* Head);
    char* FirstScreen(char* user, User_Node* Head);
    float GetBalance(char* user);
    void PrintOptions();
    float Withdraw(float balance);
    float Load (float balance);
    void  WelcomeScreen(User_Node* User);



// GESTIONECAPI.C

    struct __capo* LoadCapo(FILE* file, struct __capo* array, int arr_index, char* name);
    TreeNode* Read_Clothes_File(TreeNode* Clothes, FILE* Capi);
    void PrintClothe(TreeNode* Clothe);
    void FindClothes(TreeNode* Clothes, char* choice);
    WaitingNode* IsInStock(TreeNode* Clothes, WaitingNode* List, WaitingNode* Waited);
    TreeNode* SelectMerch (TreeNode* Clothes, int code);
    WaitingNode* Buy(User_Node* User, TreeNode* Merch, WaitingNode* List);
    FILE* PrintInFile(FILE* file, struct __capo clothe);
    void WriteClothesInFile(TreeNode* Clothes, FILE* file);
    void Rewrite_Clothes_File(TreeNode* Clothes);
    WaitingNode* BuyMenu(User_Node* User, TreeNode* Clothes, WaitingNode* List);



// GESTIONEWAITING.C

    WaitingNode* Read_Waiting_List(FILE* file, WaitingNode* Head);
    void Rewrite_Waiting_File(WaitingNode* Head);
    WaitingNode* RemoveWaiting(WaitingNode* Head, WaitingNode* Node);
    WaitingNode* WriteNode (char* name, char* clothe_name, char size);
    WaitingNode* AddWaiting(WaitingNode* List, char* name, char* clothe_name, char size);

// GESTIONEADMIN.C

    void PrintAdminOptions();
    void Rewrite_Admin_File(User_Node* Head);
    TreeNode* ChangeSizes(TreeNode* Clothe, char size, int choice);
    TreeNode* ChangeClothes(TreeNode* Clothes);
    TreeNode* AddClothe(TreeNode* Clothes);




/*************************************************************************************************************************/


    







