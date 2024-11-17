#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

//存储Huffman结点
struct HuffmanNode
{
    double weight;
    int parent;
    int left, right;
};

int minIndex(priority_queue<int, vector<int>, greater<int>>* F_2, int first_min, int m)
{
    
}

HuffmanNode* BestBinaryTree(vector<int> F_1, priority_queue<int, vector<int>, greater<int>>* F_2, int n) 
{
    HuffmanNode *BBTree;
    int first_min, second_min; 
    int m = n*2; 
    int i, j;

    //先移植所有叶子节点
    BBTree = new HuffmanNode[m];
    for (j = 0; j < n; j++)
    {   
        i = m-1-j;
        BBTree[i].weight = F_1[j];
        BBTree[i].parent = 0;
        BBTree[i].left = 0;
        BBTree[i].right = 0;
    }
    i = n-1; //第一个非叶子结点的下标
          
    while (i != 0) //数组左侧尚有未用空间，即新创建的结点个数还不足
    {   
        first_min = minIndex(F_2, i, m);  
        BBTree[first_min].parent = i; 
        second_min = minIndex(F_2, i, m);  
        BBTree[second_min].parent = i; 

        BBTree[i].weight = BBTree[first_min].weight + BBTree[second_min].weight;
        BBTree[i].parent = 0;
        BBTree[i].left = first_min; BBTree[i].right = second_min;

        i--;
    }

    return BBTree;
}

int calSum()
{

}

int main()
{
    int N;
    cin >> N;

    vector<int> F_1; //用于遍历
    priority_queue<int, vector<int>, greater<int>>* F_2 = new priority_queue<int, vector<int>, greater<int>>; //小顶堆优先级队列，便于更快找最小值
    for (int i = 0; i < N; i++)
    {
        int freq;
        F_1.push_back(freq);
        F_2->push(freq);
    }

    return 0;
}