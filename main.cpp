#include <stdio.h>

#include "node.h"
#include "file.h"
#include "visdump.h"
#include "texdump.h"
#include "simplify.h"
#include "calc.h"

int main()
{
    char* buffer = FileRead(calcFile);

    Node* root = Calculate(buffer);

    Tree* tree = TreeInit();
    tree->root = root;

    HtmlDump(tree);
    LatexDump(tree);

    // TreeSimplify(tree);
    // HtmlDump(tree);
    // LatexDump(tree);

    NodeDestroy(&root);
    TreeDestroy(&tree);
}