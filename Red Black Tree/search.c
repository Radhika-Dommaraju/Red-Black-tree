#include "rbt.h"

int search_RBT(RBT *root, int data)
{
    RBT *temp = root;

    while (temp != NULL)
    {
        if (data == temp->data)
        {
            return SUCCESS;
        }
        else if (data < temp->data)
        {
            temp = temp->left;
        }
        else
        {
            temp = temp->right;
        }
    }

    return FAILURE;
}