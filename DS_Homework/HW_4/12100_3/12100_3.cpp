#include <iostream>
#include <queue>

using namespace std;

int main() 
{
    int N;
    cin >> N;

    // 小顶堆优先级队列，用于存储权重
    priority_queue<int, vector<int>, greater<int>> F;

    // 输入所有权重到优先级队列
    for (int i = 0; i < N; ++i) 
    {
        int weight;
        cin >> weight;
        F.push(weight);
    }

    int ans = 0;

    // 哈夫曼树构建
    while (F.size() > 1) 
    {
        // 取出两个最小的权重
        int first_min = F.top(); 
        F.pop();
        int second_min = F.top(); 
        F.pop();

        // 合并权重
        int newWeight = first_min + second_min;
        ans += newWeight;

        // 将新权重加入优先级队列
        F.push(newWeight);
    }

    cout << ans << endl;

    return 0;
}