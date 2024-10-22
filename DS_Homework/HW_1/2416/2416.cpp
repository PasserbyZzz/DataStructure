#include <iostream>

using namespace std;

class FreeList;

class Memoryblock 
{
        friend class FreeList;
    private:
        int start;
        int size;
        Memoryblock *next;
    public:
        Memoryblock(): next(NULL) {};
        Memoryblock(const int st, const int si, Memoryblock* N=NULL): start(st), size(si), next(N) {};
};

class FreeList 
{
    private:
        Memoryblock *head;
    public:
        FreeList(const int st[], const int si[], const int n);
        void allocate(const int request_size);
        void release(const int st, const int si);
        void display();
        void clear();
        ~FreeList();
};

FreeList::FreeList(const int st[], const int si[], const int n) 
{
    head = new Memoryblock();

    Memoryblock *p = head;
    for (int i = 0; i < n; i++) {
        p->next = new Memoryblock(st[i], si[i]);
        p = p->next;
    }
}

void FreeList::clear() 
{
    Memoryblock *p = head->next;
    while (p) {
        Memoryblock *q = p->next;
        delete p;
        p = q;
    }
    head->next = NULL;
}

void FreeList::allocate(const int request_size) 
{
    Memoryblock *q = head, *p = head->next;

    while (p) {
        if (p->size >= request_size) 
        {
            if (p->size > request_size) //内存块大小大于所需，进行分割
            {
                p->start += request_size;
                p->size -= request_size;
            } 
            else //内存块大小等于所需，直接丢弃
            {
                q->next = p->next;
                delete p;
            }

            return;
        }
        q = p;
        p = p->next;
    }
}

void FreeList::release(const int st, const int si) 
{
    Memoryblock *p = head, *q = head->next; //q是p的直接后继节点

    while (q && q->start < st) //查找合适的start位置
    {
        p = q;
        q = q->next;
    }

    p->next = new Memoryblock(st, si, q); //插入内存块

    if (p != head && p->start + p->size == p->next->start) //与前内存块合并
    {
        p->size += p->next->size;
        Memoryblock *tmp = p->next; //删除该节点
        p->next = tmp->next;
        delete tmp;

        //检查是否可以再次与后内存块合并
        if (p->start + p->size == q->start)
        {
            p->size += q->size;
            p->next = q->next;
            delete q;
        }

        return;
    }
    if (q && p->next && p->next->start + p->next->size == q->start) //与后内存块合并
    {
        p->next->size += q->size;
        p->next->next = q->next;
        delete q;
    }
}

void FreeList::display() //输出答案
{
    Memoryblock *p = head->next;

    while (p) {
        cout << '(' << p->start << ',' << p->size << ") ";
        p = p->next;
    }
    cout << endl;
}

FreeList::~FreeList() 
{
    clear();
    delete head;
}

int main() 
{
    int n;
    cin >> n;

    int st[n], si[n];
    for (int i = 0; i < n; i++) {
        cin >> st[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> si[i];
    }

    FreeList free(st, si, n);

    int m;
    cin >> m;

    for (int i = 0; i < m; i++)
    {
        int op;
        cin >> op;

        if (op == 1) 
        {
            int request_size;
            cin >> request_size;
            free.allocate(request_size);
        } 
        else if (op == 2) 
        {
            int start, size;
            cin >> start >> size;
            free.release(start, size);
        }
    }

    free.display();

    return 0;
}