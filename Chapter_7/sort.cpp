#include <iostream>

using namespace std;

// 冒泡排序
template <class elemType>
void bubbleSort(elemType a[], int n) 
// 时间复杂度O(n^2)，稳定排序
{  
    int i, j;   
    bool  change = true;
    elemType tmp;   

    for (j = n-1; j > 0 && change; j--) //提前退出
    {    
        change = false;

        for (i = 0; i < j; i++)
        if (a[i] > a[i+1]) //注意是大于
        {   
            tmp = a[i];  
            a[i] = a[i+1];
            a[i+1] = tmp;  change = true;
        } 
    }
} 

// 简单插入排序
template <class elemType>
void insert(elemType a[], int n, const elemType &x)
//n为有序表a中当前元素的个数，x为待插入新元素
{
    int i;
    //从后往前找第一个不比x大的元素，大者后移一位
    for (i = n-1; i >= 0; i--)
        if (a[i] <= x) //注意是小于等于
            break;
        else a[i+1] = a[i];

    a[i+1] = x; //在腾出的位置上存新元素x
}

template <class elemType>
void insertSort(elemType a[], int n)
// 时间复杂度O(n^2)，稳定排序
{   
    int i;
    elemType tmp;

    //将第i个元素插入到前i-1个元素的有序序列中
    for (i = 1; i < n; i++) //注意i从1开始
    {   
        tmp = a[i];   
        insert(a, i, tmp);  
    }
}

// 希尔排序
template <class elemType>
void shellSort(elemType a[], int n)
// 时间复杂度 < O(n^2)，不稳定排序
{   
    int step, i, j;
    elemType tmp;

    for (step = n/2; step > 0; step /= 2)
        for (i = step; i < n; i++)
        {    
            tmp = a[i];
            j = i;
            
            while ((j-step >= 0)&&(tmp < a[j-step]))
            {   
                a[j] = a[j-step];
                j -= step;
            }
            a[j] = tmp;
        }
}

