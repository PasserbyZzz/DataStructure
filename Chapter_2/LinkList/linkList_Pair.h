#include <cstddef>

template <class elemType>
class linkList_Pair; 

template <class elemType>
class node
{   
    friend class linkList_Pair<elemType>;
    private:
        elemType data;
        node *prior, *next;
    public:
        node():prior(NULL),next(NULL){};
        node(const elemType &e, node *P=NULL, node *N=NULL)
        {  data = e; prior=P; next = N; };
};

template <class elemType>
class linkList_Pair
{   
    private:
        node<elemType> *head; 
    public:
        void insert(node<elemType> *p, const elemType &x);
        void remove(node<elemType> *p);
};

template <class elemType>
void linkList_Pair<elemType>::insert(node<elemType> *p, const elemType &x) //将元素x插入到p指针所指结点之后
{
    node<elemType> *tmp = new node<elemType>();  //（1）

    tmp->data = x;         // （2）
    tmp->prior = p;        
    tmp->next = p->next;    

    tmp->prior->next = tmp;  // （3）
    tmp->next->prior = tmp;  // （4）
}

template <class elemType>
void linkList_Pair<elemType>::remove(node<elemType> *p) //删除p指针所指结点
{
    p->prior->next = p->next;
    p->next->prior = p->prior;
    delete p;
}