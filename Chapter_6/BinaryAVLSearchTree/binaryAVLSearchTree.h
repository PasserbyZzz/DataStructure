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
        binaryAVLSearchTree(){root = NULL;}
        bool search(const elemType &x) const;
        void insert(const elemType &x);
        void remove(const elemType &x);
        void levelTravese() const; 
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
void binaryAVLSearchTree<elemType>::insert(const elemType &x)
{
	insert(x, root);
}

template <class elemType>
void binaryAVLSearchTree<elemType>::insert(const elemType &x, AVLNode<elemType>* &t)
{      
    if (!t) //在空树上插入
        t = new AVLNode<elemType>(x); 

	else if(x == t->data) //已存在，结束插入
        return; 

    else if (x < t->data) //在左子树上插入
    {	                      
        insert(x, t->left);
	    if (height(t->left) - height(t->right) == 2) //t为冲突结点
		    if (x < t->left->data) //在左孩子左子树上插入
                LL(t); 
            else //在左孩子右子树上插入
                LR(t);
    }

    else if (t->data < x) //在右子树上插入
    {                        
	    insert(x, t->right);
	    if (height(t->left) - height(t->right) == -2) //t为冲突结点
		    if(x > t->right->data) 
                RR(t); //在右孩子右子树上插入
            else 
                RL(t); //在右孩子左子树上插入
    }
    
    //重新计算t的高度 
    t->height = max(height(t->left), height(t->right)) + 1;
}

template <class elemType>
void binaryAVLSearchTree<elemType>::LL(AVLNode<elemType>* &t)
{
    AVLNode<elemType> *newRoot = t->left; //新的根
    t->left = newRoot->right;
    newRoot->right = t;
    t->height = max(height(t->left), height(t->right)) + 1; //重新计算t的高度
    newRoot->height = max(height(newRoot->left), height(newRoot->right)) + 1; //重新计算新的根的高度
    t = newRoot; //新的父子关联
}

template <class elemType>
void binaryAVLSearchTree<elemType>::RR(AVLNode<elemType>* &t)
{
    AVLNode<elemType> *newRoot = t->right; // 新的根
    t->right = newRoot->left;
    newRoot->left = t;
    t->height = max(height(t->left), height(t->right)) + 1; //重新计算t的高度
    newRoot->height = max(height(newRoot->left), height(newRoot->right)) + 1; //重新计算新的根的高度
    t = newRoot; // 新的父子关联
}

template <class elemType>
void binaryAVLSearchTree<elemType>::LR(AVLNode<elemType>* &t)
{
    RR(t->left);
    LL(t);
}

template <class elemType>
void binaryAVLSearchTree<elemType>::RL(AVLNode<elemType>* &t)
{
    LL(t->right);
    RR(t);
}

template <class elemType>
void binaryAVLSearchTree<elemType>::remove(const elemType &x)
{
    remove(x, root);
}

template <class elemType>
void binaryAVLSearchTree<elemType>::remove(const elemType &x, AVLNode<elemType>* &t)
{
    if (!t) //未找到
        return; 

    else if (x < t->data) //在左子树上删除
    {
        remove(x, t->left);

        if (height(t->left) - height(t->right) == -2) //t为冲突节点
            if (height(t->right->right) > height(t->right->left)) //相当于在右孩子的右子树上添加
                RR(t);
            else //相当于在右孩子的左子树上添加
                RL(t);
        else //无冲突，重新计算t的高度
            t->height = max(height(t->left), height(t->right)) + 1;
    }

    else if (x > t->data) //在右子树上删除
    {
        remove(x, t->right);

        if (height(t->left) - height(t->right) == 2) //t为冲突节点
            if (height(t->left->left) >= height(t->left->right)) //相当于在左孩子的左子树上添加
                LL(t);
            else //相当于在左孩子的右子树上添加
                LR(t);
        else //无冲突，
        重新计算t的高度
            t->height = max(height(t->left), height(t->right)) + 1;
    }

    else //删除开始
    {
        if (!t->left || !t->right) //只有一个孩子或者没有孩子
        {
            AVLNode<elemType>* tmp;
            tmp = t;
            t = (t->left) ? t->left : t->right; //父节点链接其唯一孩子节点
            delete tmp; //释放待删除节点
            return;
        }
        // 待删除结点有两个孩子的情况
        AVLNode<elemType> *p;
        p = t->right;
        while (p->left) //找到右子树的最小值
            p = p->left;
        t->data = p->data; //将右子树的最小值赋给待删除结点
        remove(p->data, t->right); //删除右子树的最小值
    }
}

template <class elemType>
void binaryAVLSearchTree<elemType>::levelTravese() const
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