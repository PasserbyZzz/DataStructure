// 顺序和这般查找算法的实现

#include <iostream>

using namespace std;

class illegalSize{};

template <class elemType>
class staticSearch
{ 
    private:
        elemType *data; //存储静态数据
        int len;
    public:
        staticSearch(elemType a[], int n);
        int Search(const elemType &x) const; //顺序查找
        int BSearch(const elemType &x) const; //折半查找
        ~staticSearch(){delete []data;}
};

template <class elemType>
staticSearch<elemType>::staticSearch(elemType a[], int n)
{  
    len = n;
    data = new elemType[n+1]; //多一个哨兵位
    if (!data) throw illegalSize();

    for (int i = 1; i < n+1; i++) 
        data[i]=a[i-1]; //0下标不用
}

template <class elemType>
int staticSearch<elemType>::Search(const elemType &x) const //顺序查找
// 时间复杂度为O(n)
{  
    int i;    
    data[0] = x;

    for (i = len; data[i] != x; i--);
    return i;
}

template <class elemType>
int staticSearch<elemType>::BSearch(const elemType &x) const //折半查找
// 时间复杂度为O(log_2 n)
{  
    int mid, low, high;      
    low = 1; 
    high = len;

    while (low <= high)
    {  
        mid = (low + high) / 2;
        if (x == data[mid]) break; //查找成功    
        else
            if (x < data[mid]) 
                high = mid -1; //x小于中间位置元素
            else  
                low = mid +1; //x大于中间位置元素
      }

    if (low <= high) 
        return mid;
    return 0;    
}

int main()
{
    int a[10] = {72, 90, 25, 60, 30, 70, 80, 19, 20, 35};
    int pos, x;
    staticSearch<int> sd(a,10);

    cout << "Input thedata you want to seek:";
    cin >> x;
    
    pos = sd.Search(x);
    if (pos == 0)
        cout << x << " doesn't exist!";
    else
        cout << x << " exists!";
    cout << endl;

    return 0;
}
