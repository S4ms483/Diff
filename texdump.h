#ifndef TEXDUMP_H_
#define TEXDUMP_H_

#include <stdio.h>

#include "node.h"

static const char* const TexF = "log/diff.tex";
static const char* const TaylorTexF = "log/taylor.tex";
static const char* const texCommand = "pdfLatex %s";
static const size_t texCommLen = 50;

static const char* const OpSigns [] =
{
    "+",
    "-",
    "\\cdot",
    "/",
    "^",
    "\\sin",
    "\\cos",
    "\\tan",
    "\\cot",
    "\\ln"
};


void LatexDump(Tree* tree);
void PrintTexNode(Node* node, FILE* file);
bool IsBracketNeeded(Node* parent, Node* child);
int DefinePriority(Node* node);
void PrintOpBrackets(bool flag, FILE* file);
void PrintEndBrackets(bool flag, FILE* file);
void PrintBeginning(Tree* tree);
void PrintEnd(const char* file, Tree* tree);

#endif //TEXDUMP_H_