#include "RBT.h"

int delete_element_RBT(RBT **root, int data)
{
    RBT *temp = *root;

    /* Search for the element */
    while (temp != NULL)
    {
        if (data == temp->data)
            break;
        else if (data < temp->data)
            temp = temp->left;
        else
            temp = temp->right;
    }

    /* Element not found */
    if (temp == NULL)
        return FAILURE;

    /* Delete the element */
    return delete_RBT(root, data);
}