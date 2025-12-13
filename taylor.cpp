#include "taylor.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "node.h"
#include "diff.h"
#include "texdump.h"
#include "visdump.h"
#include "dsl.h"

static int Factorial(int num);
static Node* NDiff(Node* node, Tree* tree, int n);

Tree* TreeTaylor(Tree* tree, int n)
{
    assert(tree != NULL);

    Node* rootCopy = CopyNode(tree->root);
    Node* taylorRoot = CopyNode(tree->root);

    Tree* taylorTree = TreeInit(taylorRoot, TaylorTexF);
    HtmlDump(taylorTree);

    Node* nextNode = NULL;
    fprintf(stderr, "%d = n\n", n);

    for (int i = 1; i < n; i++)
    {
        nextNode = rootCopy;
        fprintf(stderr, "%d factorial = %d\n", i, Factorial(i));
        nextNode = DIV_(MUL_(NDiff(nextNode, taylorTree, i), POW_(VAR_('x'), CONST_(i))), CONST_(Factorial(i)));
        taylorTree->root = ADD_(nextNode, taylorTree->root);
        HtmlDump(taylorTree);
    }

    free(rootCopy);
    // free(taylorRoot);
    return taylorTree;
}


static int Factorial(int num)
{
    //REVIEW - респект

    int res = 1;
    // fprintf(stderr, "%d = num\n", num);

    for (int i = 1; i <= num; i++)
    {
        res = res*i;
        // fprintf(stderr, "res = %d \n", res);
    }
    
    // fprintf(stderr, "%d = res\n", res);
    return res;
}


static Node* NDiff(Node* node, Tree* tree, int n)
{
    assert(node != NULL);
    
    for (int i = 0; i < n; i++)
    {
        // Node* tmp = node;
        node = Differentiate(node, tree);
        // NodeDestroy(&tmp);
    }

    return node;
}