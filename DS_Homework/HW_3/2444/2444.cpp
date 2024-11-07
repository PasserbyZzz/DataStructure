#include <iostream>
#include <stack>
#include <queue>
#include <vector>

using namespace  std;

class BTree;

class Node
{   
    friend class BTree;
    private:
        int data;       
        Node *left, *right;
    public:
        Node(){ left=NULL; right=NULL; };
        Node(const int &e, Node* L=NULL, Node *R=NULL)
        {  
            data = e;
            left=L; right=R;
        }
};

class BTree
{
    private:
        Node *root;
        void DelTree(Node *t);
    public:
        BTree(){ root=NULL; }
        void createTree(vector<int> preOrder); //根据前序遍历结果建立二叉树
        bool isCousin(int x, int y); //检查两个节点是否为堂姐妹堂兄弟节点
        void DelTree();
        ~BTree();
};

void BTree::createTree(vector<int> preOrder)
{
    if (!preOrder[0])
        return; 
    else
        root = new Node(preOrder[0]);

    stack<int> datas, cnts; //记录节点数据与访问次数
    stack<Node*> nodes;
    Node *p;
    int flag;
    int zero=0, one=1;

    datas.push(preOrder[0]);
    cnts.push(zero);
    nodes.push(root);
    int i = 0;
    while (i < preOrder.size() - 1)
    {
        flag = cnts.top();
        cnts.pop();
        p = nodes.top();

        if (flag == 0) //访问次数为0，有左节点则带建立左节点
        {
            if (preOrder[i+1] > 0)
            {
                cnts.push(one);
                Node *tmp = new Node(preOrder[i+1]);              
                p->left = tmp;
                nodes.push(tmp);
                datas.push(preOrder[i+1]);
                cnts.push(zero);
            }
            else
            {
                cnts.push(one);
            }
        }
        else //访问次数为1，有右节点则建立右节点
        {
            if (preOrder[i+1] > 0)
            {
                nodes.pop();
                datas.pop();
                Node *tmp = new Node(preOrder[i+1]);
                p->right = tmp;
                nodes.push(tmp);
                datas.push(preOrder[i+1]);
                cnts.push(zero);
            }
            else
            {
                nodes.pop();
                datas.pop();
            }
        }

        i++;
    }
}

bool BTree::isCousin(int x, int y) //层次遍历
{
    queue<Node*> que;
    queue<int> height; //记录层次
    Node *p;
    int zero=0, height_1=-1, height_2=-2, h;

    if (!root) return false;
    que.push(root);
    height.push(zero);
    while (!que.empty())
    {
        p = que.front();
        que.pop();
        h = height.front();
        height.pop();
        if (p->data == x) //节点data值与x或y相同
            height_1 = h;
        if (p->data == y)
            height_2 = h;

        if (p->left && p->right) // x，y正好是左右孩子，即亲兄弟
        {
            if ((p->left->data == x && p->right->data == y) || 
                (p->left->data == y && p->right->data == x))
                return false;
        }

        if (p->left)
        {
            que.push(p->left);
            int tmp = h + 1;
            height.push(tmp);
        }
        if (p->right)
        {
            que.push(p->right);
            int tmp = h + 1;
            height.push(tmp);
        }
    }

    if (height_1 == height_2)
        return true;
    else
        return false;
}


void BTree::DelTree()
{  
    DelTree(root);    
    root = NULL;   
}

void BTree::DelTree(Node *t)
{  
    if (!t) return;       
    DelTree(t->left);       
    DelTree(t->right);
    delete t;   
}

BTree::~BTree()
{
    DelTree();
}

int main()
{
    int n;
    cin >> n;

    int num[2*n]; //存储数据
    for (int i = 0; i < 2*n; i += 2)
    {
        int x, y;
        cin >> x >> y;
        num[i] = x;
        num[i+1] = y;
    }

    vector<int> preOrder; //存储前序遍历结果
    int a;
    while (cin >> a)
    {
        preOrder.push_back(a);
        if (cin.get() == '\n')
            break;
    }
        
    BTree* tree = new BTree();
    tree->createTree(preOrder);
    for (int i = 0; i < 2*n; i += 2) //输出结果
        cout << tree->isCousin(num[i], num[i+1]) << endl;
    delete tree; //显式调用 delete 释放tree对象本身的内存

    return 0;
}