#include <iostream>
#include <string>
#include <queue>

using namespace std;

class Node
{   
    friend class BTree;
    private:
        string data;       
        Node *left, *right;
    public:
        Node(){ left=NULL; right=NULL; };
        Node(string e, Node* L=NULL, Node *R=NULL)
        {  
            data = e;
            left=L; right=R;
        }
};
 
class BTree
{
    private:
        Node *root;
        int Height (Node *t);
        void DelTree(Node *t);
    public:
        BTree(){ root=NULL; }
        void createTree(queue<string> levelOrder);
        int Height (); 
        void DelTree();
        ~BTree();
};

void BTree::createTree(queue<string> levelOrder)
{
    if (levelOrder.front() == "null")
        return;
    queue<Node*> nodes;
    Node* p;
    string current = levelOrder.front();
    levelOrder.pop();

    root = new Node(current);
    root->left = new Node("#");
    root->right = new Node("#");

    nodes.push(root->left);
    nodes.push(root->right);

    while (!levelOrder.empty())
    {
        current = levelOrder.front();
        levelOrder.pop();

        if (current != "null")
        {
            p = nodes.front();
            nodes.pop();
            p->data = current;
            p->left = new Node("#");
            p->right = new Node("#");
            nodes.push(p->left);
            nodes.push(p->right);
        }
        else
        {
            nodes.pop();
        }
    }
}

int BTree::Height()
{ 
    return Height(root); 
}


int BTree::Height(Node *t) 
{  
    int hl, hr;     
    if (!t) return 0;
    if (t->data == "#") return 0;
   
    hl = Height(t->left);      
    hr = Height(t->right);
   
    if (hl >= hr) 
        return 1 + hl;    
    return 1 + hr;                  
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
    int num_nodes;
    cin >> num_nodes;

    queue<string> levelOrder;
    for (int i = 0; i < num_nodes; i++)
    {
        string data;
        cin >> data;

        levelOrder.push(data);
    }

    BTree* tree = new BTree();
    tree->createTree(levelOrder);
    cout << tree->Height();

    delete tree;

    return 0;
}