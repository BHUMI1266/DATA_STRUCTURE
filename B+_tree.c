#include <stdio.h>
#include <stdlib.h>

#define MIN_DEGREE 3

typedef struct Node
{
    int* keys;
    int t;
    struct Node** children;
    int n;
    int leaf;
    struct Node* next;
} Node;

typedef struct BTree
{
    Node* root;
    int t;
} BTree;


/* Create Node */
Node* createNode(int t, int leaf)
{
    Node* newn;

    newn = (Node*)malloc(sizeof(Node));

    newn->t = t;
    newn->leaf = leaf;

    newn->keys =
        (int*)malloc((2 * t - 1) * sizeof(int));

    newn->children =
        (Node**)malloc((2 * t) * sizeof(Node*));

    newn->n = 0;
    newn->next = NULL;

    return newn;
}


/* Create B Tree */
BTree* createBTree(int t)
{
    BTree* bt;

    bt = (BTree*)malloc(sizeof(BTree));

    bt->t = t;

    /* 1 means true */
    bt->root = createNode(t, 1);

    return bt;
}


/* Display */
void display(Node* p)
{
    int i;

    if (p == NULL)
        return;

    for (i = 0; i < p->n; i++)
    {
        if (!p->leaf)
        {
            display(p->children[i]);
        }

        printf("%d ", p->keys[i]);
    }

    if (!p->leaf)
    {
        display(p->children[i]);
    }
}


/* Search */
int search(Node* p, int key)
{
    int i = 0;

    while (i < p->n && key > p->keys[i])
    {
        i++;
    }

    if (i < p->n && key == p->keys[i])
    {
        return 1;
    }

    if (p->leaf)
    {
        return 0;
    }

    return search(p->children[i], key);
}


/* Split Child */
void splitChild(Node* prent, int in, Node* ch)
{
    int t;
    int j;

    Node* newc;

    t = ch->t;

    newc = createNode(t, ch->leaf);

    newc->n = t - 1;

    for (j = 0; j < t - 1; j++)
    {
        newc->keys[j] =
            ch->keys[j + t];
    }

    if (!ch->leaf)
    {
        for (j = 0; j < t; j++)
        {
            newc->children[j] =
                ch->children[j + t];
        }
    }

    ch->n = t - 1;

    for (j = prent->n; j >= in + 1; j--)
    {
        prent->children[j + 1] =
            prent->children[j];
    }

    prent->children[in + 1] = newc;

    for (j = prent->n - 1; j >= in; j--)
    {
        prent->keys[j + 1] =
            prent->keys[j];
    }

    prent->keys[in] =
        ch->keys[t - 1];

    prent->n++;
}


/* Insert Non Full */
void insertNonFull(Node* p, int key)
{
    int i;

    i = p->n - 1;

    if (p->leaf)
    {
        while (i >= 0 && p->keys[i] > key)
        {
            p->keys[i + 1] =
                p->keys[i];

            i--;
        }

        p->keys[i + 1] = key;

        p->n++;
    }
    else
    {
        while (i >= 0 && p->keys[i] > key)
        {
            i--;
        }

        i++;

        if (p->children[i]->n ==
            2 * p->t - 1)
        {
            splitChild(p, i,
                       p->children[i]);

            if (p->keys[i] < key)
            {
                i++;
            }
        }

        insertNonFull(p->children[i], key);
    }
}


/* Insert */
void insert(BTree* bt, int key)
{
    Node* p;
    Node* newr;

    p = bt->root;

    if (p->n == 2 * bt->t - 1)
    {
        /* 0 means false */
        newr =
            createNode(bt->t, 0);

        newr->children[0] = p;

        splitChild(newr, 0, p);

        insertNonFull(newr, key);

        bt->root = newr;
    }
    else
    {
        insertNonFull(p, key);
    }
}



void deleteKeyHelper(Node* p, int key);
int findKey(Node* p, int key);
void removeFromLeaf(Node* p, int in);
int getPredecessor(Node* p, int in);
void fill(Node* p, int in);
void borrowFromPrev(Node* p, int in);
void borrowFromNext(Node* p, int in);
void merge(Node* p, int in);


/* Delete */
void deleteKey(BTree* bt, int key)
{
    Node* p;

    p = bt->root;

    deleteKeyHelper(p, key);

    if (p->n == 0 && !p->leaf)
    {
        bt->root =
            p->children[0];

        free(p);
    }
}


/* Delete Helper */
void deleteKeyHelper(Node* p, int key)
{
    int in;
    int isLastChild;

    in = findKey(p, key);

    if (in < p->n &&
        p->keys[in] == key)
    {
        if (p->leaf)
        {
            removeFromLeaf(p, in);
        }
        else
        {
            int predecessor;

            predecessor =
                getPredecessor(p, in);

            p->keys[in] = predecessor;

            deleteKeyHelper(
                p->children[in],
                predecessor);
        }
    }
    else
    {
        if (p->leaf)
        {
            printf("Key %d not found in the B+ tree.\n",
                   key);

            return;
        }

        isLastChild =
            (in == p->n);

        if (p->children[in]->n <
            p->t)
        {
            fill(p, in);
        }

        if (isLastChild &&
            in > p->n)
        {
            deleteKeyHelper(
                p->children[in - 1],
                key);
        }
        else
        {
            deleteKeyHelper(
                p->children[in],
                key);
        }
    }
}


/* Find Key */
int findKey(Node* p, int key)
{
    int in;

    in = 0;

    while (in < p->n &&
           key > p->keys[in])
    {
        in++;
    }

    return in;
}


/* Remove From Leaf */
void removeFromLeaf(Node* p, int in)
{
    int i;

    for (i = in + 1;
         i < p->n;
         i++)
    {
        p->keys[i - 1] =
            p->keys[i];
    }

    p->n--;
}


/* Get Predecessor */
int getPredecessor(Node* p, int in)
{
    Node* cur;

    cur = p->children[in];

    while (!cur->leaf)
    {
        cur =
            cur->children[cur->n];
    }

    return cur->keys[cur->n - 1];
}


/* Fill */
void fill(Node* p, int in)
{
    if (in != 0 &&
        p->children[in - 1]->n >= p->t)
    {
        borrowFromPrev(p, in);
    }
    else if (in != p->n &&
             p->children[in + 1]->n >= p->t)
    {
        borrowFromNext(p, in);
    }
    else
    {
        if (in != p->n)
        {
            merge(p, in);
        }
        else
        {
            merge(p, in - 1);
        }
    }
}


/* Borrow From Previous */
void borrowFromPrev(Node* p, int in)
{
    Node* ch;
    Node* sibl;
    int i;

    ch = p->children[in];
    sibl = p->children[in - 1];

    for (i = ch->n - 1;
         i >= 0;
         i--)
    {
        ch->keys[i + 1] =
            ch->keys[i];
    }

    if (!ch->leaf)
    {
        for (i = ch->n;
             i >= 0;
             i--)
        {
            ch->children[i + 1] =
                ch->children[i];
        }
    }

    ch->keys[0] =
        p->keys[in - 1];

    if (!ch->leaf)
    {
        ch->children[0] =
            sibl->children[sibl->n];
    }

    p->keys[in - 1] =
        sibl->keys[sibl->n - 1];

    ch->n++;
    sibl->n--;
}


/* Borrow From Next */
void borrowFromNext(Node* p, int in)
{
    Node* ch;
    Node* sibl;
    int i;

    ch = p->children[in];
    sibl = p->children[in + 1];

    ch->keys[ch->n] =
        p->keys[in];

    if (!ch->leaf)
    {
        ch->children[ch->n + 1] =
            sibl->children[0];
    }

    p->keys[in] =
        sibl->keys[0];

    for (i = 1;
         i < sibl->n;
         i++)
    {
        sibl->keys[i - 1] =
            sibl->keys[i];
    }

    if (!sibl->leaf)
    {
        for (i = 1;
             i <= sibl->n;
             i++)
        {
            sibl->children[i - 1] =
                sibl->children[i];
        }
    }

    ch->n++;
    sibl->n--;
}


/* Merge */
void merge(Node* p, int in)
{
    Node* ch;
    Node* sibl;
    int i;

    ch = p->children[in];
    sibl = p->children[in + 1];

    ch->keys[ch->n] =
        p->keys[in];

    if (!ch->leaf)
    {
        ch->children[ch->n + 1] =
            sibl->children[0];
    }

    for (i = 0;
         i < sibl->n;
         i++)
    {
        ch->keys[i + ch->n + 1] =
            sibl->keys[i];
    }

    if (!ch->leaf)
    {
        for (i = 0;
             i <= sibl->n;
             i++)
        {
            ch->children[i + ch->n + 1] =
                sibl->children[i];
        }
    }

    for (i = in + 1;
         i < p->n;
         i++)
    {
        p->keys[i - 1] =
            p->keys[i];
    }

    for (i = in + 2;
         i <= p->n;
         i++)
    {
        p->children[i - 1] =
            p->children[i];
    }

    ch->n += sibl->n + 1;

    p->n--;

    free(sibl);
}


/* Main */
int main()
{
    BTree* bt;

    int n;
    int key;
    int i;

    int skey;
    int dkey;

    int f;

    bt = createBTree(MIN_DEGREE);


    /* Dynamic Insertion */

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("\nEnter %d elements:\n", n);

    for (i = 0; i < n; i++)
    {
        printf("Enter element %d: ",
               i + 1);

        scanf("%d", &key);

        insert(bt, key);
    }


    /* Display */

    printf("\nB+ Tree after insertion: ");

    display(bt->root);

    printf("\n");


    /* Search */

    printf("\nEnter key to search: ");
    scanf("%d", &skey);

    f =
        search(bt->root, skey);

    if (f)
    {
        printf("Key %d found in the B+ tree.\n",
               skey);
    }
    else
    {
        printf("Key %d not found in the B+ tree.\n",
               skey);
    }


    /* Delete */

    printf("\nEnter key to delete: ");
    scanf("%d", &dkey);

    deleteKey(bt, dkey);


    /* Display after deletion */

    printf("\nB+ Tree after deletion: ");

    display(bt->root);

    printf("\n");


    /* Search after deletion */

    f =
        search(bt->root,
               dkey);

    if (f)
    {
        printf("Key %d found in the B+ tree.\n",
               dkey);
    }
    else
    {
        printf("Key %d not found in the B+ tree.\n",
               dkey);
    }

    return 0;
}