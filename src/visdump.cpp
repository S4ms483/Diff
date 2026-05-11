#include "visdump.h"

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "node.h"

void VisualDump(Tree* tree, int nDump)
{
    assert(tree != NULL);

    Node* root = tree->root;
    assert(root != NULL);

    char graph[50] = {0};

    sprintf(graph, "log/graph%d.txt", nDump); 


    FILE* graphFile = fopen(graph, "w");
    assert(graphFile != NULL);

    fprintf(graphFile, "digraph G\n \t{\n\t\trankdir = TB;\n\t\t node [shape = record];\n");

    PrintNode(root, graphFile);

    fprintf(graphFile, "}");

    fclose(graphFile);

    char commSvg [commLen] = {0};
    char commPng [commLen] = {0};
    sprintf(commSvg, textCommSvg, nDump, nDump);
    sprintf(commPng, textCommPng, nDump, nDump);
    system(commSvg);
    system(commPng);
};


void PrintNode(Node* node, FILE* file)
{
    assert(node != NULL);
    assert(file != NULL);

    static int nElem = 0;
    int parent = nElem;

    switch (node->type)
    {
        case (Num):
        {
            fprintf(file, numStr, 
                    nElem, node, (node->value).num, node->parent, node->left, node->right);
            break;
        }

        case (Op):
        {
            fprintf(file, opStr, 
                    nElem, node, OpArray[(node->value).op], node->parent, node->left, node->right);
            break;
        }

        case (Var):
        {
            fprintf(file, varStr, 
                    nElem, node, (node->value).var, node->parent, node->left, node->right);
            break;
        }
    }


    if (node->left)
    {
        nElem++;
        fprintf(file, "\t\t%d -> %d; \n", parent, nElem);
        PrintNode(node->left, file);
    }

    if(node->right)
    {
        nElem++;
        fprintf(file, "\t\t%d -> %d; \n", parent, nElem);
        PrintNode(node->right, file);
    }
}


void HtmlDump(Tree* tree)
{
    assert(tree != NULL);

    static int nDump = 0;
    
    nDump ++;

    FILE* logFile = fopen(LogF, "a");
    assert(logFile != NULL);

    VisualDump(tree, nDump);

    fprintf(logFile, "<!DOCTYPE html>\n<html>\n<body>\n<pre>");
    
    fprintf(logFile, "<h3> <font color = red> --------------Dump number %d -------------</font> </h3>\n", nDump);

    fprintf(logFile, "Root address = %p\n", tree);

    fprintf(logFile, "Image:\n");
    fprintf(logFile, "<img src=dump%d.png width = 500px>\n", nDump);


    fprintf(logFile, "--------------------------------------------------");

    fclose(logFile);
}