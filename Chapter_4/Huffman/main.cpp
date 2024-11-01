#include<iostream>
#include "huffman.h"

using namespace std;

int main()
{
    char a[6] = {'A','B','C','D','E','F'};
    double w[6] = {3, 8, 10, 12, 50, 4};
    HuffmanNode<char>* Tree;

    Tree = BestBinaryTree(a, w, 6); //建立哈夫曼树
    HuffmanCode(Tree, 6); //求哈夫曼编码

    return 0;
} 