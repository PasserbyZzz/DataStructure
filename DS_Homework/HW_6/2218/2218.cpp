#include <iostream>
#include <sstream>
#include <queue>

using namespace std;

int main()
{
    priority_queue<int, vector<int>, std::greater<int>> minHeap; //存储节点值

    string preOrder;
    getline(cin, preOrder);

    istringstream ss(preOrder);
    string node;
    while (ss >> node)
    {
        if (node != "-1")
            minHeap.push(stoi(node));
    }

    int minDifference = 2000000;
    while (!minHeap.empty())
    {
        int first_min = minHeap.top();
        minHeap.pop();

        if (minHeap.empty())
            break;
        int second_min= minHeap.top();

        if (second_min - first_min < minDifference)
            minDifference = second_min - first_min;
    }

    cout << minDifference << endl;

    return 0;
}