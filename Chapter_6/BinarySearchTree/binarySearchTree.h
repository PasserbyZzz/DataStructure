// 二叉查找树类的定义

#ifndef BINARYSEARCHTREE_H_INCLUDED
#define BINARYSEARCHTREE_H_INCLUDED

#include <iostream>
#include "seqQueue.h"

using namespace std;

template <class elemType>
class binarySearchTree;

template <class elemType>
class Node
{
    friend class binarySearchTree<elemType>;
    private:
        elemType data;
        Node *left, *right;      
        int factor; //平衡因子，用于缩减树高
    public:
        Node(){left=NULL; right=NULL;}
        Node(const elemType &x, Node *l=NULL, Node *r=NULL)
        {data = x; left = l; right = r;}
};

template <class elemType>
class binarySearchTree
{
    private:
        Node<elemType> *root;
        bool search(const elemType &x, Node<elemType> *t) const;
        void insert(const elemType &x, Node<elemType> *&t);
        void remove(const elemType &x, Node<elemType> *&t);
    public:
        binarySearchTree(){root = NULL;}
        bool search(const elemType &x) const;
        void insert(const elemType &x);
        void remove(const elemType &x);
        void levelTravese() const; //层次遍历,用于验证插入、删除操作
};

template <class elemType>
bool binarySearchTree<elemType>::search(const elemType &x) const
{
    return search(x, root);
}

template <class elemType>
bool binarySearchTree<elemType>::search(const elemType &x, Node<elemType> *t) const
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

/*
template <class elemType>
bool binarySearchTree<elemType>::search(const elemType &x) const
// 查找操作的非递归实现
{    
    if (!root) return false;
    
    Node<elemType> *p;     
    p = root;
    while (p)
    {   
        if (x == p->data) 
            return true;
        if (x < p->data) 
            p = p->left;
        else 
            p = p->right;
    }
    return false;
}
*/

template <class elemType> 
void binarySearchTree<elemType>::insert(const elemType &x)
{
    insert(x, root);
}

template <class elemType> 
void binarySearchTree<elemType>::insert(const elemType &x, Node<elemType> *&t)
// 插入操作的递归实现；参数t用了引用形式，完成了新结点的父子关联
{   
    if (!t) 
    { 
        t = new Node<elemType>(x); //因为是引用，所以这里直接赋值给t
        return; 
    }

    if (x == t->data) //已存在，结束插入
        return; 
    if (x < t->data)
        insert(x, t->left);
    else
        insert(x, t->right);
}

/*
template <class elemType> 
void binarySearchTree<elemType>::insert(const elemType &x)
// 插入操作的非递归实现
{
    Node<elemType> *p;
    if (!root)  //如果查找树的根为空，直接建立一个结点并作为根结点
    {   
        root = new Node<elemType>(x);
        return;
    }

    p = root;
    while (p)
    {   
        if (x == p->data) //已经在二叉树中
            return; 
        if (x < p->data)
        {   
            if (!p->left)  //左子为空，插入位置即此地
            {   
                p->left = new Node<elemType>(x);  
                return;   
            }
            p = p->left;
        }
        else
        {   
            if (!p->right)  //右子为空，插入位置即此地
            {   
                p->right = new Node<elemType>(x);  
                return;    
            }
            p = p->right;
        }
    }
}
*/

/*
template <class elemType> 
void binarySearchTree<elemType>::insert(const elemType &x)
// 插入操作另一种非递归实现
{
    Node<elemType> *p, *tmp, *parent=NULL;   
    int flag;
   
    p = root;
    while (p)
    {  
        if (x == p->data) //已存在，无需插入  
            return;     
        
        parent = p;
        if (x < p->data) //p为其父parent的左子
        {   
            flag = 0;     
            p = p->left; 
        }  
        else //p为其父parent的右子
        {   
            flag = 1;     
            p = p->right; 
        } 
    }

    tmp = new Node<elemType>(x);
    if (!parent) //parent为空，表示二叉树为空
    { 
        root = tmp; 
        return; 
    }   
    if (flag == 0) 
        parent->left = tmp;
    else  
        parent->right = tmp;
}
*/

template <class elemType> 
void binarySearchTree<elemType>::remove(const elemType &x)
// 删除操作的递归实现
{
    remove(x, root);
}

template <class elemType> 
void binarySearchTree<elemType>::remove(const elemType &x, Node<elemType> *&t)
// 删除操作的递归实现，时间复杂度O(log_2 n)；注意同样是传引用
{
    if (!t) return;
    if (x < t->data) //先找到待删除结点   
        remove(x, t->left);
    else if (x > t->data)
        remove(x, t->right);
    else //找到待删除结点
    {
        if (!t->left && !t->right) //如果是叶子结点
        {   
            delete t;  //释放待删除结点
            t = NULL;  //父结点和叶子的链接断开（因为这里是传引用）
            return;
        }

        if (!t->left || !t->right) //如果只有一个孩子
        {
            Node<elemType> *tmp;
            tmp = t;
            t = (t->left)? t->left : t->right; //父结点链接其唯一孩子结点（因为这里是传引用）
            delete tmp; //释放待删除结点
            return;
        }

        //待删除结点有两个孩子的情况，这里选择右子树的最小结点为替身
        Node<elemType> *p;
        p = t->right;
        while (p->left) //找到右子树的最小结点
            p = p->left;

        t->data = p->data; //替身结点的值赋给待删除结点
        remove(p->data, t->right); //以t->right为根删除替身结点
    }
}

template <class elemType> 
void binarySearchTree<elemType>::remove(const elemType &x)
// 删除操作的非递归实现
{
    if (!root) return;

    Node<elemType> *p, *parent; //p，parent协同
    int flag; //0为父结点顺左子下来，1为父结点顺右子下来。

    p = root;
    parent = NULL;
    while (p)
    {
        // 先找到待删除结点
        if (x < p->data) 
        {
            parent = p; 
            flag = 0;
            p = p->left; 
            continue; //注意这里的continue
        }
        if (x > p->data)
        {
            parent = p; 
            flag = 1;
            p = p->right; 
            continue; //注意这里的continue
        }

        //删除开始
        //待删除结点为叶子结点
        if (!p->left && !p->right) 
        {
            delete p;

            // 解引用前先检查是否为空指针
            if (!parent) //待删除结点为根，且根为叶子(仅一个结点) 
            {
                root = NULL; 
                return;
            } 

            if (flag == 0) //待删除结点为父结点的左子
                parent->left = NULL;
            else //待删除结点为父结点的右子
                parent->right = NULL;

            return;
        }

        //待删除结点仅有一个孩子结点
        if (!p->left || !p->right) 
        {   
            Node<elemType> *tmp;   
            tmp = p;

            if (!parent) //待删除结点为根，且根有一个孩子
               root = (p->left)? p->left : p->right;
            else
                if (flag == 0) //待删除结点为父结点的左子
                    parent->left = (p->left)? p->left : p->right;
                else //待删除结点为父结点的右子
                    parent->right = (p->left)? p->left : p->right;

            delete tmp;     
            return;
        }

        // 待删除结点有二个孩子结点，选择左子树的最大结点为替身
        Node<elemType> *q, *substitute;
        parent = p;  
        q = p->left;

        while (q->right) 
        {
            parent = q; 
            q = q->right;
        }
        substitute = q;   

        //交换待删除结点和替身的元素值
        p->data = substitute->data;    
        substitute->data = x;

        p = substitute; //待删除结点指针变为替身继续返回循环
        //下一次循环其实已经找到x的位置，直接进入叶子/有一个孩子结点的情况，删除后退出循环
    }
}

template <class elemType>
void binarySearchTree<elemType>::levelTravese() const
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
        cout << p->data << ' ';

        if (p->left) que.enQueue(p->left);
        if (p->right) que.enQueue(p->right);
    }
    cout << endl;
}

#endif // BINARYSEARCHTREE_H_INCLUDED