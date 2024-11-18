// 顺序存储真你妈的好用！

#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

class Forest;

class ForestNode
{
    friend class Forest;
    private:
        int left, right;
        int path; //记录小道
        int index; //记录data/index值
        bool flag; //记录是否被访问过
    public:
        ForestNode(){ left=-1; right=-1; path=-1; flag=false; }
};

class Forest
{
    private:
        ForestNode *array; //顺序存储
        int root; //存储根节点下标
        
        bool isAccessible(int index, int node);; //以下标/data值为index的子树的前序遍历
    public:
        Forest(){ array = new ForestNode[10000]; }; //因为结点值不超过10000，故数组大小设为10000
        void createRoot(int data, int i, vector<int> levelOrder); //根据层次遍历结果创建根节点
        void createNode(int data, int i, vector<int> levelOrder); //根据层次遍历结果建立二叉树
        void createPath(int from, int to); //添加小道
        void isAccessible(int node); //遍历森林，检查结点是否可达
        void reset(vector<int> flag_index); //置零所有flag，准备检测下一个结点是否可达
        ~Forest(){ delete []array; };
};

void Forest::createRoot(int data, int i, vector<int> levelOrder)
{
    root = data;
    if (2*i-1 < levelOrder.size())
        array[data].left = levelOrder[2*i-1];
    if (2*i < levelOrder.size())
        array[data].right = levelOrder[2*i];
}

void Forest::createNode(int data, int i, vector<int> levelOrder)
{
    if (2*i-1 < levelOrder.size())
        array[data].left = levelOrder[2*i-1];
    if (2*i < levelOrder.size())
        array[data].right = levelOrder[2*i];
}

void Forest::createPath(int from, int to)
{
    array[from].path = to;
}

void Forest::isAccessible(int node)
{
    if (isAccessible(root, node))
        cout << "Yes" << endl;
    else
        cout << "No" << endl;
}

bool Forest::isAccessible(int index, int node) //类似前序遍历的递归实现
{
    if (index == -1 || array[index].flag) 
        return false;
    else
        array[index].flag = true; //已经访问过该节点，后续不再访问

    if (index == node)
        return true;

    if (array[index].path > 0) //若存在小道
        return isAccessible(array[index].left, node) || isAccessible(array[index].right, node) || isAccessible(array[index].path, node);
    else //若存在小道
        return isAccessible(array[index].left, node) || isAccessible(array[index].right, node);
}

void Forest::reset(vector<int> flag_index)
{
    for (int i = 0; i < flag_index.size(); i++)
    {
        array[flag_index[i]].flag = false;
    }
}

int main()
{
    int n;
    cin >> n;

    Forest *forest = new Forest();
    vector<int> flag_index; //用于进行清零操作
    for (int i = 0; i < n; i++)
    {
        int k;
        cin >> k;

        vector<int> levelOrder; //存储层次遍历
        for (int j = 0; j < pow(2, k)-1; j++)
        {
            int data;
            cin >> data;
            levelOrder.push_back(data);
            flag_index.push_back(data);
        }

        for (int j = 0; j < pow(2, k)-1; j++)
        {
            if (i == 0 && j == 0)
                forest->createRoot(levelOrder[j], j+1, levelOrder);
            else
                forest->createNode(levelOrder[j], j+1, levelOrder);
        }
    }

    int path_num;
    cin >> path_num;

    for (int i = 0; i < path_num; i++)
    {
        int from, to;
        cin >> from >> to;

        forest->createPath(from, to);
    }

    int ans_num;
    cin >> ans_num;

    vector<int> nodes;
    for (int i = 0; i < ans_num; i++)
    {
        int node;
        cin >> node;

        nodes.push_back(node);
    }

    for (int i = 0; i < ans_num; i++)
    {
        forest->isAccessible(nodes[i]);
        forest->reset(flag_index);
    }

    delete forest;
    return 0;
}