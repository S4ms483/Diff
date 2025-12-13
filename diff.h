#ifndef DIFF_H_
#define DIFF_H_

#include <stdio.h>

#include "node.h"

Node* Differentiate(Node* node);
void DiffAndSimplify(Tree* tree);
void TreeDiff(Tree* tree);

#endif // DIFF_H_