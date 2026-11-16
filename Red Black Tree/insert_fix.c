#include"RBT.h"


static void rotate_left(RBT **root, RBT *x)
{
    RBT *y = x->right;

    x->right = y->left;

    if (y->left != NULL)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == NULL)
        *root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

static void rotate_right(RBT **root, RBT *x)
{
    RBT *y = x->left;

    x->left = y->right;

    if (y->right != NULL)
        y->right->parent = x;

    y->parent = x->parent;

    if (x->parent == NULL)
        *root = y;
    else if (x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;

    y->right = x;
    x->parent = y;
}


int insert_fix(RBT **root, RBT *new, RBT *parent)
{
    RBT *grandparent;
    RBT *uncle;

    while (new != *root &&
           parent != NULL &&
           parent->colour == 'R')
    {
        grandparent = parent->parent;

        if (grandparent == NULL)
            break;

        if (parent == grandparent->left)
        {
            uncle = grandparent->right;

            if (uncle != NULL && uncle->colour == 'R')
            {
                parent->colour = 'B';
                uncle->colour = 'B';
                grandparent->colour = 'R';

                new = grandparent;
            }
            else
            {
                if (new == parent->right)
                {
                    new = parent;
                    rotate_left(root, new);

                    parent = new->parent;
                }

                parent->colour = 'B';
                grandparent = parent->parent;
                grandparent->colour = 'R';

                rotate_right(root, grandparent);
            }
        }
        else
        {
            uncle = grandparent->left;

            if (uncle != NULL && uncle->colour == 'R')
            {
                parent->colour = 'B';
                uncle->colour = 'B';
                grandparent->colour = 'R';

                new = grandparent;
            }
            else
            {
                if (new == parent->left)
                {
                    new = parent;
                    rotate_right(root, new);

                    parent = new->parent;
                }

                parent->colour = 'B';
                grandparent = parent->parent;
                grandparent->colour = 'R';

                rotate_left(root, grandparent);
            }
        }

        parent = new->parent;
    }

    (*root)->colour = 'B';

    return SUCCESS;
}
