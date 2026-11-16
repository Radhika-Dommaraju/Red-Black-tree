#ifndef RBT_H
#define RBT_H

#include<stdio.h>
#include<stdlib.h>

#define SUCCESS 1
#define FAILURE -1
#define DUPLICATE 2

typedef struct node
{
    struct node *left;
    int data;
    char colour;
    struct node *right;
    struct node *parent;
}RBT;

//to insert data to tree
int insert_RBT (RBT **root, int data);

//to fix the inserted data acc to RBT
int insert_fix(RBT **root, RBT *new,RBT *parent);

//to print the tree
int print_RBT(RBT *root);

//to rotate left
static void rotate_right(RBT **root, RBT *x);

//to rotate right
static void rotate_right(RBT **root, RBT *x);

//searching
int search_RBT(RBT *root, int data);

//find min
int min_RBT(RBT *root, int *min);

//find max
int max_RBT(RBT *root, int *max);

//delete rbt
int delete_RBT(RBT **root, int data);

//delete element
int delete_element_RBT(RBT **root, int data);

#endif 