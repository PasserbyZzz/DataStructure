#include <cstddef>

class outOfBound{};

template<class elemType>
class linkList; //类的前向说明，为声明友元类做准备

template <class elemType>
class node
{   friend class linkList<elemType>; //linkList类可以访问自己的private变量
    private:
        elemType data;
        node *next;
    public:
        node():next(NULL){};
        node(const elemType &e, node *N=NULL) //默认值为NULL
        {  data = e; next = N; };
};

template <class elemType>
class linkList
{   private:
        node<elemType> *head; //私有头指针
    public:
        linkList();  //构造函数，建立一个空表
        bool isEmpty () const; //表为空返回true,否则返回false。
        bool isFull () const {return false;}; //表为满返回true,否则返回false。
        int length () const;  //表的长度
        elemType get(int i) const;//返回第i个元素的值
        //返回值等于e的元素的序号，从第1个开始，无则返回0
        int find (const elemType &e) const;
        //在第i个位置上插入新的元素（值为e）
        void insert (int i, const elemType &e);
        //若第i个元素存在，删除并将其值放入e指向的空间。
        void remove (int i, elemType &e);
        void reverse() const; //元素就地逆置
        void clear (); //清空表，使其为空表
        void reversed_insert(const elemType a[], int n);
        ~linkList();
};

template <class elemType>
linkList<elemType>::linkList() //构造函数，建立一个空表
{
    head = new node<elemType>();
}

template <class elemType>
bool linkList<elemType>::isEmpty() const //表为空返回true,否则返回false。
{
    if (head->next == NULL) return true;
    return false;
}

template <class elemType>
void linkList<elemType>::insert(int i, const elemType &e )
//在第i个位置上插入新的元素（值为e）
{   
    if (i < 1) return; //参数i越界

    int j = 0; 
    node<elemType> *p = head;

    //找到指向第i个结点的指针
    while (p && j < i-1) //检查p是否为空指针
    { 
        j++;  
        p = p->next; 
    }

    if (!p) return; //参数i越界
    p->next = new node<elemType>(e, p->next);  
}

template <class elemType> 
void linkList<elemType>::remove(int i, elemType &e)
{  
    if (i < 1) return;

    node<elemType> *p = head;
    int j = 0;
    
    while (p && j < i-1) //找到指向第i个结点的指针
    {
        p = p->next;
        j++;
    }

    if (!p) return; //参数i越界

    node<elemType> *q = p->next; //防止内存泄漏

    if (!q) return;

    e = q->data;
	p->next = q->next;
	delete q;  
}

template <class elemType>
int linkList<elemType>::length() const //表的长度
{
    int count = 0;
    node<elemType> *p;
    p = head->next;

    while(p)
    {   
        count++;    
        p = p->next;  
    }

    return count;
}

template <class elemType>  //注意：五步口诀法
elemType linkList<elemType>::get(int i) const //时间复杂度为O(n)
//返回第i个元素的值,首元素为第1个元素
{
    if (i < 1) throw outOfBound(); //参数i越界

    int j = 1;
    node<elemType> *p = head->next;

    while (p && j < i) 
    {
        p = p->next; 
        j++;
    }

    if (p) 
        return p->data;
    else
        throw outOfBound();
}

template <class elemType>
int linkList<elemType>::find(const elemType &e)const
//返回值等于e的元素的序号，从第1个开始，无则返回0
{   
    int i = 1;
    node<elemType> *p = head->next;

    while (p && p->data != e) //先检查p是否为空指针
    {   
        i++;   
        p = p->next;
    }

    if (p) return i;
    return 0;
}

template <class elemType>    //p、q兄弟协同法
void linkList<elemType>::clear() //清空表，使其为空表
{    
    node<elemType> *p, *q;

    p = head->next;      
    head->next = NULL;

    while (p)
    {   
        q = p->next;
        delete p;
        p = q;
    }
}

template <class elemType>    
void linkList<elemType>::reverse() const
{   
    node<elemType> *p,*q;  //p、q兄弟俩协同
    p = head->next;   
    head->next = NULL; //先断开头节点

    while (p)
    {  
        q = p->next;
        p->next = head->next; head->next = p; //首席插入（逆向）
        p = q;
    }
}

template <class elemType>
void linkList<elemType>::reversed_insert(const elemType a[], int n) //首席插入（逆向）
{  
    for (int i = 0; i < n; i++)
    {     
    head->next = new node<elemType>(a[i], head->next);
    }
}

template <class elemType>
linkList<elemType>::~linkList()
{
    clear();
    delete head;
}