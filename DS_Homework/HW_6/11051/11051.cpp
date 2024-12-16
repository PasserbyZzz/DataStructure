#include <iostream>

using namespace std;

class Linklist;

class Node
{
    friend class Linklist;
    private:
        int data;
        Node* next;
    public:
        Node():next(NULL){};
        Node(const int &e, Node* N=NULL):data(e), next(N){};
};

class Linklist
{
    private:
        Node* head;
        int cnt;
    public:
        Linklist(int n); //构造函数，根据输入建立单链表
        void find_delete_insert(const int &e); //查找元素，找到则删除并首席插入
        int getCnt(); //返回cnt的值
        void clear (); //清空表，使其为空表
        ~Linklist();
};

Linklist::Linklist(int n) //构造函数，根据输入建立单链表
{
    cnt = 0;
    head = new Node();
    Node* p = head;

    for (int i = 0; i < n; i++)
    {
        int data;
        cin >> data;

        p->next = new Node(data);
        p = p->next;
    }
}

void Linklist::find_delete_insert(const int &e)
{
    Node* p = head->next;
    Node* q = head;

    while (p && p->data != e)
    {
        cnt++;
        q = p;
        p = p->next;   
    }

    if (p)
    {
        cnt++;
        q->next = p->next;
        delete p;

        head->next = new Node(e, head->next);
    }
}

int Linklist::getCnt()
{
    return cnt;
}

void Linklist::clear() //清空表，使其为空表
{    
    Node *p, *q;

    p = head->next;      
    head->next = NULL;

    while (p)
    {   
        q = p->next;
        delete p;
        p = q;
    }
}

Linklist::~Linklist()
{
    clear();
    delete head;
}

int main()
{
    int n;
    cin >> n;

    Linklist* linklist = new Linklist(n);

    int m;
    cin >> m;

    for (int i = 0; i < m; i++)
    {
        int e;
        cin >> e;

        linklist->find_delete_insert(e);
    }

    cout << linklist->getCnt() << endl;

    delete linklist;
    return 0;
}