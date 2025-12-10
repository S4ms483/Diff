#include <stdio.h>

#include "node.h"
#include "file.h"
#include "visdump.h"
#include "texdump.h"
#include "simplify.h"
#include "calc.h"
#include "diff.h"

int main(int argc, char* argv[])
{
    const char* cFile = calcFile;
    if (argc > 1) { cFile = argv[1]; }
    // char* buffer = FileRead(cFile); // FIXME argc argv -> calcFile и передавать в ReadTreeExpresion

    Node* root = ReadTreeExpression(cFile);
    // Node* root = Calculate(buffer);

    Tree* tree = TreeInit(root); // FIXME аргумент root
    // tree->root = root;

    HtmlDump(tree);
    LatexDump(tree);

    TreeDiff(tree);

    HtmlDump(tree);
    LatexDump(tree);

    NodeDestroy(&root); // FIXME для дерева функцию
    // TreeDestroy(tree); // FIXME че за жесть, оно почему отдельно
}