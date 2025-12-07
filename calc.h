#ifndef CALC_H_
#define CALC_H_

#include "node.h"

Node* Calculate(char* buffer);
Node* GetNumber(char** chr);
Node* GetVariable(char** chr);
Node* GetP(char** chr);
Node* GetPow(char** chr);
Node* GetGeneral(char** chr);
Node* GetExpression(char** chr);
Node* GetT(char** chr);

#endif //CALC_H_