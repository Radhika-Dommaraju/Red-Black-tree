#include "rbt.h"

int min_RBT(RBT *root, int *min)
{
    RBT *temp = root;

    if (root == NULL)
    {
        return FAILURE;
    }

    while (temp->left != NULL)
    {
        temp = temp->left;
    }

    *min = temp->data;

    return SUCCESS;
}


