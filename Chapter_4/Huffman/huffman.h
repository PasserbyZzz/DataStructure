// 用哈夫曼算法构造最优二叉树

#include <iostream>
#include "seqStack.h"

using namespace std;

//存储Huffman结点
template <class elemType>
struct HuffmanNode
{
    elemType data;
    double weight;
    int parent;
    int left, right;
};

//在所有父亲为0的元素中找最小值的下标
template <class elemType>
int minIndex(HuffmanNode<elemType> Bt[], int k, int m) 
//k为数组的左边界，m为数组的右边界
{  
    int i, min, minWeight = 9999; //用一个不可能且很大的权值

    for (i = m-1; i > k; i--) //从后往前找最小值
    {   
        if ((Bt[i].parent == 0) && (Bt[i].weight < minWeight)) //排除已经在树上的结点
        {   
            min = i;     
            minWeight = Bt[min].weight;     
        }
    }
    return min;  
}

//构造最优二叉树
template <class elemType>
HuffmanNode<elemType> *BestBinaryTree(elemType a[], double w[], int n) 
//a为叶子结点的数据，w为叶子结点的权值，n为叶子结点的个数
// 算法总的时间复杂度为O(𝑛^2 )（可优化）
{
    HuffmanNode<elemType> *BBTree;
    int first_min, second_min; //最小和次小的权值
    int m = n*2; //共2n-1个结点，下标为0处不放结点，故数组的大小为2n
    int i, j;

    //在数组中从后往前存储叶子结点
    BBTree = new HuffmanNode<elemType>[m];
    for (j = 0; j < n; j++)
    {   
        i = m-1-j;
        BBTree[i].data = a[j];
        BBTree[i].weight = w[j];
        BBTree[i].parent = 0;
        BBTree[i].left = 0;
        BBTree[i].right = 0;
    }
    i = n-1; // i is the position which is ready for the first new node
          
    while (i != 0) //数组左侧尚有未用空间，即新创建的结点个数还不足
    {   
        first_min = minIndex(BBTree, i, m);  
        BBTree[first_min].parent = i; //修改parent值，保证下次找最小值时不会再被找到
        second_min = minIndex(BBTree, i, m);  
        BBTree[second_min].parent = i; //修改parent值，保证下次找最小值时不会再被找到

        BBTree[i].weight = BBTree[first_min].weight + BBTree[second_min].weight;
        BBTree[i].parent = 0;
        BBTree[i].left = first_min; BBTree[i].right = second_min;

        i--;
    }

    //------辅助调试开始------
    //显示BBTree中的每一个结点
    for(i = 1; i < n; i++) //显示非叶子结点信息
        cout << i << " data:" << "-" << " weight:" << BBTree[j].weight
        << " left:" << BBTree[j].left
        << " right:" << BBTree[j].right << endl;
    for(; i < m; i++) //显示叶子结点信息
        cout<< i << " data:" << BBTree[j].data << " weight:" << BBTree[j].weight
        << " left:" << BBTree[j].left
        << " right:" << BBTree[j].right << endl;
    //------辅助调试结束------

    return BBTree;
}

template <class elemType>
char ** HuffmanCode(HuffmanNode<elemType> BBTree[], int n)
//n为待编码元素的个数，BBTree数组为Huffman树，数组长度为2n
//时间复杂度最好为O(nlogn)，最坏为O(n^2)
{
    seqStack<char> s;
    char **HFCode;
    char zero = '0', one = '1';
    int m, i, j, parent, child;

    //为HFCode创建空间
    HFCode = new char* [n]; //n个代编码元素
    for (i = 0; i < n; i++)
        HFCode[i] = new char[n+1]; //每位元素编码最长n-1位，+1为n=1时储备
        
    m = 2*n; //BBTree数组长度
    if (n == 0) return HFCode; //没有元素
    if (n == 1) //元素个数为1
    {
        HFCode[0][0] = '0', HFCode[0][1] = '\0';
        return HFCode;
    }

    for (i = m-1; i >= n; i--) //从后往前找叶子结点，n到2n-1为叶子结点
    {
        child = i;
        parent = BBTree[child].parent;
        while (parent != 0) //从叶子结点往上找
        {
            if (BBTree[parent].left == child)
                s.push(zero);
            else
                s.push(one);
            child = parent;
            parent = BBTree[parent].parent;
        }

        j = 0;
        while (!s.isEmpty()) //将栈中的编码取出
        {
            HFCode[m-i-1][j] = s.top();
            s.pop();
            j++;
        }
        HFCode[m-i-1][j] = '\0'; //字符串结束符!!

        //------辅助调试开始------
        cout << "The huffmanCode of " << BBTree[i].data << " is:" << HFCode[m-i-1] << endl;
        //------辅助调试结束------
    }
    return HFCode;
}