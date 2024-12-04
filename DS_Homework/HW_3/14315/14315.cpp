// 二叉树的顺序存储

#include <iostream>

using namespace std;

class BTree;

class Node
{   
    friend class BTree;
    private:
        //以该结点在数组中的下标表示其data值      
        int left, right;
    public:
        Node(){ left=-1; right=-1; };
};

class BTree
{
    private:
        Node *array; //顺序存储
        int root; //存储根节点下标
        void mirrortree(int index); //生成以下标/data值为index的子树的镜像
        void PostOrder(int index); //以下标/data值为index的子树的后序遍历
    public:
        BTree(){ array = new Node[10000]; }; //因为结点值不超过10000，故数组大小设为10000
        void createRoot(int a, int b, int c); //根据输入创建根节点
        void createNode(int a, int b, int c); //根据输入不断完善二叉树
        void mirrortree(); //生成整棵二叉树的镜像
        void PostOrder(); //整棵二叉树后序遍历 
        ~BTree(){ delete []array; };
};

void BTree::createRoot(int a, int b, int c)
{
    root = a;
    array[a].left = b;
    array[a].right = c;
}

void BTree::createNode(int a, int b, int c)
{
    array[a].left = b;
    array[a].right = c;
}

void BTree::mirrortree(int index)
{
    if (index != -1) //该结点存在
    {
        if ((array[index].left > 0) || (array[index].right > 0))
        {
            int tmp = array[index].left;
            array[index].left = array[index].right;
            array[index].right = tmp;
    
            //递归生成该结点的左右子树的镜像
            mirrortree(array[index].left);
            mirrortree(array[index].right);
        }
    }

    else
        return;
}

void BTree::mirrortree()
{
    mirrortree(root);
}

void BTree::PostOrder(int index)
{
    if (index == -1) return;

    PostOrder(array[index].left);
    PostOrder(array[index].right);
    cout << index << ' ';
}

void BTree::PostOrder()
{
    PostOrder(root);
}

int main()
{
    int n;
    cin >> n;

    BTree *tree = new BTree();
    for (int i = 0; i < n; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;

        if (i == 0)
            tree->createRoot(a, b, c);
        else
            tree->createNode(a, b, c);
    }

    tree->mirrortree();
    tree->PostOrder();

    delete tree;
    return 0;
}