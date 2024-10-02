#include <iostream> 
#define INITSIZE 100 //定义常量
using namespace std;

class illegalSize{};
class outOfBound{};

template <class elemType>
class seqList
{   private:
        elemType *elem; // 顺序表存储数组，存放实际的数据元素
        int len; // 顺序表中的元素个数，亦称表的长度
        int maxSize; // 顺序表最大可能的长度
        void doubleSpace(); // 工具函数
    public:
        seqList(int size = INITSIZE); //初始化顺序表
        //表为空返回 true,否则返回 false
        bool isEmpty() const {return(len == 0);}
        //表为满返回 true,否则返回 false
        bool isFull() const {return(len == maxSize);}
        int length() const {return len;} //表的长度，即实际存储元素的个数
        elemType get(int i) const; //返回第i个元素的值
        //返回值等于e的元素的序号，无则返回0
        int find(const elemType &e) const;

        //在第i个位置上插入新的元素(值为e)
        //使原来的第i个元素成为第i+1个元素
        void insert(int i, const elemType &e); 
        //若第1个元素存在，删除井将其值放入e指向的空间
        void remove(int i, elemType &e);

        void clear() {len = 0;}; //清除顺序表，使其成为空表
        ~seqList() {delete []elem;}; //释放表占用的动态数组
};

template <class elemType>
seqList<elemType>::seqList(int size) //初始化顺序表
{
    elem = new elemType[size]; //申请动态数组
    if(!elem) throw illegalSize();
    maxSize = size - 1; //0下标位置不放元素，用于查找时做哨兵位
    len=0;
}

template <class elemType>
void seqList<elemType>::doubleSpace()
{
    int i;
    elemType *tmp = new elemType[2*maxSize];
    if(!tmp) throw illegalSize();

    for (i = 1; i <= len; i++)
        tmp[i] = elem[i];

    delete []elem;
    elem = tmp;
    maxSize = 2*maxSize - 1;
}

template <class elemType> 
elemType seqList<elemType>::get(int i)const// 返回第i个元素的值
{
    if ((i < 1) || (i > len)) throw outOfBound();
    return elem[i];
}

template <class elemType> //返回值等于e的元素的序号，无则返回0
int seqList<elemType>::find(const elemType &e) const //时间复杂度为O(n)
{
    int i;
    elem[0] = e;  //哨兵位先置为待查元素
    // 从后往前进行查找
    // 总能找到，不会越界
    for (i = len; elem[i] != e; i--); 
    return i;
}

template <class elemType>
void seqList<elemType>::insert (int i, const elemType &e ) //时间复杂度为O(n)
{  int k;
    if ((i < 1) || (i > len + 1)) return; //插入位置越界
    if (len == maxSize) doubleSpace(); //空间满了，无法插入元素

    for (k = len + 1; k > i; k--) //最后一个元素先后移
        elem[k] = elem[k - 1];
    elem[i] = e;
    len++; //更新
}

template <class elemType>
void seqList<elemType>::remove (int i, elemType &e )
{   int k;
    if ((i < 1) || (i > len)) return;
    e = elem[i]; //保存数据

    for (k = i; k < len; k++) //从前面的元素开始前移，然后依次后推
        elem[k] = elem[k+1];
    len--; //更新
} 

