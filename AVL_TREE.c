	#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *lptr;
    struct node *rptr;
};

/* Create Node */
int createnode(int ele, struct node **newnode)
{
    *newnode = (struct node *)malloc(sizeof(struct node));

    if (*newnode == NULL)
        return 0;

    (*newnode)->data = ele;
    (*newnode)->lptr = NULL;
    (*newnode)->rptr = NULL;

    return 1;
}

/* Height */
int height(struct node *root)
{
    int lh, rh;

    if (root == NULL)
        return 0;

    lh = height(root->lptr);
    rh = height(root->rptr);

    if (lh > rh)
        return lh + 1;
    else
        return rh + 1;
}

/* Balance Factor */
int balancefactor(struct node *root)
{
    if (root == NULL)
        return 0;

    return height(root->lptr) - height(root->rptr);
}

/* Right Rotation - LL Case */
void rightrotate(struct node **root)
{
    struct node *temp;

    temp = (*root)->lptr;

    (*root)->lptr = temp->rptr;

    temp->rptr = *root;

    *root = temp;
}

/* Left Rotation - RR Case */
void leftrotate(struct node **root)
{
    struct node *temp;

    temp = (*root)->rptr;

    (*root)->rptr = temp->lptr;

    temp->lptr = *root;

    *root = temp;
}

/* Insert */
void insert(struct node **root, int ele)
{
    int bf;
    struct node *newnode;

    /* Create new node */
    if (*root == NULL)
    {
        if (createnode(ele, &newnode))
            *root = newnode;

        return;
    }

    /* BST insertion */
    if (ele < (*root)->data)
    {
        insert(&((*root)->lptr), ele);
    }
    else if (ele > (*root)->data)
    {
        insert(&((*root)->rptr), ele);
    }
    else
    {
        printf("Duplicate value not allowed.\n");
        return;
    }

    /* Balance Factor */
    bf = balancefactor(*root);

    /* LL Case */
    if (bf > 1 && ele < (*root)->lptr->data)
    {
        rightrotate(root);
    }

    /* RR Case */
    else if (bf < -1 && ele > (*root)->rptr->data)
    {
        leftrotate(root);
    }

    /* LR Case */
    else if (bf > 1 && ele > (*root)->lptr->data)
    {
        leftrotate(&((*root)->lptr));
        rightrotate(root);
    }

    /* RL Case */
    else if (bf < -1 && ele < (*root)->rptr->data)
    {
        rightrotate(&((*root)->rptr));
        leftrotate(root);
    }
}

/* Find Minimum */
int findmin(struct node *root)
{
    struct node *curr;

    curr = root;

    while (curr->lptr != NULL)
    {
        curr = curr->lptr;
    }

    return curr->data;
}

/* Delete */
void deleteNode(struct node **root, int ele)
{
    struct node *temp;
    int bf;

    if (*root == NULL)
        return;

    /* Search left */
    if (ele < (*root)->data)
    {
        deleteNode(&((*root)->lptr), ele);
    }

    /* Search right */
    else if (ele > (*root)->data)
    {
        deleteNode(&((*root)->rptr), ele);
    }

    /* Node found */
    else
    {
        /* No child */
        if ((*root)->lptr == NULL && (*root)->rptr == NULL)
        {
            free(*root);
            *root = NULL;
            return;
        }

        /* Only right child */
        else if ((*root)->lptr == NULL)
        {
            temp = (*root)->rptr;

            free(*root);

            *root = temp;
        }

        /* Only left child */
        else if ((*root)->rptr == NULL)
        {
            temp = (*root)->lptr;

            free(*root);

            *root = temp;
        }

        /* Two children */
        else
        {
            temp = (*root)->rptr;

            while (temp->lptr != NULL)
            {
                temp = temp->lptr;
            }

            (*root)->data = temp->data;

            deleteNode(&((*root)->rptr), temp->data);
        }
    }

    if (*root == NULL)
        return;

    /* Balance Factor */
    bf = balancefactor(*root);

    /* LL Case */
    if (bf > 1 && balancefactor((*root)->lptr) >= 0)
    {
        rightrotate(root);
    }

    /* LR Case */
    else if (bf > 1 && balancefactor((*root)->lptr) < 0)
    {
        leftrotate(&((*root)->lptr));
        rightrotate(root);
    }

    /* RR Case */
    else if (bf < -1 && balancefactor((*root)->rptr) <= 0)
    {
        leftrotate(root);
    }

    /* RL Case */
    else if (bf < -1 && balancefactor((*root)->rptr) > 0)
    {
        rightrotate(&((*root)->rptr));
        leftrotate(root);
    }
}

/* Search */
int searchBST(struct node *root, int ele)
{
    struct node *curr;

    curr = root;

    while (curr != NULL)
    {
        if (curr->data == ele)
            return 1;

        if (ele < curr->data)
            curr = curr->lptr;
        else
            curr = curr->rptr;
    }

    return 0;
}

/* Inorder */
void inorder(struct node *root)
{
    if (root != NULL)
    {
        inorder(root->lptr);

        printf("%d ", root->data);

        inorder(root->rptr);
    }
}

/* Preorder */
void preorder(struct node *root)
{
    if (root != NULL)
    {
        printf("%d ", root->data);

        preorder(root->lptr);

        preorder(root->rptr);
    }
}

/* Main */
void main()
{
    struct node *root = NULL;

    int ch;
    int ele;
    int result;

    while (1)
    {
        printf("\n\n----- AVL TREE -----\n");

        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Search\n");
        printf("4. Inorder\n");
        printf("5. Preorder\n");
        printf("6. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch)
        {
            case 1:

                printf("Enter element: ");
                scanf("%d", &ele);

                insert(&root, ele);

                printf("Element inserted.\n");

                break;

            case 2:

                printf("Enter element to delete: ");
                scanf("%d", &ele);

                result = searchBST(root, ele);

                if (result == 1)
                {
                    deleteNode(&root, ele);

                    printf("Element deleted.\n");
                }
                else
                {
                    printf("Element not found.\n");
                }

                break;

            case 3:

                printf("Enter element to search: ");
                scanf("%d", &ele);

                result = searchBST(root, ele);

                if (result == 1)
                    printf("Element Found.\n");
                else
                    printf("Element Not Found.\n");

                break;

            case 4:

                printf("Inorder Traversal: ");

                inorder(root);

                break;

            case 5:

                printf("Preorder Traversal: ");

                preorder(root);

                break;

            case 6:

                exit(0);

            default:

                printf("Invalid choice.\n");
        }
    }
}