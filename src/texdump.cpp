#include "texdump.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "node.h"

void LatexDump(Tree* tree)
{
    assert(tree != NULL);

    static int nTexDump = 0;

    if (nTexDump > 0) { fprintf(tree->tex, "%s\n", RandTexPhrase()); }

    nTexDump++;

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

        default: { return; }
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


void PrintBeginning(Tree* tree)
{
    fprintf(tree->tex, "\\documentclass[12pt]{article}\n");
    fprintf(tree->tex, "\\usepackage[utf8]{inputenc}\n");
    fprintf(tree->tex, "\\usepackage[english]{babel}\n");
    fprintf(tree->tex, "\\usepackage{amsmath,amssymb}\n");
    fprintf(tree->tex, "\\begin{document}\n");
}


void PrintDiffHeader(Tree* tree)
{
    fprintf(tree->tex, "\\bfseries{Let's differentiate this:}\n\n");
}


void PrintTaylorHeader(Tree* tree)
{
    fprintf(tree->tex, "\\bfseries{Let's find Taylor expansion for this:}\n\n");
}


const char* RandTexPhrase()
{
    int n = rand() % (int)(sizeof(RandPhrases) / sizeof(RandPhrases[0]));
    return RandPhrases[n];
}


void PrintEnd(const char* file, Tree* tree)
{
    fprintf(tree->tex, "\\end{document}\n\n"); 
    fclose(tree->tex);
}