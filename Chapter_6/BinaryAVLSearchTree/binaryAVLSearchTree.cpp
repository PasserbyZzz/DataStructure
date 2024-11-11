// 平衡二叉查找树的定义

#ifndef BINARYAVLSEARCHTREE_H_INCLUDED
#define BINARYAVLSEARCHTREE_H_INCLUDED

#include <iostream>
#include "seqQueue.h"
using namespace std;

template <class elemType>
class binaryAVLSearchTree;

template <class elemType>
class AVLNode
{
    friend class binaryAVLSearchTree<elemType>;
    private:
        elemType data;
        AVLNode *left, *right;   
        int height; //记录以该结点为根的二叉树的高度
    public:
        AVLNode() {left=NULL; right=NULL;height=0;}
        AVLNode(const elemType &x, AVLNode *l=NULL, AVLNode *r=NULL)
        { data = x; left = l; right = r; height=1;}
};

template <class elemType>
class binaryAVLSearchTree
{
    private:
        AVLNode<elemType> *root;
        bool search(const elemType &x, AVLNode<elemType>* t) const;
        void insert(const elemType &x, AVLNode<elemType>* &t);
        void remove(const elemType &x, AVLNode<elemType>* &t);
        int height(AVLNode<elemType> *t) const;
	    void LL(AVLNode<elemType>* &t);
	    void LR(AVLNode<elemType>* &t);
	    void RL(AVLNode<elemType>* &t);
	    void RR(AVLNode<elemType>* &t);
    public:
        binarySearchTree(){root = NULL;}
        bool search(const elemType &x) const;
        void insert(const elemType &x);
        void remove(const elemType &x);
        void levelTravese() const; //层次遍历,用于验证插入、删除操作
};

template <class elemType>
bool binaryAVLSearchTree<elemType>::search(const elemType &x) const
{
    return search(x, root);
}

template <class elemType>
bool binaryAVLSearchTree<elemType>::search(const elemType &x, AVLNode<elemType> *t) const
// 查找操作的递归实现，时间复杂度O(log_2 n)；极端情况下O(n)
{    
    if (!t) return false;

    if (x == t->data) 
        return true;
    if (x < t->data)
        return search(x, t->left);
    else
        return search(x, t->right);
}



template <class elemType>
int binaryAVLSearchTree<elemType>::height(AVLNode<elemType> *t) const
{
	if(!t) return 0;
    return t->height;
}

template <class elemType>
void binaryAVLSearchTree<elemType>::insert(const elemType & x)
{
	insert(x, root);
}

template <class elemType>
void binaryAVLSearchTree<elemType>::insert( const elemType & x, AVLNode<elemType> * & t )
{      
    if (!t) //在空树上插入
        t = new AVLNode<elemType>(x); 

	else if(x == t->data) //已存在，结束插入
        return; 

    else if (x < t->data) //在左子树上插入
    {	                      
        insert(x, t->left);
	    if (height(t->left) - height(t->right) == 2) //t为冲突结点
		    if(x < t->left->data) 
                LL(t); 
            else 
                LR(t);
    }

    else if (t->data < x) //在右子树上插入
    {                        
	    insert( x, t->right );
	    if(height(t->left) - height(t->right) == -2 ) //t为冲突结点
		   if( x > t->right->data ) 
                RR(t); 
            else 
                RL(t);
    }
    
    //重新计算t的高度 
    t->height = max(height( t->left), height(t->right)) + 1;
}

template <class elemType>
void binaryAVLSearchTree<elemType>::levelTravese() const
// 层次遍历二叉树算法的实现，时间复杂度为O(n)
{   
    seqQueue<AVLNode<elemType>*> que;
    AVLNode<elemType> *p;

    if (!root) return; //二叉树为空
    que.enQueue(root);
    while (!que.isEmpty())
    {
        p = que.front();
        que.deQueue();
        cout << p->data << ' ';

        if (p->left) que.enQueue(p->left);
        if (p->right) que.enQueue(p->right);
    }
    cout << endl;
}

#endif 