#pragma once
typedef char SearchNodeType;
typedef struct SearchNode
{
    SearchNodeType data;
    struct SearchNode* lchild;
    struct SearchNode* rchild;
}SearchNode;


//初始化
void SearchTreeInit(SearchNode** pRoot);

//销毁
void SearchTreeDestroy(SearchNode* root);
void SearchTreeDestroy2(SearchNode** pRoot);

//向搜索树中插入元素
void SearchTreeInsert(SearchNode** pRoot,SearchNodeType to_insert);

//递归的方式查找元素
SearchNode* SearchTreeFind(SearchNode* root,SearchNodeType to_find);

//按值来删除元素
void SearchTreeRemove(SearchNode** pRoot,SearchNodeType to_remove);
