#include <stdio.h>
#include <stdlib.h>

#define T 3

typedef struct BNode
{
    int keys[2 * T - 1];
    struct BNode *child[2 * T];
    int n;
    int leaf;
} BNode;

BNode *root = NULL;


/* Create Node */
BNode *createNode(int leaf)
{
    BNode *p;
    int i;

    p = (BNode *)malloc(sizeof(BNode));

    p->n = 0;
    p->leaf = leaf;

    for (i = 0; i < 2 * T; i++)
        p->child[i] = NULL;

    return p;
}


/* Display B-Tree */
void display(BNode *p)
{
    int i;

    if (p == NULL)
        return;

    for (i = 0; i < p->n; i++)
    {
        if (!p->leaf)
            display(p->child[i]);

        printf("%d ", p->keys[i]);
    }

    if (!p->leaf)
        display(p->child[i]);
}


/* Search */
BNode *search(BNode *p, int key)
{
    int in;

    if (p == NULL)
        return NULL;

    in = 0;

    while (in < p->n && key > p->keys[in])
        in++;

    if (in < p->n && key == p->keys[in])
        return p;

    if (p->leaf)
        return NULL;

    return search(p->child[in], key);
}


/* Split Child */
void splitChild(BNode *prent, int in, BNode *fullc)
{
    BNode *newc;
    int i;

    newc = createNode(fullc->leaf);

    newc->n = T - 1;

    /* Copy second half of keys */
    for (i = 0; i < T - 1; i++)
        newc->keys[i] = fullc->keys[i + T];

    /* Copy children */
    if (!fullc->leaf)
    {
        for (i = 0; i < T; i++)
            newc->child[i] = fullc->child[i + T];
    }

    fullc->n = T - 1;

    /* Move parent's children */
    for (i = prent->n; i >= in + 1; i--)
        prent->child[i + 1] = prent->child[i];

    prent->child[in + 1] = newc;

    /* Move parent's keys */
    for (i = prent->n - 1; i >= in; i--)
        prent->keys[i + 1] = prent->keys[i];

    prent->keys[in] = fullc->keys[T - 1];

    prent->n++;
}


/* Insert in Non-Full Node */
void insertNonFull(BNode *p, int key)
{
    int in;

    in = p->n - 1;

    if (p->leaf)
    {
        /* Shift keys */
        while (in >= 0 && key < p->keys[in])
        {
            p->keys[in + 1] = p->keys[in];
            in--;
        }

        p->keys[in + 1] = key;
        p->n++;
    }
    else
    {
        while (in >= 0 && key < p->keys[in])
            in--;

        in++;

        /* If child is full */
        if (p->child[in]->n == 2 * T - 1)
        {
            splitChild(p, in, p->child[in]);

            if (key > p->keys[in])
                in++;
        }

        insertNonFull(p->child[in], key);
    }
}


/* Insert */
void insert(int key)
{
    BNode *newc;

    if (root == NULL)
    {
        root = createNode(1);

        root->keys[0] = key;
        root->n = 1;

        return;
    }

    /* Duplicate check */
    if (search(root, key) != NULL)
    {
        printf("Key %d already exists.\n", key);
        return;
    }

    /* Root is full */
    if (root->n == 2 * T - 1)
    {
        newc = createNode(0);

        newc->child[0] = root;

        splitChild(newc, 0, root);

        root = newc;
    }

    insertNonFull(root, key);
}


/* Get Predecessor */
int getPredecessor(BNode *p)
{
    while (!p->leaf)
        p = p->child[p->n];

    return p->keys[p->n - 1];
}


/* Get Successor */
int getSuccessor(BNode *p)
{
    while (!p->leaf)
        p = p->child[0];

    return p->keys[0];
}


/* Merge */
void merge(BNode *p, int in)
{
    BNode *fullc;
    BNode *sibl;
    int i;

    fullc = p->child[in];
    sibl = p->child[in + 1];

    fullc->keys[T - 1] = p->keys[in];

    /* Copy sibling keys */
    for (i = 0; i < sibl->n; i++)
        fullc->keys[i + T] = sibl->keys[i];

    /* Copy sibling children */
    if (!fullc->leaf)
    {
        for (i = 0; i <= sibl->n; i++)
            fullc->child[i + T] = sibl->child[i];
    }

    fullc->n = fullc->n + sibl->n + 1;

    /* Move parent keys */
    for (i = in + 1; i < p->n; i++)
        p->keys[i - 1] = p->keys[i];

    /* Move parent children */
    for (i = in + 2; i <= p->n; i++)
        p->child[i - 1] = p->child[i];

    p->n--;

    free(sibl);
}


/* Borrow From Previous Sibling */
void borrowFromPrev(BNode *p, int in)
{
    BNode *fullc;
    BNode *sibl;
    int i;

    fullc = p->child[in];
    sibl = p->child[in - 1];

    /* Shift child's keys */
    for (i = fullc->n - 1; i >= 0; i--)
        fullc->keys[i + 1] = fullc->keys[i];

    /* Shift child's children */
    if (!fullc->leaf)
    {
        for (i = fullc->n; i >= 0; i--)
            fullc->child[i + 1] = fullc->child[i];
    }

    fullc->keys[0] = p->keys[in - 1];

    if (!fullc->leaf)
        fullc->child[0] = sibl->child[sibl->n];

    p->keys[in - 1] = sibl->keys[sibl->n - 1];

    fullc->n++;
    sibl->n--;
}


/* Borrow From Next Sibling */
void borrowFromNext(BNode *p, int in)
{
    BNode *fullc;
    BNode *sibl;
    int i;

    fullc = p->child[in];
    sibl = p->child[in + 1];

    fullc->keys[fullc->n] = p->keys[in];

    if (!fullc->leaf)
        fullc->child[fullc->n + 1] = sibl->child[0];

    p->keys[in] = sibl->keys[0];

    /* Shift sibling keys */
    for (i = 1; i < sibl->n; i++)
        sibl->keys[i - 1] = sibl->keys[i];

    /* Shift sibling children */
    if (!sibl->leaf)
    {
        for (i = 1; i <= sibl->n; i++)
            sibl->child[i - 1] = sibl->child[i];
    }

    fullc->n++;
    sibl->n--;
}


/* Fill Child */
void fill(BNode *p, int in)
{
    if (in != 0 && p->child[in - 1]->n >= T)
    {
        borrowFromPrev(p, in);
    }
    else if (in != p->n && p->child[in + 1]->n >= T)
    {
        borrowFromNext(p, in);
    }
    else
    {
        if (in != p->n)
            merge(p, in);
        else
            merge(p, in - 1);
    }
}


/* Delete From Node */
void deleteFromNode(BNode *p, int key)
{
    int in;
    int pre;
    int suc;
    int flag;
    int i;

    in = 0;

    while (in < p->n && p->keys[in] < key)
        in++;

    /* Key found */
    if (in < p->n && p->keys[in] == key)
    {
        /* Leaf Node */
        if (p->leaf)
        {
            for (i = in + 1; i < p->n; i++)
                p->keys[i - 1] = p->keys[i];

            p->n--;
        }

        /* Internal Node */
        else
        {
            if (p->child[in]->n >= T)
            {
                pre = getPredecessor(p->child[in]);

                p->keys[in] = pre;

                deleteFromNode(p->child[in], pre);
            }
            else if (p->child[in + 1]->n >= T)
            {
                suc = getSuccessor(p->child[in + 1]);

                p->keys[in] = suc;

                deleteFromNode(p->child[in + 1], suc);
            }
            else
            {
                merge(p, in);

                deleteFromNode(p->child[in], key);
            }
        }
    }

    /* Key not found */
    else
    {
        if (p->leaf)
            return;

        flag = (in == p->n);

        /* Make sure child has enough keys */
        if (p->child[in]->n < T)
            fill(p, in);

        if (flag && in > p->n)
            deleteFromNode(p->child[in - 1], key);
        else
            deleteFromNode(p->child[in], key);
    }
}


/* Delete Key */
void deleteKey(int key)
{
    BNode *old;

    if (root == NULL)
    {
        printf("B-Tree is empty.\n");
        return;
    }

    if (search(root, key) == NULL)
    {
        printf("Key %d not found.\n", key);
        return;
    }

    deleteFromNode(root, key);

    /* Root becomes empty */
    if (root->n == 0)
    {
        old = root;

        if (root->leaf)
            root = NULL;
        else
            root = root->child[0];

        free(old);
    }
}


/* Modify Key */
void modify(int oKey, int newk)
{
    if (search(root, oKey) == NULL)
    {
        printf("Key %d not found.\n", oKey);
        return;
    }

    if (search(root, newk) != NULL)
    {
        printf("Key %d already exists.\n", newk);
        return;
    }

    deleteKey(oKey);
    insert(newk);

    printf("Key %d modified to %d successfully.\n", oKey, newk);
}


/* Main */
int main()
{
    int ch;
    int key;
    int oKey;
    int newk;

    while (1)
    {
        printf("\n========== B-TREE MENU ==========\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Modify\n");
        printf("4. Display\n");
        printf("5. Exit\n");
        printf("=================================\n");

        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch)
        {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);

                insert(key);

                printf("Key inserted successfully.\n");
                break;

            case 2:
                printf("Enter key to delete: ");
                scanf("%d", &key);

                deleteKey(key);

                printf("Delete operation completed.\n");
                break;

            case 3:
                printf("Enter key to modify: ");
                scanf("%d", &oKey);

                printf("Enter new key: ");
                scanf("%d", &newk);

                modify(oKey, newk);
                break;

            case 4:
                if (root == NULL)
                {
                    printf("B-Tree is empty.\n");
                }
                else
                {
                    printf("B-Tree elements: ");
                    display(root);
                    printf("\n");
                }
                break;

            case 5:
                printf("Exiting program...\n");
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}