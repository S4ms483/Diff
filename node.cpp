#include "node.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>


Node* NodeInit (Type_t type, Value_t value, Node* left, Node* right, Node* parent)
{
    Node* node = (Node*)calloc(1, sizeof(Node));
    assert(node != NULL);

    node->type = type;
    node->left = left;
    node->right = right;
    node->parent = parent; 

    ValueInit(&node, type, value);

    return node;
}


Tree* TreeInit()
{
    Tree* tree = (Tree*)calloc(1, sizeof(Tree));
    assert(tree != NULL);

    tree->root = NULL;

    return tree;
}


void ValueInit(Node** node, Type_t type, Value_t value)
{
    switch (type)
    {
        case Num:
        {
        ((*node)->value).num = value.num;
        break;
        }

        case Op:
        {
        ((*node)->value).op = value.op;
        break;
        }

        case Var:
        {
        ((*node)->value).var = value.var;
        break;
        }
    }
}


double NodeCount(Node* node)
{
    double lValue = ((node->left)->value).num;
    double rValue = ((node->right)->value).num;

    fprintf(stderr, "lvalue = %f, rvalue = %f\n", lValue, rValue);
    fprintf(stderr, "op = %d, sub = %d\n", (node->value).op, Sub);

    switch ((node->value).op)
    {
        case (Add): 
        {
            return (lValue + rValue);
            break;
        }  //Как вот это сделать лучше
        case (Sub): 
        {
            return (lValue - rValue);
            break;
        }
        case (Mul): 
        {
            fprintf(stderr, "lv&rv = %d\n", lValue * rValue);
            return (lValue * rValue);
            break;
        }
        case (Div): 
        {
            return (lValue / rValue);
            break;
        } 
        case (Pow):
        {
            return (pow(lValue, rValue));
            break;
        }
        case (Sin):
        {
            return (sin(rValue));
            break;
        }
        case (Cos):
        {
            return (cos(rValue));
            break;
        }
        case (Tan):
        {
            return (tan(rValue));
            break;
        }
        case (Cot):
        {
            return (1/tan(rValue));
            break;
        }
        case (Ln):
        {
            return (log(rValue));
            break;
        }
        default: 
        {
            return 0;
            break;
        }
    }
}


Node* CopyNode(Node* node)
{
    Node* newNode = NodeInit(node->type, node->value, NULL, NULL, NULL);
    if (node->left)
    {
        newNode->left = CopyNode(node->left);
        (newNode->left)->parent = newNode;
    }

    if (node->right)
    {
        newNode->right = CopyNode(node->right);
        (newNode->right)->parent = newNode;
    }

    return newNode;
}


void NodeDestroy(Node** node)
{
    assert(node != NULL);
    
    if ((*node)->left != NULL)
    {
        NodeDestroy(&((*node)->left));
    }
    
    if ((*node)->right != NULL)
    {
        NodeDestroy(&((*node)->right));
    }

    free(*node);
    *node = NULL;
}


void TreeDestroy(Tree** tree)
{
    assert(tree != NULL);

    (*tree)->root = NULL;
    // (*tree)->keys = NULL;
    free(*tree);
    *tree = NULL;
}