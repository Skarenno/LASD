#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#ifndef STRLEN
    #define STRLEN 100
#endif


struct __capo{
    char name[STRLEN];
    unsigned short int S, M, L;
    float price;
    int code;
};

typedef struct tr_node{
    struct __capo capo;
    struct tr_node *left, *right;
}TreeNode;


bool IsUsable(FILE* file){
    int size;

    if(file != NULL){
        fseek(file, 0, SEEK_END);
        size = ftell(file);
        fseek(file, 0, SEEK_SET);

        if(size > 0)
            return true;
    }
    return false;
}

void StringSort(struct __capo *array, int length){
    int j;
    struct __capo tmp;
    if(length == 1)
        return;
    
    for(int i = 1; i < length; i++){
        tmp = array[i];
        j = i - 1;

        while(j >= 0 && strcmp(array[j].name, tmp.name) < 0){
            array[j + 1] = array[j];
            j = j - 1;
        }
        array[j + 1] = tmp;
    }
}


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
    leaf->capo.code = capo.code;
    
    leaf->left = leaf->right = NULL;
    return leaf;
}

TreeNode* InsertLeaf (TreeNode* Root, struct __capo capo){
    if(Root == NULL){
        Root = Initialize_Tree_Node(Root);
        Root = WriteLeaf(Root, capo);
        return Root;
    }

    if(strcmp(Root->capo.name, capo.name) >= 0){
        Root->left = InsertLeaf(Root->left, capo);
    }
    else{
        Root->right = InsertLeaf(Root->right, capo);
    }
    
    return Root;
}

TreeNode* MinimumValue(TreeNode* Leaf){
    TreeNode* temp = Initialize_Tree_Node(temp);

    while(temp != NULL && temp->left != NULL){
        temp = temp->left;
    }

    return temp;
}

TreeNode* DeleteLeaf (TreeNode* Root, struct __capo capo){
    if(Root == NULL)
        return Root;

    TreeNode* temp = Initialize_Tree_Node(temp);

    if(strcmp(Root->capo.name, capo.name) > 0)
        Root->left = DeleteLeaf(Root->left, capo);
    
    else if (strcmp(Root->capo.name, capo.name) < 0)
        Root->right = DeleteLeaf(Root->right, capo);

    else{
        if(Root->left == NULL && Root->right == NULL){
            free(Root);
            return NULL;
        }

        if(Root->left == NULL){
            temp = Root->right;
            free(Root);
            return temp;
        }
        else if(Root->right == NULL){        
            temp = Root->left;
            free(Root);
            return temp;
        }

        temp = MinimumValue(Root->right);
        Root = WriteLeaf(Root, temp->capo);
        Root->right = DeleteLeaf(Root->right, temp->capo);
    }
    return Root;
}

TreeNode* WriteTree(TreeNode* Root, struct __capo* capi, int index){
    if(index == 0)
        return Root;
    
    int start = index/2;

    if(index == 1){
        Root= InsertLeaf(Root, capi[index - 1]);
        return Root;
    }
    
    Root = InsertLeaf(Root, capi[start]);
    for(int i = 0; i < index; i++)
        if(i!= start)
            InsertLeaf(Root, capi[i]);


    return Root;
}


void PrintInOrder(TreeNode* Root){
    if(Root != NULL){
        PrintInOrder(Root->left);
        printf("%s\n", Root->capo.name);
        PrintInOrder(Root->right);
    }

    return;
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
    Node->user.username[0] = '\0';
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




struct __waiter{
    char name[STRLEN];
    char clothe[STRLEN];
    char size;
};

typedef struct waiting_l{
    struct __waiter waiter;
    struct waiting_l* next;
}WaitingNode;


WaitingNode* Initialize_Waiting_Node(WaitingNode* Node){
    Node = (WaitingNode*)malloc(sizeof(WaitingNode));
    Node->waiter.name[0] = '\0';
    Node->next = NULL;
    return Node;
}

