#include "diff.h"

#include <stdio.h>
#include <assert.h>

#include "dsl.h"
#include "texdump.h"
#include "visdump.h"
#include "simplify.h"

static Node* Differentiate(Node* node, Tree* tree);
static Node* OpDiff(Node* node, Tree* tree);


void TreeDiff(Tree* tree)
{
    assert(tree != NULL);

    TreeSimplify(tree); // FIXME вынести отдельно функцию которая последовательно diff и opt

    tree->root = Differentiate(tree->root, tree);
    HtmlDump(tree); // FIXME странная тема делать это тут

     
    // TreeSimplify(tree);
}


static Node* Differentiate(Node* node, Tree* tree)
{
    assert(node != NULL);
    assert(tree != NULL);

    HtmlDump(tree);

    Node* parent = node->parent;
    
    Value_t value;

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
        
        case (Log): { return MUL_(DIV_(CONST_(1), cR), dR); }

        case (Pow): 
        { 
            return MUL_(MUL_(cR, POW_(cL, SUB_(cR, CONST_(1)))), dL); // FIXME 2^x x^2 x^x
        }
        default : { assert(!"Unkown op"); return NULL; }
    }
}
