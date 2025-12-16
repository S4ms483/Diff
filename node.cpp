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


Tree* TreeInit(Node* root, const char* file)
{
    assert(file != NULL);

    Tree* tree = (Tree*)calloc(1, sizeof(Tree));
    assert(tree != NULL);

    tree->root = root;

    FILE* TexFile = fopen(file, "w");
    assert(TexFile != NULL);
    tree->tex = TexFile;

    return tree;
}


void GiveParents(Node* node)
{
    if (node->left) 
    { 
        (node->left)->parent = node; 
        GiveParents(node->left);
    }

    if (node->right) 
    { 
        (node->right)->parent = node; 
        GiveParents(node->right);
    }
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


Node* VarNodeCreate(char name)
{
    Value_t value;
    value.var = name;

    Node* newNode = NodeInit(Var, value, NULL, NULL, NULL);

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
        case (Ln): { return log(rValue); }
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



double AskForVar()
{
    printf("Enter a value:\n");
    double res = 0;

    int read = scanf("%lf", &res);
    assert(read > 0);

    return res;
}


void ReplaceVar(Node* node, char var, double num)
{
    if (node->left) { ReplaceVar(node->left, var, num); }
    if (node->right) { ReplaceVar(node->right, var, num); }

    Value_t value; 
    value.num = num;

    if ((node->type == Var) && ((node->value).var == var))
    {
        node->type = Num;
        node->value = value;
    }
}


void ChangeVar(Node* node, char var)
{
    if (node->left) { ChangeVar(node->left, var); }
    if (node->right) { ChangeVar(node->right, var); }

    Value_t value; 
    value.var = var;

    if ((node->type == Var) && (node->value).var == 'x')
    {
        node->value = value;
    }
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