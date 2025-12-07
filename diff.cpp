#include "diff.h"

#include <stdio.h>

Node* Differentiate(Node* node)
{
    assert(node != NULL);

    Node* parent = node->parent;
    // bool isLeft = (node == parent->left);

    Value_t value;

    switch (node->type):
    {
        case (Num):
        {
            return NumDiff;
        }

        case (Var):
        {
            if ((node->value).var != 'x') 
            {
                node->type = Num;
                return NumDiff(Node* node);
            }

            else {return XDiff(Node* node);}
        }

        case (Op):
        {
            return OpDiff(Node* node);
        }
    }
}


Node* NumDiff(Node* node)
{
    (node->value).num = 0;
    return node;
}


Node* XDiff(Node* node)
{
    (node->type) = Num;
    (node->value).num = 1;
    return node;
}


Node* OpDiff(Node* node)
{
    switch ((node->value).op):
    {
        case (Add):
        case (Sub):
        {
            node->left = Diverative(node->left);
            node->right = Diverative(node->right);
            return node;
            break;
        }

        case (Mul):
        {
            return MulDiff(node);
            break;
        }

        case (Div):
        {
            return DivDiff(node);
            break;
        }

        case (Sin):
        {
            return SinDiff(node);
        }

        case (Cos):
        {
            return CosDiff(node);
        }
    }
}


Node* MulDiff(Node* node)
{
    lOrigin = CopyNode(node->left);
    rOrigin = CopyNode(node->right);
    Node* dLeft = Differentiate(node->left);
    Node* dRight = Differentiate(node->right);

    node->type = Op;
    (node->value).op = Add;

    Value_t lValue;
    Value_t rValue;

    lValue.op = Mul;
    rValue.op = Mul;

    Node* lMul = NodeInit(Op, lValue, lOrigin, dRight, node);
    lOrigin->parent = lMul;
    dRight->parent = lMul; 

    Node* rMul = NodeInit(Op, rValue, rOrigin, lRight, node);
    rOrigin->parent = rMul;
    dLeft->parent = rMul;

    return node;
}


Node* DivDiff(Node* node)
{
    lOrigin = CopyNode(node->left);
    rOrigin1 = CopyNode(node->right);
    rOrigin2 = CopyNode(node->right);
    Node* dLeft = Differentiate(node->left);
    Node* dRight = Differentiate(node->right);

    node->type = Op;
    (node->value).op = Div;

    Value_t lTopValue;
    Value_t rTopValue;
    Value_t botValue;
    Value_t mTopValue;
    Value_t powValue;

    lTopValue.op = Mul;
    rTopValue.op = Mul;
    mTopValue.op = Sub;
    botValue.op = Pow;
    powValue.num = 2;

    Node* lMul = NodeInit(Op, lTopValue, rOrigin1, dLeft, NULL);
    rOrigin1->parent = lMul;
    dLeft->parent = lMul;

    Node* rMul = NodeInit(Op, rTopValue, lOrigin, dRIght, NULL);
    lOrigin->parent = lMul;
    dRight->parent = lMul; 

    Node* Sub = NodeInit(Op, mTopValue, lMul, rMul, node);
    rMul->parent = Sub;
    lMul->parent = Sub;

    Node* Pow = NodeInit(Num, powValue, NULL, NULL, NULL);

    Node* Sqr = NodeInit(Op, botValue, rOrigin2, Pow, node)
    Pow->parent = Sqr;
    rOrigin2->parent = Sqr;

    return node;
}


Node* SinDiff(Node* node)
{
    (node->value).op = Cos;
    return Node;
}


Node* CosDiff(Node* node)
{
    Value_t sinValue;
    Value_t minusValue;
    Value_t value;

    sinValue.op = Sin;
    minusValue.num = -1;
    value.op = Mul;
    Node* sin = NodeInit(Op, sinValue, NULL, node->right, node);
    Node* minus = NodeInit(Num, minusValue, NULL, NULL, node);

    node->type = Op;
    node->value = value;

    node->left = sin;
    node->right = minus;

    return Node;
}