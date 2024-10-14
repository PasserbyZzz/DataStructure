// 链式栈结构定义及基本操作的实现

#ifndef LINKQUEUE_H_INCLUDED
#define LINKQUEUE_H_INCLUDED

class outOfBound{};

template <class elemType>
class linkStack;

template <class elemType>
class Node
{ 
    friend class linkStack<elemType>;
    private:
        elemType data;
        Node *next;
    public:
        Node(){next = NULL;}
        Node(const elemType &x, Node *p=NULL)
        { data = x; next = p; }
};

template <class elemType>
class linkStack
{
    private:
        Node<elemType> *Top;
    public:
        linkStack(){ Top = NULL; }; //初始化栈，使其为空栈（无头结点）
        bool isEmpty(){ return (Top==NULL); }; //栈为空返回true,否则返回false。
        bool isFull(){ return false; }; //栈满true，否则false。结点空间不连续，故总能满足
        elemType top();
        void push(const elemType &e);
        void pop();
        ~linkStack();
};

template <class elemType>
elemType linkStack<elemType>::top()
{
    if (!Top) throw outOfBound(); //栈空

    return Top->data;
}

template <class elemType>
void linkStack<elemType>::push(const elemType &e)
{  
    Top = new Node<elemType>(e, Top); //首席插入法
}

template <class elemType>
void linkStack<elemType>::pop()
{
    Node<elemType> *tmp;

    if (!Top) throw outOfBound(); //栈空

    tmp = Top; //用tmp记住原栈顶结点空间，用于弹栈后的空间释放
    Top = Top->next; //实际将栈顶结点弹出栈

    delete tmp;//释放原栈顶结点空间
}

template <class elemType>
linkStack<elemType>::~linkStack()
{
    Node<elemType> *tmp;

    while (Top) //协同法
    {
        tmp = Top;
        Top = Top->next;
        delete tmp;
    }
}

#endif

// 析构函数将栈中的所有结点清除，空间回收，时间复杂度为O(n)
// 构造函数、isEmpty、isFull、top、push、pop的时间复杂度均为O(1)