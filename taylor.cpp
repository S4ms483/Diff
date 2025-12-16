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

    PrintBeginning(taylorTree);
    PrintTaylorHeader(taylorTree);

    LatexDump(taylorTree);

    ChangeVarName(taylorTree->root, 'x', 'a');
    HtmlDump(taylorTree);

    Node* nextNode = NULL;

    for (int i = 1; i < n; i++)
    {
        nextNode = CopyNode(tree->root);
        nextNode = DIV_(MUL_(NDiff(nextNode, taylorTree, i), POW_(SUB_(VAR_('x'), VAR_('a')), CONST_(i))), CONST_(Factorial(i)));
        taylorTree->root = ADD_(taylorTree->root, nextNode);

        LatexDump(taylorTree);
    }
    
    HtmlDump(taylorTree);
    TreeSimplify(taylorTree);

    ReplaceVarWNum(taylorTree->root, 'a', AskForVarValue('a'));
    LatexDump(taylorTree);

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
    assert(tree != NULL);
    assert(node != NULL);
    
    for (int i = 0; i < n; i++)
    {
        Node* tmp = node;
        node = Differentiate(node, tree);
        NodeDestroy(&tmp);
    }

    ChangeVarName(node, 'x', 'a');

    return node;
}