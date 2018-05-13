#pragma once
typedef char SearchNodeType;
typedef struct SearchNode
{
    SearchNodeType data;
    struct SearchNode* lchild;
    struct SearchNode* rchild;
}SearchNode;


