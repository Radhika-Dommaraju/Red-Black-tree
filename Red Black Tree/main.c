#include"rbt.h"

int main()
{
    RBT *root = NULL;
    int option, data,res, min, max;

    while(1)
    {
    printf("\nMENU: \n1.insert\n2.search\n3.find min\n4.find max\n5.delete min\n6.delete max\n7.delete element\n 8.exit\nenter the option:");
    scanf("%d", &option);
    
    switch(option)
    {
        case 1:
        printf("Enter the data to insert:");
        scanf("%d", &data);
        res = insert_RBT(&root,data);
        if( res == FAILURE)
        {
            printf("insert is failed\n");
        }
        else if (res == DUPLICATE)
        {
            printf("DAT enteres is already present in the tree\n");
        }
        else
        {
            printf("insert sucessful\n");
            print_RBT(root);
        }
       break; 
       
       case 2:
       printf("Enter the data to search: ");
       scanf("%d", &data);

       res = search_RBT(root, data);

       if (res == SUCCESS)
       {
        printf("Data found in the tree\n");
       }
       else
       {
        printf("Data not found in the tree\n");
        }
       break;


       case 3:
       res = min_RBT(root , &min);

       if(res == SUCCESS)
       {
        printf("Minimum element is %d\n", min);
       }
       else
       {
        printf("Tree is empty\n");
       }
       break;

       case 4:
       
       res = max_RBT(root, &max);

       if(res == SUCCESS)
       {
        printf("Maximum element is %d\n", max);
       }
       else
       {
        printf("Tree is empty\n");
       }
       
       break;

       case 5:
       //delete min
        res = min_RBT(root, &min);

        if (res == SUCCESS)
        {
           res = delete_RBT(&root, min);

           if (res == SUCCESS)
           {
              printf("Minimum element deleted successfully\n");
              print_RBT(root);
           }
        }
        else
        {
        printf("Tree is empty\n");
        }
       break;

       case 6:
       //delete max

       res = max_RBT(root, &min);

        if (res == SUCCESS)
        {
           res = delete_RBT(&root, min);

           if (res == SUCCESS)
           {
              printf("Minimum element deleted successfully\n");
              print_RBT(root);
           }
        }
        else
        {
        printf("Tree is empty\n");
        }
       break;
       
       
       case 7:
       printf("Enter the data to delete: ");
       scanf("%d", &data);

       res = delete_element_RBT(&root, data);

       if (res == SUCCESS)
       {
        printf("Element deleted successfully\n");
        print_RBT(root);
       }
       else
       { 
        printf("Element not found in tree\n");
        }
       break;

       
       case 8:
       exit(0);
       break;

       default:
       printf("Invalid option \n");
       break;


    }

 }
}