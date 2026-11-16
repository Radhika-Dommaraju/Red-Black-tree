#include "RBT.h"

int max_RBT(RBT *root, int *max)
{
    RBT *temp = root;

    if (root == NULL)
    {
        return FAILURE;
    }

    while (temp->right != NULL)
    {
        temp = temp->right;
    }

    *max = temp->data;

    return SUCCESS;
}