#ifndef STRLEN
    #define STRLEN 30
#endif

#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct __capo{
    char name[STRLEN];
    unsigned short int S, M, L;
    float price;
};

typedef struct tr_node{
    struct __capo capo;
    struct tr_node *left, *right;
}TreeNode;

TreeNode* Initialize_Tree_Node(TreeNode* Node){
    Node = (TreeNode*)malloc(sizeof(TreeNode));
    Node->left = NULL;
    Node->right = NULL;
    return Node;
}

TreeNode* WriteLeaf(TreeNode* leaf, struct __capo capo){
    strcpy(leaf->capo.name, capo.name);
    leaf->capo.S = capo.S;
    leaf->capo.M = capo.M;
    leaf->capo.L = capo.L;
    leaf->capo.price = capo.price;
    
    leaf->left = leaf->right = NULL;
    return leaf;
}

TreeNode* InsertLeaf (TreeNode* Root, struct __capo capo){
    if(Root == NULL)
        Root = Initialize_Tree_Node(Root);
        WriteLeaf(Root, capo);

    if(strcmp(Root->capo.name, capo.name) <= 0){
        Root->left = WriteLeaf(Root->left, capo);
    }
    else{
        Root->right = WriteLeaf(Root->right, capo);
    }
    
    return Root;
}


void StringSort(struct __capo *array, int length){
    int j;
    struct __capo tmp;

    for(int i = 1; i < length; i++){
        tmp = array[i];

        while(j >= 0 && strcmp(array[j].name, tmp.name) < 0){
            array[j + 1] = array[j];
            j = j - 1;
        }
        array[j + 1] = tmp;
    }
}

TreeNode* WriteTree(TreeNode* Root, struct __capo capi[], int index){
    int start = index/2;
    Root = InsertLeaf(Root, capi[start]);
    for(int i = 0; i < index; i++)
        InsertLeaf(Root, capi[i]);


    return Root;
}


struct __user{
    char username[STRLEN];
    char password[STRLEN];
    float balance;
};

typedef struct user_node{
    struct __user user;
    struct user_node* next;
}User_Node;

User_Node* Initialize_User_Node(User_Node* Node){
    Node = (User_Node*)malloc(sizeof(User_Node));
    Node->next = NULL;

    return Node;
}

User_Node* FindUser(char* username, User_Node* Head){
    User_Node* Cursor = Initialize_User_Node(Cursor);
    Cursor = Head;

    while(Cursor){
        if(strcmp(Cursor->user.username, username) == 0)
            return Cursor;
        else{
            Cursor = Cursor->next;
        }
    }
    
    return NULL;
}

User_Node* InsertNode(User_Node* Head, User_Node* NewNode){
    NewNode = Initialize_User_Node(NewNode);
    NewNode = Head;
    User_Node* prev = Initialize_User_Node(prev);
    prev = Head;

    while(NewNode){
        prev = NewNode;
        NewNode = NewNode->next;
    }
    NewNode = Initialize_User_Node(NewNode);
    prev->next = NewNode;
    return NewNode;
}