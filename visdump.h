#ifndef VISDUMP_H_
#define VISDUMP_H_

#include <stdio.h>

#include "node.h"

static const char* LogF = "log/DiffLogfile.html";
static const char* textComm = "dot log/graph%d.txt -T png -o log/dump%d.png";
static const size_t commLen = 50;

static const char* numStr = "\t\t%d [label = \" { %p | %lg | parent = %p | { left = %p | right = %p } }\"]; \n";
static const char* opStr =  "\t\t%d [label = \" { %p | %s  | parent = %p | { left = %p | right = %p } }\"]; \n";
static const char* varStr = "\t\t%d [label = \" { %p | %c  | parent = %p | { left = %p | right = %p } }\"]; \n"; //FIXME color

static const char* OpArray [] =
{
    "ADD",
    "SUB",
    "MUL",
    "DIV",
    "POW",
    "SIN",
    "COS",
    "TAN",
    "COT",
    "LOG",
    "LN"
};

void VisualDump(Tree* tree, int nDump);
void PrintNode(Node* node, FILE* file);
void HtmlDump(Tree* tree);

#endif // VISDUMP_H_