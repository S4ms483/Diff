#ifndef DIFF_H_
#define DIFF_H_

#include <stdio.h>

#include "node.h"

Node* Differentiate(Node* node);
Node* NumDiff(Node* node);
Node* XDiff(Node* node);
Node* OpDiff(Node* node);
Node* MulDiff(Node* node);
Node* DivDiff(Node* node);
Node* SinDiff(Node* node);
Node* CosDiff(Node* node);

#endif //DIFF_H_