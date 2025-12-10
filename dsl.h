#ifndef DSL_H_
#define DSL_H_

#include <stdio.h>

#define dL Differentiate(node->left, tree)
#define dR Differentiate(node->right, tree)
#define cL CopyNode(node->left)
#define cR CopyNode(node->right)

#define CONST_(num) NumNodeCreate(num)
#define ADD_(lNode, rNode) OpNodeCreate(Add, lNode, rNode)
#define SUB_(lNode, rNode) OpNodeCreate(Sub, lNode, rNode)
#define MUL_(lNode, rNode) OpNodeCreate(Mul, lNode, rNode)
#define DIV_(lNode, rNode) OpNodeCreate(Div, lNode, rNode)
#define POW_(lNode, rNode) OpNodeCreate(Pow, lNode, rNode)

#define SIN_(rNode) OpNodeCreate(Sin, NULL, rNode)
#define COS_(rNode) OpNodeCreate(Cos, NULL, rNode)
#define TAN_(rNode) OpNodeCreate(Tan, NULL, rNode)
#define COT_(rNode) OpNodeCreate(Cot, NULL, rNode)
#define LN_(rNode)  OpNodeCreate(Ln,  NULL, rNode)
#define LOG_(lNode, rNode) OpNodeCreate(Log, lNode, rNode)
 
#endif //DSL_H_