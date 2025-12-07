#ifndef CALC_H_
#define CALC_H_

#include "node.h"

typedef struct
{
    const char* textName;
    Ops_t enumName;
}Funcs_t;

const Funcs_t Functions [] =
{
    {"sin", Sin},
    {"cos", Cos},
    {"tan", Tan},
    {"cot", Cot},
    {"ln",  Ln} 
};

const size_t nFuncs = 5;
const int start = 5;

Node* Calculate(char* buffer);
Node* GetNumber(char** chr);
Node* GetVariable(char** chr);
Node* GetP(char** chr);
Node* GetPow(char** chr);
Node* GetGeneral(char** chr);
Node* GetExpression(char** chr);
Node* GetT(char** chr);
Node* GetFunction(char** chr, Ops_t func);
Ops_t DefineFunc(char** chr);

#endif //CALC_H_