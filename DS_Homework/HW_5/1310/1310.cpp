#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Meeting
{
    int start;
    int end;

    // 重载大于运算符，用于构造最小堆
    bool operator>(const Meeting& other) const 
    {
        return start > other.start;
    }
};

int minNum(priority_queue<Meeting, vector<Meeting>, greater<Meeting>> meetings)
{
    int cnt=1;
    priority_queue<int, std::vector<int>, std::greater<int>> minHeap; //存储空余会议室
    minHeap.push(-1);

    while (!meetings.empty())
    {
        Meeting minStartMeeting = meetings.top();
        meetings.pop();
        
        // 有空余
        if (minHeap.top() <= minStartMeeting.start)
        {
            minHeap.pop();
            minHeap.push(minStartMeeting.end);
        }
        // 无空余
        else
        {
            minHeap.push(minStartMeeting.end);
            cnt++;
        }
    }

    return cnt;
}

int main()
{
    int n;
    cin >> n;

    priority_queue<Meeting, vector<Meeting>, greater<Meeting>> meetings; //要求存储起始时间从小到大的会议
    for (int i = 0; i < n; i++)
    {
        int s, e;
        cin >> s >> e;

        Meeting meeting;
        meeting.start = s;
        meeting.end = e;
        meetings.push(meeting);
    }

    cout << minNum(meetings) << endl;

    return 0;
}