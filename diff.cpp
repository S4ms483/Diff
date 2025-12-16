#include "diff.h"

#include <stdio.h>
#include <assert.h>

#include "dsl.h"
#include "texdump.h"
#include "visdump.h"
#include "simplify.h"


static Node* OpDiff(Node* node, Tree* tree);
static bool ConstPow(Node* node);
static bool ConstBase(Node* node);


void DiffAndSimplify(Tree* tree)
{
    assert(tree != NULL);
    TreeSimplify(tree);

    TreeDiff(tree);
    GiveParents(tree->root);
    HtmlDump(tree);

    TreeSimplify(tree);

    HtmlDump(tree);
    LatexDump(tree);
}


void TreeDiff(Tree* tree)
{
    assert(tree != NULL);

    Node* tmp = tree->root;

    tree->root = Differentiate(tree->root, tree);

    NodeDestroy(&tmp);
}


Node* Differentiate(Node* node, Tree* tree)
{
    assert(node != NULL);
    assert(tree != NULL);

    HtmlDump(tree);


    switch (node->type)
    {
        case (Num): { return CONST_(0); }

        case (Var):
        {
            if ((node->value).var != 'x') { return CONST_(0); }

            else { return CONST_(1); }
        }

        case (Op):
        {
            return OpDiff(node, tree);
        }

        default: { return NULL; }
    }

}


static Node* OpDiff(Node* node, Tree* tree)
{
    switch ((node->value).op)
    {
        case (Add): { return ADD_(dL, dR); }

        case (Sub): { return SUB_(dL, dR); }

        case (Mul): { return ADD_(MUL_(dL, cR), MUL_(cL, dR)); }

        case (Div): { return DIV_(SUB_(MUL_(dL, cR), MUL_(cL, dR)), POW_(cR, CONST_(2))); }

        case (Sin): { return MUL_(COS_(cR), dR); }

        case (Cos): { return MUL_(MUL_(SIN_(cR), CONST_(-1)), dR); }
        
        case (Tan): { return MUL_(DIV_(CONST_(1), POW_(COS_(cR), CONST_(2))), dR); }
        
        case (Cot): { return MUL_(DIV_(CONST_(-1), POW_(SIN_(cR), CONST_(2))), dR); }
        
        case (Ln): { return MUL_(DIV_(CONST_(1), cR), dR); }

        case (Pow): 
        { 
            if (ConstPow(node)) { return MUL_(MUL_(cR, POW_(cL, SUB_(cR, CONST_(1)))), dL); }

            if (ConstBase(node)) { return MUL_(POW_(cL, cR), LN_(cL)); }

            return MUL_(POW_(cL, cR), ADD_(MUL_(dR, LN_(cL)), DIV_(MUL_(dL, cR), cL)));
        }
        default : { assert(!"Unkown op"); return NULL; }
    }
}


static bool ConstPow(Node* node)
{
    assert (node != NULL);
    return ((node->right)->type == Num);
}


static bool ConstBase(Node* node)
{
    assert (node != NULL);
    return ((node->left)->type == Num);
}