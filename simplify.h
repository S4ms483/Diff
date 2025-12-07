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


void TreeSimplify(Tree* tree);
Node* NodeSimplify(Node* node, bool* flag);
sType DefineSimplification(Node* node);
Node* ConstSim(Node* node);
Node* AddZeroSim(Node* node);
Node* MulZeroSim(Node* node);
Node* PowZeroSim(Node* node);

#endif //SIMPLIFY_H_