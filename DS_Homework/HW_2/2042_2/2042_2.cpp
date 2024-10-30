// 优先级队列

#include <iostream>

using namespace std;

class illegalSize{};
class outOfBound{};

// 从1开始编号
template <class elemType>
class priorityQueue
{    
    private:
        elemType *array;   
        elemType *index;
        int maxSize, currentLen;
        void doubleSpace(); //扩展队队列元素的存储空间             
        void adjust(int hole); //调整下标为hole的元素，使成为小顶堆
        void build(int r); //递归调整
    public:
        priorityQueue(int size=10); //建立空优先级队列
        priorityQueue(elemType a[], int n); //建立非空优先级队列，即建小顶堆
        bool isEmpty() { return currentLen==0; };  //判断队空否
        bool isFull() { return currentLen==maxSize-1; };  //判断队满否
        elemType front(); //读取队首元素的值，队首不变
        void enQueue(const elemType &x, const elemType &y); //将x进队，成为新的队尾
        void deQueue(); //将队首元素出队
        ~priorityQueue() { delete []array; delete []index; }; //释放队列元素所占据的动态数组
};

template <class elemType>
priorityQueue<elemType>::priorityQueue(int size) //建立空优先级队列
{
    array = new elemType[size]; //申请实际的队列存储空间
    index = new elemType[size];
    if (!array || !index) throw illegalSize();
    maxSize = size;
    currentLen = 0;
}

template <class elemType>
priorityQueue<elemType>::priorityQueue(elemType a[], int n) //建立优先级队列
{
    if (n < 1) throw illegalSize();

    array = new elemType[n+10]; //申请实际的队列存储空间，多10，支持入队
    index = new elemType[n+10];
    if (!array || !index) throw illegalSize();

    maxSize = n + 10;     
    currentLen = n;
    for (int i = 1; i <= n; i++) //根结点从1开始
    {
        index[i] = i-1;
        array[i] = a[i-1]; 
    }
    // for (int i = 1; i <= n; i++) //根结点从1开始
    //     cout << '(' << index[i] << ',' << array[i] << ')' << ' ';
    for (int i = n/2; i >= 1; i--) //从最后一个非叶结点开始，注意：前提是根结点从1开始
    {
        adjust(i);   //首次建立小顶堆
        // for (int i = 1; i <= n; i++) //根结点从1开始
        //     cout << '(' << index[i] << ',' << array[i] << ')' << ' ' << endl;
    }

    // for (int i = 1; i <= n; i++) //根结点从1开始
    //     cout << '(' << index[i] << ',' << array[i] << ')' << ' ' << endl;
}

template <class elemType>
void priorityQueue<elemType>::build(int r) //调整以编号r为根的子树为优先级队列
{
    if (r > currentLen/2) return; //如果r是叶结点，则返回

    build(2*r); //将左子树调整为堆
    build(2*r+1); //将右子树调整为堆
    adjust(r); //调整以r为根的堆
}

template <class elemType>
void priorityQueue<elemType>::adjust(int hole) //从某个节点开始，向下调整该节点的位置，使得整个堆重新满足堆的性质
//反复向下调整hole的位置，需要比较hole和其左右子结点的大小
{ 
    int minChild; //hole的最小子结点 
    elemType x, y; //暂存hole的值
    x = array[hole];
    y = index[hole];

    while (true)
    {    
        minChild = 2*hole; //hole的左子下标
        if (minChild > currentLen) //越界
            break;

        if (minChild+1 <= currentLen) //hole还有右子
           if (array[minChild+1] < array[minChild])             
                   minChild++; //右子最小

        if (x <= array[minChild]) //找到了合适的位置
            break;

        array[hole] = array[minChild];
        index[hole] = index[minChild];
        hole = minChild;  //继续向下调整
    }

    array[hole] = x;
    index[hole] = y;
}
//比较次数最多为：二叉树的高度

template <class elemType>
elemType priorityQueue<elemType>::front() //读取队首元素（编号为1）的值，队首不变
{    
    if (isEmpty()) throw outOfBound();    

    return index[1]; 
}

template <class elemType>
void priorityQueue<elemType>::deQueue() //将队首元素出队
{  
    if (isEmpty()) throw outOfBound();

    array[1] = array[currentLen]; //将队尾元素放到根结点
    index[1] = index[currentLen];
    currentLen--;
    adjust(1); //调整根结点，使之成为小顶堆
}

template <class elemType>
void priorityQueue<elemType>::enQueue(const elemType &x, const elemType &y)  //将x进队
{  
    if (isFull()) doubleSpace();

    int hole ; //hole位置向上调整
    currentLen++; 

    for (hole = currentLen; hole > 1 && x < array[hole/2]; hole /= 2) //向上调整，只需要比较x和父结点的大小
    {
        array[hole] = array[hole/2]; //hole的父结点下移
        index[hole] = index[hole/2];
    }
    array[hole] = x; //找到了合适的位置，插入x
    index[hole] = y;
}
//比较次数最多为二叉树高度，故入队时间效率为O(log_2⁡𝑛)

template <class elemType>
void priorityQueue<elemType>::doubleSpace() 
{
    elemType *tmp = new elemType[2*maxSize]; // 创建一个新的数组，大小是原数组的两倍
    elemType *tmpIndex = new elemType[2*maxSize];

    for (int i = 1; i <= currentLen; i++) 
    {
        tmp[i] = array[i]; // 将原数组中的元素复制到新数组中
        tmpIndex[i] = index[i];
    }

    delete[] array; // 删除原数组
    delete[] index;
    array = tmp; // 指向新数组
    maxSize *= 2; // 更新最大容量
}

int main()
{
    int n, time;
    cin >> n >> time;

    int children[n];
    for (int i = 0; i < n; i++)
    {
        int t;
        cin >> t;

        if (!(t % time))
            children[i] = t / time - 1;
        else
            children[i] = t / time;
    }

    priorityQueue<int> childrenQueue(children, n);
    while (!childrenQueue.isEmpty())
    {
        cout << childrenQueue.front() << ' ';
        childrenQueue.deQueue();
    }

    return 0;
}
