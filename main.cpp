#include <stdio.h>

#include "node.h"
#include "file.h"
#include "visdump.h"
#include "texdump.h"
#include "simplify.h"
#include "calc.h"
#include "diff.h"

// static const char* const TexF = "log/diff.tex";

int main(int argc, char* argv[])
{
    const char* cFile = calcFile;
    if (argc > 1) { cFile = argv[1]; }

    Node* root = ReadTreeExpression(cFile);

    Tree* tree = TreeInit(root);
    // tree->root = root;

    PrintBeginning(TexF, tree);

    HtmlDump(tree);
    LatexDump(tree);

    DiffAndSimplify(tree);

    // NodeDestroy(&root); 
    TreeDestroy(tree); 

}