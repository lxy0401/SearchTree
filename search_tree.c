#include "search_tree.h"
#include <stdio.h>
#include <stdlib.h>


//先序遍历树
void TreePreOrder(SearchNode* root)
{
    if(root == NULL)
    {
        //空树
        return ;
    }
    //先访问根节点
    printf("%c",root->data);
    //遍历左子树
    TreePreOrder(root->lchild);
    //遍历右子树
    TreePreOrder(root->rchild);
    return ;
}

//中序遍历树
void TreeInOrder(SearchNode* root)
{
    if(root == NULL)
    {
        //空树
        return ;
    }
    //遍历左子树
    TreeInOrder(root->lchild); 
    //先访问根节点
    printf("%c",root->data);
    //遍历右子树
    TreeInOrder(root->rchild);
    return ;
}

//初始化
void SearchTreeInit(SearchNode** pRoot)
{
    if(pRoot == NULL)
    {
        //非法操作
        return ;
    }
    *pRoot = NULL;
    return ;
}

//销毁
void DestroySearchNode(SearchNode* node)
{
    free(node);
}
//方法1
void SearchTreeDestroy(SearchNode* root)
{
    if(root == NULL)
    {
        return ;
    }
    SearchTreeDestroy(root->lchild);
    SearchTreeDestroy(root->rchild);
    DestroySearchNode(root);
}
//方法2
void SearchTreeDestroy2(SearchNode** pRoot)
{
    if(pRoot == NULL)
    {
        //非法操作
        return ;
    }
    if(*pRoot == NULL)
    {
        return ;
    }
    SearchNode* node = *pRoot;
    SearchTreeDestroy2(&node->lchild);
    SearchTreeDestroy2(&node->rchild);
    DestroySearchNode(node);
    *pRoot = NULL;
    return ;
}

//向搜索树中插入元素
SearchNode* CreateSearchNode(SearchNodeType value)
{
    SearchNode* new_node = (SearchNode*)malloc(sizeof(SearchNode));
    new_node->data=value;
    new_node->lchild=NULL;
    new_node->rchild=NULL;
    return new_node;
}

void SearchTreeInsert(SearchNode** pRoot,SearchNodeType to_insert)
{
    if(pRoot == NULL)
    {
        //非法操作
        return ;
    }
    if(*pRoot == NULL)
    {
        //空树,插到root位置
        SearchNode* new_node = CreateSearchNode(to_insert);
        *pRoot = new_node;
        return ;
    }
    //对于树非空的情况
    //采用递归的方式进行插入
    SearchNode* cur = *pRoot;
    if(to_insert < cur->data)
    {
        //递归地往左子树中插入
        SearchTreeInsert(&cur->lchild,to_insert);
    }
    else if(to_insert > cur->data)
    {
        //递归地往右子树中插入
        SearchTreeInsert(&cur->rchild,to_insert);
    }
    else
    {
        //等于的情况，采用下面的约定方式
        //约定二叉搜索树中所有的元素不能重复，
        return ;//表示不做任何动作，插入失败
        //也可以有其他的约定方式：将该元素放到相等元素的左子树的最右边，或者右子树的最左边
    }
}

//递归的方式查找元素
SearchNode* SearchTreeFind(SearchNode* root,SearchNodeType to_find)
{
    if(root == NULL)
    {
        return NULL;
    }
    if(to_find < root->data)
    {
        //递归地查找左子树
        return SearchTreeFind(root->lchild,to_find);
    }
    else if(to_find > root->data)
    {
        //递归地查找右子树
        return SearchTreeFind(root->rchild,to_find);
    }
    else
    {
        //相等，找到了
        return root;
    }
}
/*****
 *
 *以下为测试代码
 *
 *
 * *****/
#if 1
#include <stdio.h>
#define TEST_HEADER printf("\n========%s=========\n",__FUNCTION__)
void SearchTreePrintChar(SearchNode* root,const char* msg)
{
    printf("[%s]\n",msg);
    printf("先序遍历结果为");
    TreePreOrder(root);
    printf("\n");
    printf("中序遍历结果");
    TreeInOrder(root);
    printf("\n");
}
void TestInit()
{
    TEST_HEADER;
    SearchNode* root;
    SearchTreeInit(&root);
    printf("root expected NULL,actuall %p\n",root);
}

void TestInsert()
{
    TEST_HEADER;
    SearchNode* root;
    SearchTreeInit(&root);
    SearchTreeInsert(&root,'a');
    SearchTreeInsert(&root,'e');
    SearchTreeInsert(&root,'c');
    SearchTreeInsert(&root,'d');
    SearchTreeInsert(&root,'b');
    SearchTreePrintChar(root,"插入5个元素");

}

void TestFind()
{
    TEST_HEADER;
    SearchNode* root;
    SearchTreeInit(&root);
    SearchTreeInsert(&root,'a');
    SearchTreeInsert(&root,'e');
    SearchTreeInsert(&root,'c');
    SearchTreeInsert(&root,'d');
    SearchTreeInsert(&root,'b');
    SearchNode* result = SearchTreeFind(root,'c');
    printf("result->data expected c,actuall %c\n",result->data);
}
int main()
{
    TestInit();
    TestInsert();
    TestFind();
    return 0;
}

#endif
