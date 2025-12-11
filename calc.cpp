#include "calc.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

#include "file.h"

static Node* GetNumber(char** chr);
static Node* GetVariable(char** chr);
static Node* GetParentheses(char** chr);
static Node* GetPow(char** chr);
static Node* GetGeneral(char** chr);
static Node* GetExpression(char** chr);
static Node* GetT(char** chr);
static Node* GetFunction(char** chr, Ops_t func);
static Ops_t DefineFunc(char** chr);


Node* ReadTreeExpression(const char* file)
{
    assert(file != NULL);
    char* buffer = FileRead(file);
    assert(buffer != NULL);

    char* chr = buffer;

    Node* root = GetGeneral(&chr);
    free(buffer);
    return root;
}


static Node* GetGeneral(char** chr)
{
    assert((chr != NULL) && (*chr != NULL));

    Node* val = GetExpression(chr);

    if (**chr != '$')
    {
        fprintf(stderr, "Syntax error\n");
    }

    (*chr)++;
    return val;
}


static Node* GetNumber(char** chr)
{
    assert((chr != NULL) && (*chr != NULL));

    Value_t val;

    while(isdigit(**chr))
    {
        val.num = val.num * 10 + (**chr - '0');
        (*chr)++;     
    }

    return NodeInit(Num, val, NULL, NULL, NULL);
}


static Node* GetVariable(char** chr)
{
    assert((chr != NULL) && (*chr != NULL));

    Value_t val;
    val.var = **chr;
    (*chr)++;
    return NodeInit(Var, val, NULL, NULL, NULL);
}


static Node* GetParentheses(char** chr)
{
    assert((chr != NULL) && (*chr != NULL));

    if (**chr == '(')
    {
        (*chr)++;
        Node* val = GetExpression(chr);

        (*chr)++;
        return val;
    }
    else if (isdigit(**chr))
    {
        return GetNumber(chr);
    }

    else if (DefineFunc(chr) != Undef) { return GetFunction(chr, DefineFunc(chr)); }

    else { return GetVariable(chr); }
}


static Node* GetPow(char** chr)
{
    assert((chr != NULL) && (*chr != NULL));

    Value_t nodeOp;
    nodeOp.op = Pow;
    Node* val2 = NULL;
    Node* tmp = NULL;

    Node* val1 = GetParentheses(chr);
    if (**chr == '^')
    {
        (*chr)++;
        val2 = GetParentheses(chr);

        tmp = val1;
        val1 = NodeInit(Op, nodeOp, tmp, val2, NULL);
        tmp->parent = val1;
        val2->parent = val1;
    }

    return val1;
}


Node* GetExpression(char** chr)
{
    assert((chr != NULL) && (*chr != NULL));

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
    assert((chr != NULL) && (*chr != NULL));

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
    assert((chr != NULL) && (*chr != NULL));

    Value_t nodeOp;
    nodeOp.op = func;
    Node* val2 = NULL;

    (*chr) += strlen(Functions[func - start].textName);
    val2 = GetParentheses(chr);
    
    Node* val1 = NodeInit(Op, nodeOp, NULL, val2, NULL);
    val2->parent = val1;

    return val1;
}


Ops_t DefineFunc(char** chr)
{
    assert((chr != NULL) && (*chr != NULL));

    for (size_t i = 0; i < nFuncs; i++)
    {
        if ((*chr - strstr(*chr, Functions[i].textName)) == 0) {return Functions[i].enumName;}
    }

    return Undef;
}