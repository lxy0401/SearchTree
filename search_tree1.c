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


SearchNode* CreateSearchNode(SearchNodeType value)
{
    SearchNode* new_node = (SearchNode*)malloc(sizeof(SearchNode));
    new_node->data=value;
    new_node->lchild=NULL;
    new_node->rchild=NULL;
    return new_node;
}

#if 0 //递归的方式实现搜索二叉树的插入、查找、删除
//向搜索树中插入元素
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

//按值来删除元素（递归的方式）
void SearchTreeRemove(SearchNode** pRoot,SearchNodeType to_remove)
{
    if(pRoot == NULL)
    {
        //非法操作
        return ;
    }
    //2.若没有找到to_remove直接返回空树
    if(*pRoot == NULL)
    {
        //空树
        return ;
    }
    //1.找到to_remove所在的位置
    SearchNode* root = *pRoot;
    if(to_remove < root->data)//递归地将左子树删除
    {
        SearchTreeRemove(&root->lchild,to_remove);
        return ;
    }
    else if(to_remove > root->data)
    {
        SearchTreeRemove(&root->rchild,to_remove);
        return ;
    }
    else
    {
        //3.找到的情况
        SearchNode* to_remove_node = root;
        if(root->lchild == NULL && root->rchild == NULL)
        {
            //a.要删除的节点没有子树
            *pRoot = NULL;
            DestroySearchNode(to_remove_node);
            return ;
        }
        else if(root->rchild != NULL && root->rchild == NULL)
        {
            //b.只有左子树
            *pRoot = to_remove_node->lchild;
            DestroySearchNode(to_remove_node);
            return ;
        }
        else if(root->lchild == NULL && root->rchild != NULL)
        {
            //c.只有右子树
            *pRoot = to_remove_node->rchild;
            DestroySearchNode(to_remove_node);
            return ;
        }
        else
        {
            //d.右左右子树
            //需要先找到右子树中的最小值，把删除点的值与最小值交换，
            //从当前节点的右子树出发，尝试递归地删除交换的值
            SearchNode* min = to_remove_node->lchild;
            while(min->lchild != NULL)
            {
                min = min->lchild;
            }
            //最小值已经指向右子树的最小节点
            to_remove_node->data = min->data;
            //尝试删除min->data
            SearchTreeRemove(&to_remove_node->rchild,min->data);
            return ;
        }
    }
    return ;
}
#endif


#if 1 //非递归的方式实现搜索二叉树的插入、查找、删除
//向搜索树中插入元素
void SearchTreeInsert(SearchNode** pRoot,SearchNodeType to_insert)
{
    //1.空树
    //2.非空树，先找到要插入的位置，将要插入的位置记录下来
    if(pRoot == NULL)
    {
        return ;
    }
    if(*pRoot == NULL)
    {
        //1.空树
        *pRoot = CreateSearchNode(to_insert);
        return ;
    }
    //新元素要放的位置
    SearchNode* cur = *pRoot;
    //新元素的父节点
    SearchNode* pre = NULL;
    //这个循环只是要找到要插入的位置在哪
    while(1)
    {
        if(cur == NULL)
        {
            //找到要插入的位置在哪
            break ;
        }
        if(to_insert < cur->data)
        {
            pre = cur;
            cur = cur->lchild;
        }
        else if(to_insert > cur->data)
        {
            pre = cur;
            cur = cur->rchild;
        }
        else
        {
            //发现有一个相同的元素
            //此时按照之前的约定插入失败
            return ;
        }
    }
    SearchNode* new_node = CreateSearchNode(to_insert);
    //pre不能为空，
    //因为pre为空意味着前面的while循环一进来就命中了cur==NULL，
    //而cur==NULL已经被前面最开始的判定排除了
    if(new_node->data < pre->data)
    {
        pre->lchild = new_node;
    }
    else
    {
        pre->lchild = new_node;
    }
    return ;
}

//递归的方式查找元素
SearchNode* SearchTreeFind(SearchNode* root,SearchNodeType to_find)
{
    if(root == NULL)
    {
        return NULL;
    }
    SearchNode* cur = root;
    while(1)
    {
        if(cur == NULL)
        {
            break ;
        }
        if(to_find < cur->data)
        {
            cur = cur->lchild;
        }
        else if(to_find > cur->data)
        {
            cur = cur->rchild;
        }
        else
        {
            //空树
            break ;
        }
        return cur;
    }
}

//按值来删除元素
void SearchTreeRemove(SearchNode** pRoot,SearchNodeType to_remove)
{

}

#endif
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
