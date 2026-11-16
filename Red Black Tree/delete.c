
#include "rbt.h"
#include <stdlib.h>

/* Return BLACK for a NULL node */
static int get_colour(RBT *node)
{
    if (node == NULL)
        return 'B';

    return node->colour;
}

/* Left rotation */
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

/* Right rotation */
static void rotate_right(RBT **root, RBT *y)
{
    RBT *x = y->left;

    y->left = x->right;

    if (x->right != NULL)
        x->right->parent = y;

    x->parent = y->parent;

    if (y->parent == NULL)
        *root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    x->right = y;
    y->parent = x;
}

/* Replace subtree u with subtree v */
static void transplant(RBT **root, RBT *u, RBT *v)
{
    if (u->parent == NULL)
        *root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;

    if (v != NULL)
        v->parent = u->parent;
}

/* Find minimum node in a subtree */
static RBT *successor_node(RBT *node)
{
    while (node->left != NULL)
        node = node->left;

    return node;
}

/* Fix Red-Black properties after deletion */
static void delete_fixup(RBT **root, RBT *x, RBT *parent)
{
    while (x != *root && get_colour(x) == 'B')
    {
        if (parent == NULL)
            break;

        if (x == parent->left)
        {
            RBT *w = parent->right;

            if (get_colour(w) == 'R')
            {
                w->colour = 'B';
                parent->colour = 'R';
                rotate_left(root, parent);
                w = parent->right;
            }

            if (w == NULL ||
                (get_colour(w->left) == 'B' &&
                 get_colour(w->right) == 'B'))
            {
                if (w != NULL)
                    w->colour = 'R';

                x = parent;
                parent = x->parent;
            }
            else
            {
                if (get_colour(w->right) == 'B')
                {
                    if (w->left != NULL)
                        w->left->colour = 'B';

                    w->colour = 'R';
                    rotate_right(root, w);
                    w = parent->right;
                }

                w->colour = parent->colour;
                parent->colour = 'B';

                if (w->right != NULL)
                    w->right->colour = 'B';

                rotate_left(root, parent);
                x = *root;
                parent = NULL;
            }
        }
        else
        {
            /* Mirror case */
            RBT *w = parent->left;

            if (get_colour(w) == 'R')
            {
                w->colour = 'B';
                parent->colour = 'R';
                rotate_right(root, parent);
                w = parent->left;
            }

            if (w == NULL ||
                (get_colour(w->left) == 'B' &&
                 get_colour(w->right) == 'B'))
            {
                if (w != NULL)
                    w->colour = 'R';

                x = parent;
                parent = x->parent;
            }
            else
            {
                if (get_colour(w->left) == 'B')
                {
                    if (w->right != NULL)
                        w->right->colour = 'B';

                    w->colour = 'R';
                    rotate_left(root, w);
                    w = parent->left;
                }

                w->colour = parent->colour;
                parent->colour = 'B';

                if (w->left != NULL)
                    w->left->colour = 'B';

                rotate_right(root, parent);
                x = *root;
                parent = NULL;
            }
        }
    }

    if (x != NULL)
        x->colour = 'B';
}

/* Delete a specified element */
int delete_RBT(RBT **root, int data)
{
    RBT *z = *root;
    RBT *y, *x, *x_parent;
    int original_colour;

    /* Step 1: Search for the node */
    while (z != NULL && z->data != data)
    {
        if (data < z->data)
            z = z->left;
        else
            z = z->right;
    }

    if (z == NULL)
        return FAILURE;

    /* Step 2: Identify the node to physically remove */
    y = z;
    original_colour = y->colour;

    if (z->left == NULL)
    {
        x = z->right;
        x_parent = z->parent;

        transplant(root, z, z->right);

        if (x != NULL)
            x_parent = x->parent;
    }
    else if (z->right == NULL)
    {
        x = z->left;
        x_parent = z->parent;

        transplant(root, z, z->left);

        if (x != NULL)
            x_parent = x->parent;
    }
    else
    {
        /* Two children: use inorder successor */
        y = successor_node(z->right);
        original_colour = y->colour;
        x = y->right;

        if (y->parent == z)
        {
            x_parent = y;

            if (x != NULL)
                x->parent = y;
        }
        else
        {
            x_parent = y->parent;

            transplant(root, y, y->right);

            y->right = z->right;
            y->right->parent = y;
        }

        transplant(root, z, y);

        y->left = z->left;
        y->left->parent = y;
        y->colour = z->colour;
    }

    /* Step 3: Free the deleted node */
    free(z);

    /* Step 4: Restore Red-Black properties */
    if (original_colour == 'B')
        delete_fixup(root, x,
                     (x != NULL) ? x->parent : x_parent);

    /* Step 5: Restore root properties */
    if (*root != NULL)
    {
        (*root)->colour = 'B';
        (*root)->parent = NULL;
    }

    return SUCCESS;
}
