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
        void LevelOrder(); // 按层次遍历输出二叉树的结点的数据值
};

template <class elemType>
void BTree<elemType>::createTree(const elemType &flag) 
// 创建一棵二叉树
{  
    seqQueue<Node<elemType>*> que; //借助队列管理结点
    elemType e, el, er;     
    Node<elemType> *p, *pl, *pr;

    stopFlag = flag;
    cout << "Please input the root: ";       
    cin >> e;

    if (e == flag) //建立空树
    { 
        root = NULL; 
        return;
    }

    p = new Node<elemType>(e);
    root = p; //根结点为该新创建结点
   
    que.enQueue(p); //入队
    while (!que.isEmpty())
    {  
        p = que.front();  //获得队首元素并出队
        que.deQueue();

        cout << "Please input the left child and the right child of " << p->data
             << " using " << flag << " as no child: ";
        cin >> el >> er;

        if (el != flag) //该结点有左孩子
        {     
            pl = new Node<elemType>(el);
            p->left = pl;    
            que.enQueue(pl);
        }

        if (er != flag) //该结点有右孩子
        {      
            pr = new Node<elemType>(er);
            p->right = pr;  
            que.enQueue(pr);
        }
    }
}

template <class elemType> //公有，外部调用
int BTree<elemType>::Size()
{ 
    return Size(root); 
}

template <class elemType> //私有，内部工具
int BTree<elemType>::Size (Node<elemType> *t)
// 得到以t为根二叉树结点个数，递归算法实现
{  
    if (!t) return 0;
    return 1 + Size(t->left) + Size(t->right);    
}

template <class elemType>
int BTree<elemType>::Height()
{ 
    return Height(root); 
}

template <class elemType>
int BTree<elemType>::Height(Node<elemType> *t) 
// 得到以t为根二叉树的高度，递归算法实现
{  
    int hl, hr;     
    if (!t) return 0;
   
    hl = Height(t->left);      
    hr = Height(t->right);
   
    if (hl >= hr) 
        return 1 + hl;    
    return 1 + hr;                  
}

template <class elemType>
void BTree<elemType>::DelTree()
{  
    DelTree(root);    
    root = NULL;   
}

template <class elemType>
void BTree<elemType>::DelTree(Node<elemType> *t)
// 删除以t为根的二叉树，递归算法实现
{  
    if (!t) return;       
    DelTree(t->left);       
    DelTree(t->right);
    delete t;   
}

template <class elemType>
void BTree<elemType>::PreOrder()
{
    PreOrder(root);
}

template <class elemType>
void BTree<elemType>::PreOrder(Node<elemType> *t)
// 前序遍历以t为根二叉树递归算法的实现，时间复杂度为O(n)
{  
    if (!t) return;
    cout << t->data;

    PreOrder(t->left);
    PreOrder(t->right);
}

/*
template <class elemType>
void BTree<elemType>::PreOrder() 
// 前序遍历的非递归算法实现，时间复杂度为O(n)
{ 
    if (!root) return;

    Node<elemType> *p;
    seqStack<Node<elemType>*> s;

    s.push(root);
    while (!s.isEmpty())
    {  
        p = s.top(); 
        s.pop();
        cout << p->data;
        if (p->right) 
            s.push(p->right);
        if (p->left)  
            s.push(p->left);
    }
    cout << endl;
}
*/

template <class elemType>
void BTree<elemType>::LevelOrder()
// 层次遍历二叉树算法的实现，时间复杂度为O(n)
{   
    seqQueue<Node<elemType>*> que;
    Node<elemType> *p;

    if (!root) return; //二叉树为空
    que.enQueue(root);
    while (!que.isEmpty())
    {
        p = que.front();
        que.deQueue();
        cout << p->data;

        if (p->left) que.enQueue(p->left);
        if (p->right) que.enQueue(p->right);
    }
    cout << endl;
}

# endif