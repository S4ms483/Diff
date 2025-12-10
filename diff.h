#ifndef DIFF_H_
#define DIFF_H_

#include <stdio.h>

#include "node.h"

void TreeDiff(Tree* tree);
// FIXME static в файл
Node* Differentiate(Node* node, Tree* tree);
Node* OpDiff(Node* node, Tree* tree);

#endif // DIFF_H_