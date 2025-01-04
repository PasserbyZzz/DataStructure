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
                a[i+1] = tmp;  
                change = true;
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
            //对每个子序列进行插入排序
            tmp = a[i]; 
            j = i;
            
            //找到插入位置
            while ((j-step >= 0) && (tmp < a[j-step]))
            {   
                a[j] = a[j-step]; //大者后移
                j -= step;
            }
            a[j] = tmp;
        }
}

// 归并排序
template <class elemType>
void merge(elemType a[], int low, int mid, int high) 
// 两个有序序列合并为一个有序序列，时间复杂度O(max(m,n))
{    
    int i, j, k;    
    elemType *c;     
      
    // 创建实际空间存储合并后结果
    c = new elemType[high-low+1];
    i = low;   
    j = mid + 1;   
    k = 0;

    // 两个有序序列中元素的比较合并 
    while ((i <= mid) && (j <= high))
    {     
        if (a[i] <= a[j]) //注意这里是小于等于
        {   
            c[k] = a[i];   
            i++;  
        }
        else
        {  
            c[k] = a[j];   
            j++; 
        }
        k++;
    }
        
    // 若a序列中i未越界，抄写剩余元素
    while (i <= mid)
    {      
        c[k]=a[i];     
        i++;    
        k++;    
    }

    // 若b序列中j未越界，抄写剩余元素
    while (j <= high)
    {     
        c[k] = a[j];     
        j++;    
        k++;    
    }

    // 将c中元素抄写进a数组
    for (i = 0; i < high-low+1; i++)   
        a[i+low] = c[i];
    delete []c;
}

template <class elemType>void mergeSort(elemType a[], int n)
// 时间复杂度O(nlogn)，稳定排序
{    
    mergeSort(a, 0, n-1); 
}

template <class elemType>
void mergeSort(elemType a[], int low, int high)
{   
    int mid;
    if (low >= high) 
        return;
    mid = (low + high) / 2;
   
    mergeSort(a, low, mid);
    mergeSort(a, mid+1, high);
    merge(a, low, mid, high);
}

// 快速排序
template <class elemType>
void quickSort(elemType a[], int n)
// 时间复杂度最好O(nlogn)，最差O(n^2)
{    
	quickSort(a, 0, n-1);
}

template <class elemType>
void quickSort(elemType a[], int start, int end)
{    
    int i, j, hole;
    elemType temp;
     
    //序列中没有元素或只有一个元素，递归结束
    if (end <= start) 
        return;

    temp = a[start]; //第一个元素作为标杆
    hole = start;
    i = start; //从左到右搜索的指针
    j = end; //从右到左搜索的指针

    while (i < j)
    {   
        //从j位置开始从后往前找第一个小于temp的值
        while ((j > i) && (a[j] >= temp)) //注意这里是大于等于
            j--;
        if (j == i) 
            break;

        a[hole] = a[j];
        hole = j;

        //从i位置开始从前往后找第一个大于等于temp的值
        while ((i < j) && (a[i] < temp)) //注意这里是小于
            i++;
        if (j == i) 
            break;

        a[hole] = a[i];
        hole = i;
    }
    a[hole] = temp;
         
    //对标杆位置左边的序列实施同样的方法
    quickSort(a, start, hole-1);

    //对标杆位置右边的序列实施同样的方法
    quickSort(a, hole+1, end);
}

// 选择排序
template <class elemType>
void selectSort(elemType a[], int n)
// 时间复杂度O(n^2)，不稳定排序
{   
    int i, j, minIndex;      
    elemType temp;

    for (i = 0; i < n; i++)
    {   
        //为第i个位置找合适的数据
        minIndex = i;
        for (j = i+1; j < n; j++)
            if (a[j] < a[minIndex])   
                minIndex = j;

        //将minIndex位置上的数据和位置i上数据交换
        if (minIndex == i) 
            continue;

        temp = a[i];  
        a[i] = a[minIndex];  
        a[minIndex] = temp;
    }
}

// 堆排序
template <class elemType>
void heapSort(elemType a[], int n)
// 时间复杂度O(nlogn)，不稳定排序
{  
    int i, j;
    elemType temp;

   //从倒数第一个非叶子结点开始调整，首次建立大顶堆
    for (i = (n/2)-1; i >= 0; i--) //注意这里从0开始编号
        adjust(a, n, i);
    //换大顶，逐次减少参与的元素，重新调整为大顶堆
    for (j = n-1; j >= 1; j--)
    {    
        //大顶和第i个位置元素交换
        temp = a[0];  
        a[0] = a[j];   
        a[j] = temp;

        //调整第0个元素
        adjust(a, j, 0);
    }
}

template <class elemType>
void adjust(elemType a[], int n, int i)
//对尺寸为n的数组a，假设根为0下标元素，
//调整下标为i的元素，使得以i为根的二叉树为一个大顶堆。
{  
    int maxChild;      
    elemType temp;
 
    while (true)
    {   
        maxChild = 2*i + 1;  //i的左子下标

        if (maxChild > n-1) return;
        if (maxChild+1 <= n-1) //i还有右子
        {
            if (a[maxChild+1] >= a[maxChild])             
               maxChild++; //右子最大
        }
           
        //最大孩子小于父结点
        if (a[i] > a[maxChild]) 
            return;

        //最大孩子大于等于父结点，父结点向下调整
        temp = a[i];
        a[i] = a[maxChild];
        a[maxChild] = temp;

        i = maxChild;  //继续向下调整
    }
}
