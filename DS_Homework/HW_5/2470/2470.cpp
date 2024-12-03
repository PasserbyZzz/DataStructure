#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int maxOfVector(vector<int> datas)
{
    int max = 0;
    for (int i = 0; i < datas.size(); i++)
    {
        if (datas[i] > max)
            max = datas[i];
    }

    return max;
}

struct Blog
{
    int index;
    vector<int> datas;

    // 重载小于于运算符，用于构造大顶堆
    bool operator<(const Blog& other) const 
    {
        if (maxOfVector(datas) < maxOfVector(other.datas))
            return true;
        if (maxOfVector(datas) == maxOfVector(other.datas))
            return index < other.index;
        else
            return false;
    }
};

int main()
{
    int T;
    cin >> T;

    int D, P; //分别表示最大天数和总帖子数
    cin >> D >> P;

    vector<int> results;
    vector<Blog> blogs; 
    for (int i = 0; i < D; i++)
    {
        priority_queue<Blog> maxHeap;
        for (int j = 0; j < P; j++)
        {
            int data;
            cin >> data;

            if (i == 0)
            {
                Blog blog;
                blog.index = j;
                for (int k = 0; k < T - 1; k++)
                    blog.datas.push_back(0);
                blog.datas.push_back(data);
                blogs.push_back(blog);
            }
            else
            {
                blogs[j].datas.push_back(data);
                blogs[j].datas.erase(blogs[j].datas.begin());
            }

            maxHeap.push(blogs[j]);
        }

        int res = maxHeap.top().index;
        results.push_back(res+1);
    }

    for(int i = 0; i < results.size(); i++)
        cout << results[i] << ' ';

    return 0;
}


