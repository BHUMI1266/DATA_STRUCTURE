#include <stdio.h>
#include <stdlib.h>

struct node				
{
    int data;
    struct node* left;
    struct node* right;
};

struct node* newnode(int key) 
{
    struct node* tmp = (struct node*)malloc(sizeof(struct node));   //memory allocation for node

    tmp->data = key;
    tmp->left = NULL;
    tmp->right = NULL;
    return tmp;
}

void insert(struct node **root, int key) 
{
   
    if (*root == NULL) 
	{
        *root = newnode(key); 
        return;
    }
    
  
    if (key < (*root)->data) 
	{
        insert(&((*root)->left), key); // Pass address left 
    } 
	else 
	{
        insert(&((*root)->right), key); // Pass address  Right
    }
}


void inorder(struct node **root) //left ->root->right
{
    if (*root != NULL) 
	{
        inorder(&((*root)->left));
        printf(" %d ", (*root)->data); 
        inorder(&((*root)->right));
    }
}

void preorder(struct node **root) //root->left->right
{
    if (*root != NULL) 
	{
        printf("%d ", (*root)->data); 
        preorder(&((*root)->left));    
        preorder(&((*root)->right)); 
    }
}

void postorder(struct node **root)  //left->right->root
{
    if (*root != NULL) 
	{
        postorder(&((*root)->left));  
        postorder(&((*root)->right)); 
        printf("%d ", (*root)->data);  
    }
}

int main() 
{
    struct node* root = NULL;
    int ch, key;
    
    while (1) 
	{
        printf("\n1.Insert Node\n2.Inorder\n3.Preorder\n4.Postorder\n5.Exit\n");
        printf("Enter Your Choice: ");
        scanf("%d", &ch);
        
        switch (ch) 
		{
            case 1:
                printf("Enter Data In Node: ");
                scanf("%d", &key);
                insert(&root, key); 
                break;
            case 2:
                printf("Inorder Traversal: ");
                inorder(&root);
                printf("\n");
                break;
            case 3:
                printf("Preorder Traversal: ");
                preorder(&root);
                printf("\n");
                break;
            case 4:
                printf("Postorder Traversal: ");
                postorder(&root);
                printf("\n");
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid Choice..\n");
        }
    }
    return 0;
}
