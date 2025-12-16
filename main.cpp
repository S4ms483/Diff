#include <stdio.h>

#include "node.h"
#include "file.h"
#include "visdump.h"
#include "texdump.h"
#include "simplify.h"
#include "calc.h"
#include "diff.h"
#include "taylor.h"


int main(int argc, char* argv[])
{
    const char* cFile = calcFile;
    if (argc > 1) { cFile = argv[1]; }

    Node* root = ReadTreeExpression(cFile);

    Tree* tree = TreeInit(root, TexF);
    
    // DiffAndSimplify(tree);
    
    Tree* tTree = TreeTaylor(tree, 3);

    ReplaceVar(tTree->root, AskForVar());
    TreeSimplify(tTree);

    PrintBeginning(tTree);
    LatexDump(tTree);

    HtmlDump(tTree);

    PrintEnd(TexF, tTree);
 
    TreeDestroy(tree); 
    TreeDestroy(tTree);
}