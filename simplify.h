#ifndef SIMPLIFY_H_
#define SIMPLIFY_H_

#include <stdio.h>

#include "node.h"

typedef enum
{
    No,
    AddZero,
    MulZero,
    MulOne,
    PowZero,
    PowOne,
    Const
} sType;


const double eps = 0.000001;


void TreeSimplify(Tree* tree);
Node* NodeSimplify(Node* node, bool* flag);
sType DefineSimplification(Node* node);
Node* ConstSim(Node* node);
Node* AddZeroSim(Node* node);
Node* MulZeroSim(Node* node);
Node* PowZeroSim(Node* node);

// FIXME функции а не макросы
// #define BothNum ((lType == Num) && (rType == Num))
// #define OneZero (((lType == Num) && areEqual(lValue.num, 0)) || ((rType == Num) && areEqual(rValue.num, 0)))
// #define OneUno  (((lType == Num) && areEqual(lValue.num, 1)) || ((rType == Num) && areEqual(rValue.num, 1)))

// #define LeftZero  ((((node->left)->type) == Num)  && areEqual(((node->left)->value).num, 0))

#endif // SIMPLIFY_H_