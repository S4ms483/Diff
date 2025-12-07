#include "calc.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Node* Calculate(char* buffer)
{
    char* chr = buffer;

    Node* root = GetGeneral(&chr);
    free(buffer);
    return root;
}


Node* GetGeneral(char** chr)
{
    Node* val = GetExpression(chr);

    if (**chr != '$')
    {
        fprintf(stderr, "Syntax error\n");
    }

    (*chr)++;
    return val;
}


Node* GetNumber(char** chr)
{
    Value_t val;

    while (('0' <= **chr) && (**chr <= '9'))
    {
        val.num = val.num * 10 + (**chr - '0');
        (*chr)++;     
    }

    return NodeInit(Num, val, NULL, NULL, NULL);
}


Node* GetVariable(char** chr)
{
    Value_t val;
    val.var = **chr;
    (*chr)++;
    return NodeInit(Var, val, NULL, NULL, NULL);
}


Node* GetP(char** chr)
{
    if (**chr == '(')
    {
        (*chr)++;
        Node* val = GetExpression(chr);

        (*chr)++;
        return val;
    }
    else if (('0' <= **chr) && (**chr <= '9'))
    {
        return GetNumber(chr);
    }

    else if (DefineFunc(chr) != Undef) { return GetFunction(chr, DefineFunc(chr)); }

    else { return GetVariable(chr); }
}


Node* GetPow(char** chr)
{
    Value_t nodeOp;
    nodeOp.op = Pow;
    Node* val2 = NULL;
    Node* tmp = NULL;

    Node* val1 = GetP(chr);
    if (**chr == '^')
    {
        (*chr)++;
        val2 = GetP(chr);

        tmp = val1;
        val1 = NodeInit(Op, nodeOp, tmp, val2, NULL);
        tmp->parent = val1;
        val2->parent = val1;
    }

    return val1;
}


Node* GetExpression(char** chr)
{
    Value_t nodeOp;
    Node* val2 = NULL;
    Node* tmp = NULL;

    Node* val1 = GetT(chr);
    while ((**chr == '+') || (**chr == '-'))
    {
        char op = **chr;
        (*chr)++;
        val2 = GetT(chr);

        if (op == '+') { nodeOp.op = Add; }
        else { nodeOp.op = Sub; }

        tmp = val1;
        val1 = NodeInit(Op, nodeOp, tmp, val2, NULL);
        tmp->parent = val1;
        val2->parent = val1;
    }

    return val1;
}


Node* GetT(char** chr)
{
    Value_t nodeOp;
    Node* val2 = NULL;
    Node* tmp = NULL;

    Node* val1 = GetPow(chr);
    while ((**chr == '*') || (**chr == '/'))
    {
        char op = **chr;
        (*chr)++;
        val2 = GetPow(chr);

        if (op == '*') { nodeOp.op = Mul; }
        else { nodeOp.op = Div; }
        
        tmp = val1;
        val1 = NodeInit(Op, nodeOp, tmp, val2, NULL);
        tmp->parent = val1;
        val2->parent = val1;
    }

    return val1;
}


Node* GetFunction(char** chr, Ops_t func)
{
    Value_t nodeOp;
    nodeOp.op = func;
    Node* val2 = NULL;

    (*chr) += strlen(Functions[func - start].textName);
    val2 = GetP(chr);
    
    Node* val1 = NodeInit(Op, nodeOp, NULL, val2, NULL);
    val2->parent = val1;

    return val1;
}


Ops_t DefineFunc(char** chr)
{
    for (size_t i = 0; i < nFuncs; i++)
    {
        if ((*chr - strstr(*chr, Functions[i].textName)) == 0) {return Functions[i].enumName;}
    }

    return Undef;
}