#include <stdio.h>

#include "node.h"
#include "file.h"
#include "visdump.h"
#include "texdump.h"
#include "simplify.h"
#include "calc.h"
#include "diff.h"
#include "taylor.h"

// static const char* const TexF = "log/diff.tex";

int main(int argc, char* argv[])
{
    const char* cFile = calcFile;
    if (argc > 1) { cFile = argv[1]; }

    Node* root = ReadTreeExpression(cFile);

    Tree* tree = TreeInit(root, TexF);
    // tree->root = root;

    // DiffAndSimplify(tree);
    
    Tree* tTree = TreeTaylor(tree, 3);

    // PrintBeginning(tTree);
    // HtmlDump(tree);
    // LatexDump(tree);

    // PrintEnd(TaylorTexF, tTree);

    // NodeDestroy(&root); 
    TreeDestroy(tree); 
    TreeDestroy(tTree);
}