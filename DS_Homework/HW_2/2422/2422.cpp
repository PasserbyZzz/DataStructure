// 暴力模拟

#include <iostream>
#include <queue>

using namespace std;

void num(queue<int> children, queue<int> index, int time)
{
    int i = 0, next = 1;
    bool flag = true;

    while (!index.empty())
    {
        if (children.front() == -1)
        {
            flag = true;
            i++;
            i = max(i, next);

            children.push(children.front());
            children.pop();
        }
        if (children.front() == i)
        {
            cout << index.front() << ' ';
            children.pop();
            index.pop();
        }
        else 
        {
            if (flag)
            {
                next = children.front();
                flag = false;
            }
            else if (children.front() < next)
            {
                next = children.front();
            }

            children.push(children.front());
            children.pop();
            index.push(index.front());
            index.pop();
        }
    }
}

int main()
{
    int n, time;
    cin >> n >> time;

    queue<int> children, index;
    for (int i = 0; i < n; i++)
    {
        int t;
        cin >> t;

        if (!(t % time))
            children.push(t / time - 1);
        else
            children.push(t / time);
        index.push(i);
    }
    children.push(-1); //压入队尾，用于标记每次循环

    num(children, index, time);

    return 0;
}