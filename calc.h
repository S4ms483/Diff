#ifndef CALC_H_
#define CALC_H_

#include "node.h"

typedef struct
{
    const char* textName;
    Ops_t enumName;
} Funcs_t;

const Funcs_t Functions [] =
{
    {"sin", Sin},
    {"cos", Cos},
    {"tan", Tan},
    {"cot", Cot},
    {"log", Log} 
};

const size_t nFuncs = sizeof(Functions)/sizeof(Functions[0]);
const int start = 5; //костыль чтобы енам использовать в качестве индекса

Node* ReadTreeExpression(const char* buffer);

#endif // CALC_H_