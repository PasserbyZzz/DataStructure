#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

class HuffmanTree;

//存储Huffman结点
class HuffmanNode
{
    friend class HuffmanTree;
    private:
        int freq;
        HuffmanNode *left, *right;
    public:
        HuffmanNode(){ left=NULL; right=NULL; };
        HuffmanNode(const int &e, HuffmanNode* L=NULL, HuffmanNode *R=NULL)
        {  
            freq = e;
            left=L; right=R;
        }
};

class HuffmanTree
{
    private:
        HuffmanNode *root;
        void DelTree(HuffmanNode *t);
    public:
        HuffmanTree(){ root=NULL; }
        void LevelOrder();
        HuffmanNode* buildTree(priority_queue<int, vector<int>, greater<int>> F_2);
        void DelTree(); 
};

HuffmanNode* HuffmanTree::buildTree(priority_queue<int, vector<int>, greater<int>> F_2)
{
    int first_min, second_min;
    queue<HuffmanNode> q;

    while (F_2.size() > 1)
    {
        first_min = F_2.top();
        F_2.pop();
        second_min = F_2.top();
        F_2.pop();

        HuffmanNode* l = new HuffmanNode(first_min);
        HuffmanNode* r = new HuffmanNode(second_min);
        root = new HuffmanNode(first_min+second_min, l, r);

        F_2.push(first_min+second_min);
    }
}

void HuffmanTree::LevelOrder()
{   
    queue<HuffmanNode*> que;
    HuffmanNode *p;
    int ans = 0;

    if (!root) return; 
    que.push(root);
    while (!que.empty())
    {
        p = que.front();
        que.pop();

        if (p->left) que.push(p->left);
        if (p->right) que.push(p->right);
    }
    cout << endl;
}

void HuffmanTree::DelTree()
{  
    DelTree(root);    
    root = NULL;   
}

void HuffmanTree::DelTree(HuffmanNode *t)
{  
    if (!t) return;       
    DelTree(t->left);       
    DelTree(t->right);
    delete t;   
}

int main()
{
    int N;
    cin >> N;

    priority_queue<int, vector<int>, greater<int>> F_2; //小顶堆优先级队列，便于更快找最小值
    for (int i = 0; i < N; i++)
    {
        int freq;
        F_2.push(freq);
    }

    HuffmanTree* tree = new HuffmanTree(); 
    tree->buildTree(F_2);
    tree->LevelOrder();

    delete tree;
    return 0;
}