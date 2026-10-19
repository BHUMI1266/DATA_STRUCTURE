#include <stdio.h>
#include <stdlib.h>

#define RED 1
#define BLACK 0

struct node
{
    int data;
    int color;
    struct node *left, *right, *parent;
};

struct node *root;
struct node *NIL;


struct node *newnode(int val)
{
    struct node *p = (struct node *)malloc(sizeof(struct node));

    p->data = val;
    p->color = RED;
    p->left = NIL;
    p->right = NIL;
    p->parent = NIL;

    return p;
}
/*x=child  y=parent z=target node (insert,delete )*/

void leftrotate(struct node *x)
{
    struct node *y = x->right;

    x->right = y->left;

    if (y->left != NIL)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == NIL)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}


void rightrotate(struct node *y)
{
    struct node *x = y->left;

    y->left = x->right;

    if (x->right != NIL)
        x->right->parent = y;

    x->parent = y->parent;

    if (y->parent == NIL)
        root = x;
    else if (y == y->parent->right)
        y->parent->right = x;
    else
        y->parent->left = x;

    x->right = y;
    y->parent = x;
}


void fixinsert(struct node *z)
{
    struct node *y;

    while (z->parent->color == RED)
    {
        if (z->parent == z->parent->parent->left)
        {
            y = z->parent->parent->right;

            if (y->color == RED)
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->right)
                {
                    z = z->parent;
                    leftrotate(z);
                }

                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightrotate(z->parent->parent);
            }
        }
        else
        {
            y = z->parent->parent->left;

            if (y->color == RED)
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->left)
                {
                    z = z->parent;
                    rightrotate(z);
                }

                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftrotate(z->parent->parent);
            }
        }
    }

    root->color = BLACK;
}


void insert(int val)
{
    struct node *z = newnode(val);
    struct node *y = NIL;
    struct node *x = root;

    while (x != NIL)
    {
        y = x;

        if (val < x->data)
            x = x->left;
        else if (val > x->data)
            x = x->right;
        else
        {
            printf("Duplicate values are not allowed!\n");
            free(z);
            return;
        }
    }

    z->parent = y;

    if (y == NIL)
        root = z;
    else if (val < y->data)
        y->left = z;
    else
        y->right = z;

    fixinsert(z);
    printf("Value %d inserted successfully!\n", val);
}


void display(struct node *p)
{
    if (p != NIL)
    {
        display(p->left);
        printf("%d(%s) ", p->data, p->color == RED ? "RED" : "BLACK");
        display(p->right);
    }
}


struct node *tree_minimum(struct node *x)
{
    while (x->left != NIL)
        x = x->left;
    return x;
}


void rb_transplant(struct node *u, struct node *v)
{
    if (u->parent == NIL)
        root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    v->parent = u->parent;
}


void fixdelete(struct node *x)
{
    struct node *s;
    while (x != root && x->color == BLACK)
    {
        if (x == x->parent->left)
        {
            s = x->parent->right;
            if (s->color == RED)
            {
                s->color = BLACK;
                x->parent->color = RED;
                leftrotate(x->parent);
                s = x->parent->right;
            }

            if (s->left->color == BLACK && s->right->color == BLACK)
            {
                s->color = RED;
                x = x->parent;
            }
            else
            {
                if (s->right->color == BLACK)
                {
                    s->left->color = BLACK;
                    s->color = RED;
                    rightrotate(s);
                    s = x->parent->right;
                }

                s->color = x->parent->color;
                x->parent->color = BLACK;
                s->right->color = BLACK;
                leftrotate(x->parent);
                x = root;
            }
        }
        else
        {
            s = x->parent->left;
            if (s->color == RED)
            {
                s->color = BLACK;
                x->parent->color = RED;
                rightrotate(x->parent);
                s = x->parent->left;
            }

            if (s->left->color == BLACK && s->right->color == BLACK)
            {
                s->color = RED;
                x = x->parent;
            }
            else
            {
                if (s->left->color == BLACK)
                {
                    s->right->color = BLACK;
                    s->color = RED;
                    leftrotate(s);
                    s = x->parent->left;
                }

                s->color = x->parent->color;
                x->parent->color = BLACK;
                s->left->color = BLACK;
                rightrotate(x->parent);
                x = root;
            }
        }
    }
    x->color = BLACK;
}


void delete_node(int val)
{
    struct node *z = root;
    struct node *x, *y;
    int y_original_color;

    
    while (z != NIL && z->data != val)
    {
        if (val < z->data)
            z = z->left;
        else
            z = z->right;
    }

    if (z == NIL)
    {
        printf("Value %d not found in the tree!\n", val);
        return;
    }

    y = z;
    y_original_color = y->color;

    if (z->left == NIL)
    {
        x = z->right;
        rb_transplant(z, z->right);
    }
    else if (z->right == NIL)
    {
        x = z->left;
        rb_transplant(z, z->left);
    }
    else
    {
        y = tree_minimum(z->right);
        y_original_color = y->color;
        x = y->right;

        if (y->parent == z)
            x->parent = y;
        else
        {
            rb_transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        rb_transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    free(z);

    if (y_original_color == BLACK)
        fixdelete(x);

    printf("Value %d deleted successfully!\n", val);
}

int main()
{
    int choice, val;

    NIL = (struct node *)malloc(sizeof(struct node));
    NIL->color = BLACK;
    NIL->left = NIL;
    NIL->right = NIL;
    NIL->parent = NIL;

    root = NIL;

    while (1)
    {
        printf("\n--- RED-BLACK TREE MENU ---");
        printf("\n1. Insert (?????)");
        printf("\n2. Display (????)");
        printf("\n3. Delete (???? ????)");
        printf("\n4. Exit (???? ?????)");
        printf("\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &val);
                insert(val);
                break;

            case 2:
                if (root == NIL)
                    printf("Tree is empty!\n");
                else
                {
                    printf("Inorder Traversal:\n");
                    display(root);
                    printf("\n");
                }
                break;

            case 3:
                if (root == NIL)
                    printf("Tree is empty! Nothing to delete.\n");
                else
                {
                    printf("Enter value to delete: ");
                    scanf("%d", &val);
                    delete_node(val);
                }
                break;

            case 4:
                printf("Exiting program...\n");
                return 0;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}
