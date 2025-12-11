#ifndef TEXDUMP_H_
#define TEXDUMP_H_

#include <stdio.h>

#include "node.h"

static const char* const TexF = "log/diff.tex";

static const char* const OpSigns [] =
{
    "+",
    "-",
    "*",
    "/",
    "^",
    "sin",
    "cos",
    "tan",
    "cot",
    "ln"
};


void LatexDump(Tree* tree);
void PrintTexNode(Node* node, FILE* file);
bool IsBracketNeeded(Node* parent, Node* child);
int DefinePriority(Node* node);
void PrintOpBrackets(bool flag, FILE* file);
void PrintEndBrackets(bool flag, FILE* file);
void PrintBeginning(const char* file, Tree* tree);
void PrintEnd(FILE* file);

#endif //TEXDUMP_H_