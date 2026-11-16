#include "rbt.h"

#if 0
int print_RBT(RBT *root)
{
    if(root == NULL)
    return SUCCESS;

    print_RBT(root->left);
    printf("%d->%c->",root->data,root->colour);
    print_RBT(root->right);

    return SUCCESS;
}
#endif 

int print_RBT(RBT *root)
{
    if (root == NULL)
        return SUCCESS;

    print_RBT(root->left);

    printf("Data: %d | Colour: %c | Parent: ",
           root->data, root->colour);

    if (root->parent != NULL)
        printf("%d\n", root->parent->data);
    else
        printf("NULL (ROOT)\n");

    print_RBT(root->right);

    return SUCCESS;
}