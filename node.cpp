#include "node.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "dsl.h"


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


Tree* TreeInit(Node* root)
{
    Tree* tree = (Tree*)calloc(1, sizeof(Tree));
    assert(tree != NULL);

    tree->root = root;

    return tree;
}


void ValueInit(Node** node, Type_t type, Value_t value)
{
    assert(*node != NULL);

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


Node* OpNodeCreate(Ops_t op, Node* lChild, Node* rChild)
{
    Value_t value;
    value.op = op;

    Node* newNode = NodeInit(Op, value, lChild, rChild, NULL);

    if (lChild) { lChild->parent = newNode; }
    rChild->parent = newNode;

    return newNode;
}


Node* NumNodeCreate(double num)
{
    Value_t value;
    value.num = num;

    Node* newNode = NodeInit(Num, value, NULL, NULL, NULL);

    return newNode;
}


double NodeCalculate(Node* node)
{
    assert(node != NULL);

    double lValue = 0;

    if (node->left) {lValue = ((node->left)->value).num; }
    double rValue = ((node->right)->value).num;

    switch ((node->value).op)
    {
        case (Add): { return lValue + rValue; }
        case (Sub): { return lValue - rValue; }
        case (Mul): { return lValue * rValue; } 
        case (Div): { return lValue / rValue; }
        case (Pow): { return pow(lValue, rValue); }
        case (Sin): { return sin(rValue); }
        case (Cos): { return cos(rValue); }
        case (Tan): { return tan(rValue); }
        case (Cot): { return 1/tan(rValue); }
        case (Log): { return log(rValue); }
        default: { return 0; }
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


void TreeDestroy(Tree* tree)
{
    assert(tree != NULL);

    NodeDestroy(&(tree->root));

    free(tree);
}