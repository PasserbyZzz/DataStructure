#include <iostream>
#include <queue>

using namespace std;

int NthUgly(int n)
{
    int currentUgly=0, cnt=0; //记录当前丑数及其序号
    priority_queue<int, std::vector<int>, std::greater<int>> minHeap; //存储丑数
    minHeap.push(1);

    while (true)
    {
        // 获取不重复的丑数
        while (minHeap.top() == currentUgly) 
        {
            minHeap.pop();
        }
        currentUgly = minHeap.top();
        cnt++;

        // 当前丑数的序号达到n
        if (cnt == n)
            return currentUgly;

        // 将当前丑数的2、3、5倍加入小顶堆
        minHeap.push(2*currentUgly);
        minHeap.push(3*currentUgly);
        minHeap.push(5*currentUgly);
    }
}

int main()
{
    int n;
    cin >> n;

    cout << NthUgly(n) << endl;

    return 0;
}