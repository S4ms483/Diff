#include "texdump.h"

#include <stdio.h>
#include <assert.h>

#include "node.h"

void LatexDump(Tree* tree)
{
    assert(tree != NULL);

    fprintf(tree->tex, "\\[");

    PrintTexNode(tree->root, tree->tex);

    fprintf(tree->tex, "\\]\n");   
}


void PrintTexNode(Node* node, FILE* file)
{
    assert(node != NULL);                   
    assert(file != NULL);

    Node* lChild = node->left;
    bool lBrackets = false;
    Node* rChild = node->right;
    bool rBrackets = false;

    switch(node->type)
    {
        case (Num):
        {
            fprintf(file, "%lg ", (node->value).num);
            break;
        }

        case (Var):
        {
            fprintf(file, "%c ", (node->value).var);
            break;
        }

        case (Op): 
        {
            if (lChild) {lBrackets = IsBracketNeeded(node, lChild);}
            rBrackets = IsBracketNeeded(node, rChild);

            if ((node->value).op == Div)
            {
                fprintf(file, "\\frac{");
                PrintTexNode(lChild, file);
                fprintf(file, "}");

                fprintf(file, "{");
                PrintTexNode(rChild, file);
                fprintf(file, "}");
            }

            else
            {
                if (lChild)
                {
                    PrintOpBrackets(lBrackets, file);
                    PrintTexNode(lChild, file);
                    PrintEndBrackets(lBrackets, file);
                }

                fprintf(file, " %s ", OpSigns[(node->value).op]);

                PrintOpBrackets(rBrackets, file);
                PrintTexNode(rChild, file);
                PrintEndBrackets(rBrackets, file);
            }
        }
    }
}


bool IsBracketNeeded(Node* parent, Node* child)
{
    assert(parent != NULL);

    return (((parent->value).op != Div) && (DefinePriority(parent) > DefinePriority(child)) && (child != NULL));
}


int DefinePriority(Node* node)
{
    assert(node != NULL);

    if (node->type != Op) { return 1;}

    switch ((node->value).op)
    {
        case Add:
        case Sub:
        {
            return 0;
        }

        default: { return 1; }
    }
}


void PrintOpBrackets(bool flag, FILE* file)
{
    if (flag) {fprintf(file, "("); }
}

void PrintEndBrackets(bool flag, FILE* file)
{
    if (flag) {fprintf(file, ")"); }
}


void PrintBeginning(const char* file, Tree* tree)
{
    FILE* TexFile = fopen(TexF, "w");
    assert(TexFile != NULL);

    fprintf(TexFile, "\\documentclass[12pt]{article}\n");
    fprintf(TexFile, "\\usepackage[utf8]{inputenc}\n");
    fprintf(TexFile, "\\usepackage[english,russian]{babel}\n");
    fprintf(TexFile, "\\usepackage{amsmath,amssymb}\n");
    fprintf(TexFile, "\\begin{document}\n");

    tree->tex = TexFile;
}


void PrintEnd(FILE* file)
{
    fprintf(file, "\\end{document}\n\n"); 
    fclose(file);
}