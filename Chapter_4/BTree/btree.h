// 标准存储的二叉树的结构定义及部分基本操作实现

#ifndef BTREE_H_INCLUDED
#define BTREE_H_INCLUDED

#include <iostream>
#include "seqStack.h"
#include "seqQueue.h"

using namespace std;

// BTree类的前向说明
template <class elemType> 
class BTree;

template <class elemType>
class Node
{   
    friend class BTree<elemType>;
    private:
        elemType data;       
        Node *left, *right;
        int leftFlag; //用于标识是否线索，0时left为左孩子结点，1时为前驱线索
        int rightFlag; //用于标识是否线索，0时right为右孩子结点，1时为后继线索
    public:
        Node(){ left=NULL; right=NULL; leftFlag = 0; rightFlag=0; };
        Node(const elemType &e, Node* L=NULL, Node *R=NULL)
        {  
            data = e;
            left=L; right=R; leftFlag = 0; rightFlag=0;
        };
};

template <class elemType>
class BTree
{
    private:
        Node<elemType> *root;
        elemType stopFlag;

        int Size (Node<elemType> *t); //求以t为根的二叉树的结点个数。
        int Height (Node<elemType> *t); //求以t为根的二叉树的高度。
        void DelTree(Node<elemType> *t); // 删除以t为根的二叉树
        void PreOrder(Node<elemType> *t);
        // 按前序遍历输出以t为根的二叉树的结点的数据值
        void InOrder(Node<elemType> *t);
        // 按中序遍历输出以t为根的二叉树的结点的数据值
        void PostOrder(Node<elemType> *t);
        // 按后序遍历输出以t为根的二叉树的结点的数据值
    public:
        BTree(){ root=NULL; }
        void createTree(const elemType &flag); //创建一棵二叉树
        bool isEmpty (){ return (root == NULL); } // 二叉树为空返回true，否则返回false
        Node<elemType>* GetRoot(){ return  root; } //返回根节点
        int Size (); //求二叉树的结点个数。
        int Height (); //求二叉树的高度。
        void DelTree(); //删除二叉树
        void PreOrder(); // 按前序遍历输出二叉树的结点的数据值
        void InOrder(); // 按中序遍历输出二叉树的结点的数据值
        void PostOrder(); // 按后序遍历输出二叉树的结点的数据值
        void LevelOrder(); // 按中序遍历输出二叉树的结点的数据值
};

# endif