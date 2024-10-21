// 顺序循环队列类的定义及基本操作实现

#ifndef SEQQUEUE_H_INCLUDED
#define SEQQUEUE_H_INCLUDED

class queueIllegalSize{};
class queueOutOfBound{};

template <class elemType>
class seqQueue
{    
    private:
        elemType *array;
        int maxSize;
        int Front, Rear;
        void doubleSpace(); //扩展队队列元素的存储空间为原来的2倍
    public:
        seqQueue(int size=10); //初始化队列元素的存储空间
        bool isEmpty(); //判断队空否，空返回true，否则为false
        bool isFull();  //判断队满否，满返回true，否则为false
        elemType front(); //读取队首元素的值，队首不变
        void enQueue(const elemType &x); //将x进队，成为新的队尾
        void deQueue(); //将队首元素出队
        ~seqQueue(); //释放队列元素所占据的动态数组
};

template <class elemType>
seqQueue<elemType>::seqQueue(int size) //初始化队列元素的存储空间
{
    array = new elemType[size]; //申请实际的队列存储空间

    if (!array) throw queueIllegalSize();

    maxSize = size;
    Front = Rear = 0;
}

template<class elemType>
bool seqQueue<elemType>::isEmpty() //判断队空否，空返回 true,否则为false
{
    return Front == Rear;
}

template <class elemType>
bool seqQueue<elemType>::isFull() //判断队满否，满返回 true,否则为false
{
    return (Rear+1)%maxSize == Front;
}

template <class elemType>
elemType seqQueue<elemType>::front() //读取队首元素的值，队首不变
{
    if (isEmpty()) throw queueOutOfBound(); //先判断

    return array[Front]; 
}

template <class elemType>
void seqQueue<elemType>::enQueue(const elemType &x)  //将x进队，成为新的队尾
{  
    if (isFull()) doubleSpace();

    array[Rear] = x;
    Rear = (Rear+1)%maxSize;
}

template <class elemType>
void seqQueue<elemType>::deQueue() //将队首元素出队
{  
    if (isEmpty()) throw queueOutOfBound();

    Front = (Front+1)%maxSize;
}

template <class elemType>
seqQueue<elemType>::~seqQueue() //释放队列元素所占据的动态数组
{ 
    delete []array;
}

template <class elemType>
void seqQueue<elemType>::doubleSpace() //扩展队列元素的存储空间为原来的2倍
{
    elemType* newArray;
    int i, j;

    newArray = new elemType[2*maxSize];
    if (!newArray) throw queueIllegalSize();

    for (i = 0, j = Front; j != Rear; i++, j = (j+1)%maxSize) //直接重排
        newArray[i] = array[j];

    delete []array; //释放原来的小空间

    array = newArray;
    Front = 0;
    Rear = i;
    maxSize = 2*maxSize;
}

#endif