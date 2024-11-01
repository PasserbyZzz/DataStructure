// 表达式树建立及计算测试程序

#include <iostream>
#include "btree.h"

using namespace std;

int main()
{
    BTree<char> tree;
    char exp[]="(4-2)*(7+(4+6)/2)+2";
    int result;

    tree.buildExpTree(exp); //建立表达式树
    tree.InOrder(); //用中序遍历验证建好的表达式树
    result = tree.calExpTree(); //计算表达式树 
    cout << endl << "The result is:" << result << endl;

    return 0;
}