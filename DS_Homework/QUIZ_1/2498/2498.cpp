#include <iostream>

using namespace std;

class BTree;

class Node
{
    friend class Forest;
    private:
        int left, right;
        int parent; //记录小道
        int index; //记录data/index值
        bool flag; //记录是否被访问过
    public:
        Node(){ left=-1; right=-1; flag=false; }
};

int main()
{

}