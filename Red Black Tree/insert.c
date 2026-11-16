#include "RBT.h"

int insert_RBT(RBT **root, int data)
{
    RBT *new = malloc(sizeof(RBT));

    if (new == NULL)
        return FAILURE;

    new->left = NULL;
    new->right = NULL;
    new->parent = NULL;
    new->data = data;
    new->colour = 'R';

    // First node
    if (*root == NULL)
    {
        new->colour = 'B';
        *root = new;
        return SUCCESS;
    }

    RBT *temp = *root;
    RBT *prev = NULL;

    while (temp)
    {
        prev = temp;

        if (data > temp->data)
        {
            temp = temp->right;
        }
        else if (data < temp->data)
        {
            temp = temp->left;
        }
        else
        {
            free(new);
            return DUPLICATE;
        }
    }

    // Attach new node
    new->parent = prev;

    if (data > prev->data)
        prev->right = new;
    else
        prev->left = new;

    insert_fix(root,new,prev);

    return SUCCESS;
}

