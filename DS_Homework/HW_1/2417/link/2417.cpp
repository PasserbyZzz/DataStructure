#include <iostream>

using namespace std;

struct Type
{  
    int num; 
    int cnt; 
};

struct Node
{   
    Type data;
    Node* next;
};

int main()
{
    int n;
    cin >> n;

    int a[n];
    for (int i = 0; i < n; i++)
        cin >> a[i];

    Node* head = NULL; 
    for (int i = 0; i < n; i++)
    {
        Node* p = head;
        Node* prior = NULL;

        while (p)
        {
            if (a[i] == p->data.num)
            {
                p->data.cnt++;
                break; 
            }
            prior = p;
            p = p->next;
        }

        if (!p) 
        {
            Node* tmp = new Node;
            tmp->data.num = a[i];
            tmp->data.cnt = 1;
            tmp->next = NULL;

            if (prior) 
                prior->next = tmp;
            else 
                head = tmp; 
        }
    }

    Node* p = head;
    int maxCnt = 0;
    while(p)
    {
        if (p->data.cnt > maxCnt)
            maxCnt = p->data.cnt;
        p = p->next;
    }

    cout << maxCnt;

    while (head)
    {
        Node* tmp = head;
        head = head->next;
        delete tmp;
    }

    return 0;
}
