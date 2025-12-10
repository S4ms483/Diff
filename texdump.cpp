#include "texdump.h"

#include <stdio.h>
#include <assert.h>

#include "node.h"

void LatexDump(Tree* tree)
{
    assert(tree != NULL);

    static int nTexDump = 0;
fprintf(stderr, "Curr nTexDump is %d\n", nTexDump);

    FILE* TexFile = fopen(TexF, "a");
    assert(TexFile != NULL);

    PrintBeginning(TexFile, nTexDump); //FIXME вынести из функции это 
    fprintf(TexFile, "\\[");

    PrintTexNode(tree->root, TexFile);

    fprintf(TexFile, "\\]\n");
    PrintEnd(TexFile);    //FIXME и это 

    nTexDump++;
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


void PrintBeginning(FILE* file, int nTexDump)
{
    if (!nTexDump) 
    {
        fprintf(file, "\\documentclass[12pt]{article}\n");
        fprintf(file, "\\usepackage[utf8]{inputenc}\n");
        fprintf(file, "\\usepackage[english,russian]{babel}\n");
        fprintf(file, "\\usepackage{amsmath,amssymb}\n");
        fprintf(file, "\\begin{document}\n");
    }
}


void PrintEnd(FILE* file)
{
    fprintf(file, "\\end{document}\n\n"); // как понять когда заканчивать документ
}