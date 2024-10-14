#ifndef POLYNOMIAL_H_INCLUDED
#define POLYNOMIAL_H_INCLUDED

#include <iostream>
#include "linklist.h"
using namespace std;

struct Type
{  
    int coef; // 系数
    int exp; // 幂指数
};

template <class elemType>
struct Node
{   
    elemType data;
    Node* next;
};

template <class elemType>
struct Polynomial
{
    private:
        Node<elemType>* head;
        elemType stop_flag; // 用于判断多项式输入结束。
    public:
        //从用户处获取结束标志并初始化多项式
        Polynomial(const elemType &stop);
        void getPoly(); //读入一个多项式
        void addPoly(const Polynomial &L1, const Polynomial &L2); //L3=L1+l2
        void dispPloy(); //显示一个多项式
        void clear(); //释放多项式空间
        ~Polynomial(){clear(); delete head;};
};

// getStop为外部函数，即非类成员函数
template <class elemType>
void getStop(elemType &stopFlag)//从用户处获取结束标志
{
    int c, e;
    cout << "请输入系数、指数对作为结束标志,如(0,0): ";
    cin >> c >> e;
    stopFlag.coef = c;
    stopFlag.exp = e;
}

template <class elemType>
Polynomial<elemType>::Polynomial(const elemType &stop) //初始化多项式   
{   
    head = new Node<elemType>();
    stop_flag.coef = stop.coef;
    stop_flag.exp = stop.exp;
}

template <class elemType>
void Polynomial<elemType>::getPoly() //读入一个多项式
{   
    Node<elemType> *p, *tmp;
    elemType e;

    p = head;
    cout << "请按照指数从小到大输入系数、指数对，最后输入结束标志对结束：\n";
    cin >> e.coef >> e.exp; //防止第一次结束

    while (true)
    {
        if ((e.coef == stop_flag.coef) && (e.exp == stop_flag.exp)) 
            break;

        tmp = new Node<elemType>();
        tmp->data.coef = e.coef;
        tmp->data.exp = e.exp;
        tmp->next = NULL;
        p->next = tmp;
        p = tmp;

        cin >> e.coef >> e.exp;
    }
}

template <class elemType>
void Polynomial<elemType>::addPoly(const Polynomial &La, const Polynomial &Lb)// La+Lb
{
    Node<elemType> *pa, *pb, *pc;
    Node<elemType> *tmp;

    pa = La.head->next; //pa 指向第一个多项式中的第一项(首结点)
    pb = Lb.head->next; //pb 指向第二个多项式中的第一项(首结点)
    pc = head; //pc 指向第三个多项式中的头结点，待插入相加后的结点

    // 三个链同步走
    while (pa && pb)//两个多项式都未加完
    {
        if (pa->data.exp == pb->data.exp)
        {
            if (pa->data.coef + pb->data.coef == 0) //判断和为0的情况
            {
                pa = pa->next; 
                pb = pb->next; 
                continue;
            }
            else
            {
                tmp = new Node<elemType>();
                tmp->data.coef = pa->data.coef + pb->data.coef; 
                tmp->data.exp = pa->data.exp;
                tmp->next = NULL; 
                pa = pa->next; 
                pb = pb->next;
            }
        }

        else if (pa->data.exp > pb->data.exp)
        {
            tmp = new Node<elemType>();
            tmp->data.coef = pb->data.coef;
            tmp->data.exp = pb->data.exp;
            tmp->next  =NULL;
            pb = pb->next;
        }

        else
        {
            tmp = new Node<elemType>();
            tmp->data.coef = pa->data.coef;
            tmp->data.exp = pa->data.exp; 
            tmp->next = NULL;
            pa = pa->next;
        }

        pc->next = tmp;
        pc = tmp;
    }

    //将两个多项式中未加完的项抄到结果链上
    while(pa) //第一个多项式未加完
    {
        tmp = new Node<elemType>(); 
        tmp->data.coef = pa->data.coef;
        tmp->data.exp = pa->data.exp; 
        tmp->next = NULL;

        pa = pa->next;
        pc->next = tmp;
        pc = tmp;
    }

    while(pb) //第二个多项式未加完
    {
        tmp = new Node<elemType>();
        tmp->data.coef = pb->data.coef;
        tmp->data.exp = pb->data.exp;
        tmp->next = NULL;

        pb = pb->next;
        pc->next = tmp;
        pc = tmp;
    }
}

template <class elemType>
void Polynomial<elemType>::dispPloy() //显示一个多项式
{
    Node<elemType> *p; 
    p = head->next;

    if (!p) 
    {
        cout << "多项式为空\n";
        return;
    }

    cout << "多项式为(系数指数对):" << endl;
    while(p)
    {
        cout << p->data.coef << " " << p->data.exp << "\n";
        p = p->next; 
    }
    cout << endl; 
}
    
template <class elemType>
void Polynomial<elemType>::clear()
{
    Node<elemType> *p,*q;
    p = head->next; //p指向首结点
    
    while(p) //释放从首结点开始的链中所有的结点
    {
        q = p->next;
        delete p;
        p = q;
    }
}

#endif