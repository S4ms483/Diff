#include "taylor.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "node.h"
#include "diff.h"
#include "texdump.h"
#include "visdump.h"
#include "simplify.h"
#include "dsl.h"

static int Factorial(int num);
static Node* NDiff(Node* node, Tree* tree, int n);

Tree* TreeTaylor(Tree* tree, int n)
{
    assert(tree != NULL);

    Node* taylorRoot = CopyNode(tree->root);

    Tree* taylorTree = TreeInit(taylorRoot, TaylorTexF);
    HtmlDump(taylorTree);

    Node* nextNode = NULL;

    for (int i = 1; i < n; i++)
    {
        nextNode = CopyNode(tree->root);
        nextNode = DIV_(MUL_(NDiff(nextNode, taylorTree, i), POW_(VAR_('x'), CONST_(i))), CONST_(Factorial(i)));
        taylorTree->root = ADD_(nextNode, taylorTree->root);
    }
    
    HtmlDump(taylorTree);
    TreeSimplify(taylorTree);
    return taylorTree;
}


static int Factorial(int num)
{
    int res = 1;

    for (int i = 1; i <= num; i++)
    {
        res = res*i;
    }
    
    return res;
}


static Node* NDiff(Node* node, Tree* tree, int n)
{
    assert(node != NULL);
    
    for (int i = 0; i < n; i++)
    {
        Node* tmp = node;
        node = Differentiate(node, tree);
        NodeDestroy(&tmp);
    }

    return node;
}