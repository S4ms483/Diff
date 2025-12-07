#include "simplify.h"

#include <stdio.h>
#include <assert.h>

#include "node.h"
#include "visdump.h"

void TreeSimplify(Tree* tree)
{
    bool isChanged = true;

    while (isChanged)
    {
        fprintf(stderr, "simplifying the statement\n");
        NodeSimplify(tree->root, &isChanged);
        HtmlDump(tree);
    }
}


Node* NodeSimplify(Node* node, bool* flag) //мф принимаем на веру отсутствие детей у нод чисел и переменных
{
    assert(node != NULL);

    if (node->type != Op) {return node;}

    Value_t value;

    Type_t lType = (node->left)->type;
    Type_t rType = (node->right)->type;

    if (lType == Op) { node->left = NodeSimplify(node->left, flag); }
    if (rType == Op) { node->right = NodeSimplify(node->left, flag); }

    sType sim = DefineSimplification(node);
    *flag = true;
    fprintf(stderr, "simplification = %d\n", sim);

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
            *flag = false;
            break;
        }
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

    bool bothNum = ((lType == Num) && (rType == Num));
    bool oneZero = (((lType == Num) && (lValue.num == 0)) || ((rType == Num) && (rValue.num == 0)));
    bool oneUno  = (((lType == Num) && (lValue.num == 1)) || ((rType == Num) && (rValue.num == 1)));

    if (bothNum) {return Const;}

    switch ((node->value).op)
    {
        case Add:
        {
            if (oneZero) {return AddZero;}
            break;
        }

        case Mul:
        {
            if (oneZero) { return MulZero; }
            else if (oneUno) { return MulOne; }
            break;
        }

        case Pow:
        {
            if (oneZero) { return PowZero;}
            else if (oneUno){ return PowOne;}
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
    value.num = NodeCount(node);
    fprintf(stderr, "value = %d\n", value.num);

    NodeDestroy(&(node->left));
    NodeDestroy(&(node->right));

    node->value = value;
    node->left = NULL;
    node->right = NULL;

    fprintf(stderr, "counted const got %d\n", (node->value).num);

    return node;
}


Node* AddZeroSim(Node* node)
{
    node->type = Var;

    if ((node->left)->type == Var)
    {
        node->value = (node->left)->value;
    }

    else {node->value = (node->right)->value;}

    NodeDestroy(&(node->left));
    NodeDestroy(&(node->right));
    node->left = NULL;
    node->right = NULL;

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