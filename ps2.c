#include<stdio.h>
#include<stdlib.h>
  
typedef struct Node
{
    int key;
    int balance;
    int size;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
}node;
  
int balance(struct Node *N)
{
    if (N == NULL)
        return 0;
    return N->balance;
}

int max(int a, int b)
{
    return (a > b)? a : b;
}
  
struct Node* newNode(int key,struct Node* parent)
{
    struct Node* node = (struct Node*) malloc(sizeof(struct Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->parent = parent;
    node->balance = 1;
    node->size = 0;
    return(node);
}
  
struct Node *rightRotate(struct Node *y)
{
    struct Node *x = y->left;
    
    int buff_x_left_size = x->left ? (x->left->size+1) : 0;
    int buff_x_right_size = x->right ? (x->right->size+1) : 0;
    
    int buff_y_right_size = y->right ? (y->right->size+1) : 0;
    
    struct Node *T2 = x->right;
        
    y->left = T2;
    
    y->size = buff_x_right_size + buff_y_right_size;
    x->size = buff_x_left_size + 1 + y->size;
    
    y->balance = max(balance(y->left), balance(y->right))+1;
    x->balance = max(balance(x->left), balance(x->right))+1;
  
    return x;
}
  
struct Node *leftRotate(struct Node *x)
{
    int buff_x_left_size = x->left ? (x->left->size+1) : 0;
    
    struct Node *y = x->right;
    int buff_y_left_size = y->left ? (y->left->size+1) : 0;
    int buff_y_right_size = y->right ? (y->right->size+1) : 0;
    
    struct Node *T2 = y->left;
  
    y->left = x;
    x->right = T2;
    
    x->size = buff_x_left_size + buff_y_left_size;
    y->size = buff_y_right_size + x->size + 1;
  
    x->balance = max(balance(x->left), balance(x->right))+1;
    y->balance = max(balance(y->left), balance(y->right))+1;
  
    return y;
}
  
int getBalance(struct Node *N)
{
    if (N == NULL)
        return 0;
    return balance(N->left) - balance(N->right);
}

void update_parent_size(struct Node* node)
{
    while (node->parent)
    {
        node->parent->size += 1;
        node = node->parent;
    }
}
  
struct Node* insert(struct Node* node, int key, struct Node* parent)
{
    if (node == NULL)
    {
        struct Node * new = newNode(key,parent);
        update_parent_size(new);
        return new;
    }
  
    if (key < node->key) node->left = insert(node->left,key,node->left);
    
    else if (key >= node->key) node->right = insert(node->right,key,node->right);
    
    else return node;
  
    node->balance = 1 + max(balance(node->left),balance(node->right));
  
    int balance = getBalance(node);
  
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);
  
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);
  
    if (balance > 1 && key > node->left->key)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }
  
    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    
    return node;
}

int calculate_smaller_elements(int target,struct Node *root)
{
    int res = 0;
    while(1)
    {
        if(root->key==target) break;
        else if(root->key<target)
        {
            if(root->left)
                res = res + root->left->size + 1 + 1;
            else res += 1;
            root = root->right;
            
        }
        else
        {
            res = res;
            root = root->left;
        }
    }
    return res;
}

void free_tree(struct Node* root)
{
    if(!root) return;
    
    free_tree(root->left);
    free_tree(root->right);
    
    free(root);
}
  
int main()
{
    int value = -1;
    
    //test 0
    struct Node* root = NULL;
    printf("test 0\n");
    int test_0[7] = {3,5,1,4,7,6,2};
    int res[7];
    
    for(int i=6;i>-1;--i)
    {
        root = insert(root,test_0[i],NULL);
        value = calculate_smaller_elements(test_0[i],root);
        res[i] = value;
    }
    
    for(int i=0;i<7;++i)
        printf("%d ",test_0[i]);
    printf("\n");
    
    for(int i=0;i<7;++i)
        printf("%d ",res[i]);
    printf("\n");
    
    free_tree(root);
    
    //test 1
    printf("test 1\n");
    struct Node* root_1 = NULL;
    int test_1[7] = {1,2,3,4,5,6,7};
    for(int i=0;i<7;++i)
        printf("%d ",test_1[i]);
    printf("\n");
    for(int i=6;i>-1;--i)
    {
        root_1 = insert(root_1,test_1[i],NULL);
        value = calculate_smaller_elements(test_1[i],root_1);
        res[i] = value;
    }
    
    for(int i=0;i<7;++i)
        printf("%d ",res[i]);
    printf("\n");
    free_tree(root_1);
    
    //test 2
    printf("test 2\n");
    struct Node* root_2 = NULL;
    int test_2[7] = {7,6,5,4,3,2,1};
    for(int i=0;i<7;++i)
        printf("%d ",test_2[i]);
    printf("\n");
    for(int i=6;i>-1;--i)
    {
        root_2 = insert(root_2,test_2[i],NULL);
        value = calculate_smaller_elements(test_2[i],root_2);
        res[i] = value;
    }
    
    for(int i=0;i<7;++i)
        printf("%d ",res[i]);
    printf("\n");
    free_tree(root_1);
  
    return 0;
}
