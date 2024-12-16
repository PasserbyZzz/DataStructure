#ifndef ADJACENTTABLEGRAPH_H_INCLUDED
#define ADJACENTTABLEGRAPH_H_INCLUDED

#include <iostream>
#include <seqlist.h>
#include <seqQueue.h>

using namespace std;

#define DefaultNumVertex 20

class outOfBound{};

template <class edgeType>
struct edgeNode
{  
    int dest;
    edgeType weight;
    edgeNode *link;
};

template <class verType, class edgeType>
struct verNode
{  
    verType data;
    edgeNode<edgeType> *adj;
};

template <class verType, class edgeType>
class Graph
{
    private:
        bool directed;      //有向图为1，无向图为0
        int verts, edges;     //图的实际顶点数和实际边数
        int maxVertex;      //图顶点的最大可能数量
        verNode<verType,edgeType> *verList;   // 保存顶点数据的一维数组
        void DFS(int start, bool visited[]) const;
    public:    
        //初始化图结构g，direct为是否有向图标志，e为无边数据
        Graph(bool direct);
        ~Graph();
        int numberOfVertex()const{ return verts; }; // 返回图当前顶点数
        int numberOfEdge()const{ return edges; }; // 返回图当前边数
        int getVertex(verType vertex)const; //返回顶点为vertex值的元素在顶点表中的下标
        bool existEdge(verType vertex1,verType vertex2)const; //判断某两个顶点间是否有边      
        int getFirstNeighbor(verType vertex) const;
        //返回顶点vertex1的相对vertex2的下一个邻接点，如无下一个邻接点返回-1
        int getNextNeighbor(verType vertex1, verType vertex2)const;
        void disp() const; //显示邻接矩阵的值
        void insertVertex(verType vertex); //插入顶点
        void insertEdge(verType vertex1, verType vertex2, edgeType edge); //插入边
        void removeVertex(verType vertex);  //删除顶点
        void removeEdge(verType vertex1, verType vertex2); //删除边
        //返回顶点vertex的第一个邻接点,如果无邻接点返回-1
        void DFS() const;
        void BFS() const;
        bool connected() const;
};

//初始化图结构g，direct为是否有向图标志
template <class verType, class edgeType>
Graph<verType, edgeType>::Graph(bool direct)
{   
    int i;
    //初始化属性
    directed = direct;   
    verts = 0;    
    edges = 0;     
    maxVertex = DefaultNumVertex;

    //为存顶点的一维数组创建空间
    verList = new verNode<verType,edgeType> [maxVertex];
    for (i = 0; i < maxVertex; i++)
        verList[i].adj = nullptr;
}

template <class verType, class edgeType>
Graph<verType, edgeType>::~Graph()
{   
    int i;    
    edgeNode<edgeType> *p;

    for (i = 0; i < verts; i++) //释放所有边表中的结点
    {   
        while (verList[i].adj)
        { 
            p = verList[i].adj;    
            verList[i].adj = p->link;    
            delete p;      
        }
    }

    delete []verList;
}

template <class verType, class edgeType>
void Graph<verType, edgeType>::insertEdge(verType vertex1, verType vertex2, edgeType edge) //插入边
{  
    int i, j;
    edgeNode<edgeType> *tmp;

    //找到vertex1和vertex2的下标
    for (i = 0; i < verts; i++)     
        if (verList[i].data == vertex1)    
            break;
    for (j = 0; j < verts; j++)     
        if (verList[j].data == vertex2)    
            break;
    //无此顶点
    if ((i == verts) || (j == verts))   
        return;

    //在i下标引导的单链表中插入一个边结点
    tmp = new edgeNode<edgeType>;      
    tmp->dest = j;      
    tmp->weight = edge;
    tmp->link = verList[i].adj;     
    verList[i].adj = tmp;
    edges++;
    if (!directed) //如果是无向图，矩阵中关于主对角线的对称点也要设置
    {  
        tmp = new edgeNode<edgeType>;           
        tmp->dest = i;
        tmp->weight = edge;           
        tmp->link = verList[j].adj;
        verList[j].adj = tmp;
    }
}

template <class verType, class edgeType>
void Graph<verType, edgeType>::removeVertex(verType vertex)  //删除顶点
{  
    int i, j;     
    int count = 0;     
    edgeNode<edgeType> *p, *q;

    //找到该顶点在顶点表中的下标
    for (i = 0; i < verts; i++)     
        if (verList[i].data == vertex)   
            break;

    if (i == verts) 
        return; //该顶点不在顶点表中

    //删除下标为i的顶点引导的单链表中所有结点并计数删除的边
    p = verList[i].adj;
    while (p)  
    {    
        count++;   
        verList[i].adj = p->link;   
        delete p;   
        p = verList[i].adj;  
    }

    //检查所有单链表，凡是dest是i的都删除
    for (j = 0; j < verts; j++)
    {  
        p = verList[j].adj; 
        q = NULL;
        while (p)    
        {  
            if (p->dest == i) 
                break;  

            q = p;  
            p = p->link;   
        }

        if (!p) 
            continue;
        if (!q)   
            verList[j].adj = p->link;
        else  
            q->link = p->link;

        delete p;
        count++;
    }

    //检查所有单链表，凡是dest>i的都删减一
    for (j = 0; j < verts; j++)
    {  
        p = verList[j].adj;
        while (p)   
        {   
            if (p->dest > i)   
                p->dest--;
            p = p->link;
        }
    }

    if (directed)    
        edges -= count;
    else //无向图，减少count的一半
        edges -= count/2;     

    //在顶点表中删除顶点
    for (j = i; j < verts-1; j++)
        verList[j] = verList[j+1];
    verts--;
}

template <class verType, class edgeType>
void Graph<verType, edgeType>::DFS() const //深度优先遍历
// 时间复杂度O(n+e)
{   
    bool *visited;     
    int i;

    visited = new bool[verts];   
    if (!visited) 
        throw illegalSize();

    for (i = 0; i < verts; i++) 
        visited[i] = false;

    for (i = 0; i < verts; i++)
    {  
        if (!visited[i]) 
            DFS(i, visited);
        cout << endl;     
    }       
}

template <class verType, class edgeType>
void Graph<verType, edgeType>::DFS(int start, bool visited[]) const
{  
    edgeNode<edgeType> *p;

    cout << verList[start].data << '\t';     
    visited[start] = true;    
    p = verList[start].adj;

    while (p)
    {  
        if (!visited[p->dest]) 
            DFS(p->dest, visited);
        p = p->link;
    }
} 

template <class verType, class edgeType>
void Graph<verType, edgeType>::DFS() const
// 深度优先遍历的非递归算法
{  
    seqStack<int> s;
    edgeNode<edgeType> *p;   
    bool *visited;      
    int i, start;

    //为visited创建动态数组空间，并置初始访问标志为false。
    visited = new bool[verts];   
    if (!visited) 
        throw illegalSize();
    for (i = 0; i < verts; i++)   
        visited[i] = false;
    //逐一找到未被访问过顶点，做深度优先遍历
	for (i = 0; i < verts; i++)
	{  
        if (visited[i]) 
            continue;
	    s.push(i);
	    while (!s.isEmpty())
	    {  
            start = s.top();
            s.pop();
	        if (visited[start]) 
                continue;
	        cout << verList[start].data << '\t';
	        visited[start] = true;

            p = verList[start].adj;
	        while (p)
	        {    
                if (!visited[p->dest])    
                s.push(p->dest);
                p = p->link;
	        }
        }
        cout<<'\n';
    }
}

template <class verType, class edgeType>
void Graph<verType, edgeType>::BFS() const //广度优先遍历
// 时间复杂度O(n+e)
{   
    seqQueue<int> q;      
    edgeNode<edgeType> *p;
    bool *visited;   
    int i, start;

    //为visited创建动态数组空间，并置初始访问标志为false。
    visited = new bool[verts];
    if (!visited) 
        throw illegalSize();
    for (i = 0; i < verts; i++) 
        visited[i] = false;

    //逐一找到未被访问过顶点，
    //做广度优先遍历
    for (i = 0; i < verts; i++)
    {    
        if (visited[i]) 
            continue;

        q.enQueue(i);
        while (!q.isEmpty())
        {   
            start = q.front(); 
            q.deQueue();

            if (visited[start]) 
                continue;

            cout << verList[start].data << '\t';
            visited[start] = true;
 
     	    p = verList[start].adj;
	        while (p)
	        {   
                if (!visited[p->dest])
                    q.enQueue(p->dest);
                p = p->link;
	        }
	    }
	    cout << '\n';
	}     
}

template <class verType, class edgeType>
bool Graph<verType, edgeType>::connected() const //无向图是否连通
{   
    seqQueue<int> q;     	
    edgeNode<edgeType> *p;
    bool *visited;     
    int i, start, count=0; //count为计数器

    // 为visited创建动态数组空间，并置初始访问标志为false
    visited = new bool[verts];
    if (!visited) 
        throw illegalSize();
    for (i = 0; i < verts; i++) 
        visited[i] = false;

    //逐一找到未被访问过顶点，做广度优先遍历
    for (i = 0; i < verts; i++)
    {    
        if (visited[i]) 
            continue;
        q.enQueue(i);  
        count++;  

       while (!q.isEmpty())
       {   
            start = q.front(); 
            q.deQueue();
            if (visited[start]) 
                continue;
            
            cout << verList[start].data << '\t';
            visited[start] = true;

            p = verList[start].adj;
            while (p)
            {    
                if (!visited[p->dest])
                    q.enQueue(p->dest);
                p = p->link;
            }	    
        }
        cout << '\n';
    }

    if (count == 1) 
        return true;
    return false;     
}

#endif