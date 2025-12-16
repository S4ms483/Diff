#ifndef NODE_H_
#define NODE_H_

#include <stdio.h>

typedef enum
{
    Add,
    Sub,
    Mul,
    Div,
    Pow,
    Sin,
    Cos,
    Tan,
    Cot,
    Ln,
    Undef
} Ops_t;


typedef union 
{
    double num;
    Ops_t op;
    char var;
} Value_t; 


typedef enum
{
    Num,
    Op,
    Var
} Type_t;


typedef struct Node
{
    Value_t value;
    Type_t type;
    Node* left;
    Node* right;
    Node* parent;
} Node;


typedef struct
{
    Node* root;
    FILE* tex;
} Tree;


Node* NodeInit (Type_t type, Value_t value, Node* left, Node* right, Node* parent);
Tree* TreeInit(Node* root, const char* file);
void ValueInit(Node** node, Type_t type, Value_t value);
Node* OpNodeCreate(Ops_t op, Node* lChild, Node* rChild);
Node* NumNodeCreate(double num);
Node* VarNodeCreate(char name);
double NodeCalculate(Node* node);
void GiveParents(Node* node);
Node* CopyNode(Node* node);
void NodeDestroy(Node** node);
void TreeDestroy(Tree* tree);

#endif //NODE_H_