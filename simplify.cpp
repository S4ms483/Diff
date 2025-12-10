#include "simplify.h"

#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "node.h"
#include "visdump.h"


static bool BothNum(Type_t lType, Type_t rType);
static bool OneZero(Type_t lType, Type_t rType, Value_t lValue, Value_t rValue);
static bool OneUno(Type_t lType, Type_t rType, Value_t lValue, Value_t rValue);
static bool LeftZero(Node* node);
static bool areEqual(double num1, double num2);


void TreeSimplify(Tree* tree)
{
    bool isChanged = true;

    while (isChanged)
    {
        NodeSimplify(tree->root, &isChanged);
        HtmlDump(tree);
    }
}


Node* NodeSimplify(Node* node, bool* isChanged) 
{
    assert(node != NULL);
    assert(isChanged != NULL);
    // FIXME assert flag
    // FIXME flag плохое название

    if (node->type != Op) {return node;}

    sType sim = DefineSimplification(node);

    Value_t value;
    *isChanged = true;

    switch (sim)
    {
        case (Const): 
        {
            node = ConstSim(node);
            break;
        }

        case (AddZero):
        case (MulOne):
        case (PowOne):
        {
            node = AddZeroSim(node);
            break;
        }

        case (MulZero): 
        {
            node = MulZeroSim(node);
            break;
        }

        case (PowZero): 
        {
            node = PowZeroSim(node);
            break;
        }

        default:
        {
            *isChanged = false;
            break;
        }
    }

    if (node->type != Op) {return node;}

    if (node->left) 
    {
        Type_t lType = (node->left)->type;
        if (lType == Op) { node->left = NodeSimplify(node->left, isChanged); }
    }

    if (node->right)
    {
        Type_t rType = (node->right)->type;
        if (rType == Op) { node->right = NodeSimplify(node->right, isChanged); }
    }
    
    return node;
}


sType DefineSimplification(Node* node)
{
    assert (node != NULL);

    Type_t rType = (node->right)->type;
    Value_t rValue = (node->right)->value;

    if (node->left == NULL)
    {
        if (rType == Num) {return Const;}
        return No;
    }

    Type_t lType = (node->left)->type;
    Value_t lValue = (node->left)->value;

    if (BothNum(lType, rType)) {return Const;}

    switch ((node->value).op)
    {
        case Add:
        {
            if (OneZero(lType, rType, lValue, rValue)) {return AddZero;}
            break;
        }

        case Mul:
        {
            if (OneZero(lType, rType, lValue, rValue)) { return MulZero; }
            else if (OneUno(lType, rType, lValue, rValue)) { return MulOne; }
            break;
        }

        case Pow:
        {
            if (OneZero(lType, rType, lValue, rValue)) { return PowZero;}
            else if (OneUno(lType, rType, lValue, rValue)){ return PowOne;}
            break;
        }

        default : {return No;}
    }

    return No;
}


Node* ConstSim(Node* node)
{
    node->type = Num;
    
    Value_t value;
    value.num = NodeCalculate(node); // FIXME плохое название функции

    if (node->left) {NodeDestroy(&(node->left));}
    NodeDestroy(&(node->right));

    node->value = value;

    return node;
}


Node* AddZeroSim(Node* node)
{
    if (LeftZero)
    {
        node = node->right;
        NodeDestroy(&(node->left));
    }

    else
    {
        node = node->left;
        NodeDestroy(&(node->right));
    }

    return node;
}


Node* MulZeroSim(Node* node)
{
    node->type = Num;
    (node->value).num = 0;

    NodeDestroy(&(node->left));
    NodeDestroy(&(node->right));
    node->left = NULL;
    node->right = NULL;

    return node;
}


Node* PowZeroSim(Node* node)
{
    node->type = Num;
    (node->value).num = 1;

    NodeDestroy(&(node->left));
    NodeDestroy(&(node->right));
    node->left = NULL;
    node->right = NULL;

    return node;
}


static bool BothNum(Type_t lType, Type_t rType)
{
    return ((lType == Num) && (rType == Num));
}


static bool OneZero(Type_t lType, Type_t rType, Value_t lValue, Value_t rValue)
{
    return (((lType == Num) && areEqual(lValue.num, 0)) || ((rType == Num) && areEqual(rValue.num, 0)));
}


static bool OneUno(Type_t lType, Type_t rType, Value_t lValue, Value_t rValue)
{
    return (((lType == Num) && areEqual(lValue.num, 1)) || ((rType == Num) && areEqual(rValue.num, 1)));
}


static bool LeftZero (Node* node)
{
    return ((((node->left)->type) == Num)  && areEqual(((node->left)->value).num, 0));
}


static bool areEqual(double num1, double num2)
{
    return (fabs(num1 - num2) < eps);
}