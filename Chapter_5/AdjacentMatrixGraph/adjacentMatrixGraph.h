#ifndef ADJACENTMATRIXGRAPH_H_INCLUDED
#define ADJACENTMATRIXGRAPH_H_INCLUDED

#include <iostream>
#include <seqStack.h>

using namespace std; 

#define DefaultNumVertex 20

class outOfBound{};

// 求关键路径的算法实现
// 保存边信息
template <class edgeType>
struct keyEdge
{   
    int u, v;       
    edgeType weight;
    edgeType early, last;
};

// 求单源最短路径Dijikstra算法实现
template <class edgeType>
struct DijkstraNode
{
    int source; //当前最短路径上前一顶点
    int dist;   //当前最短路径距离
    bool selected; //顶点是否已经在S中的标志
};
    
template <class verType, class edgeType>
class Graph
{  
    private:
        int verts, edges;   //图的实际顶点数和实际边数
        int maxVertex;      //图顶点的最大可能数量
        verType *verList;   // 保存顶点数据的一维数组
        edgeType **edgeMatrix; //保存邻接矩阵内容的二维数组
        edgeType noEdge;       //无边的标志
        bool directed;          //有向图为1，无向图为0
    public:
        //初始化图结构g，direct为是否有向图标志，e为无边数据
        Graph(bool direct, edgeType e);     
        int numberOfVertex()const{ return verts; }; // 返回图当前顶点数
        int numberOfEdge()const{ return edges; }; // 返回图当前边数
        //返回顶点为vertex值的元素在顶点表中的下标
        int getVertex(verType vertex)const;  
        //判断某两个顶点间是否有边
        bool existEdge(verType vertex1,verType vertex2)const;  
        void insertVertex(verType vertex ); //插入顶点
        void insertEdge(verType vertex1, verType vertex2, edgeType edge); //插入边
        void removeVertex(verType vertex);  //删除顶点
        void removeEdge(verType vertex1, verType vertex2); //删除边
        //返回顶点vertex的第一个邻接点,如果无邻接点返回-1
        int getFirstNeighbor(verType vertex ) const;
        //返回顶点vertex1相对vertex2的下一个邻接点，如果无下一个邻接点返回-1
        int getNextNeighbor(verType vertex1, verType vertex2)const;
        void disp()const; //显示邻接矩阵的值
        void topoSort() const;
        void keyActivity(verType start, verType end) const;
        void Dijkstra(verType start) const
        ~Graph();
};

//初始化图结构g，direct为是否有向图标志，e为无边数据
template <class verType, class edgeType>
Graph<verType, edgeType>::Graph(bool direct, edgeType e)
{  
    int i, j;

    //初始化属性
    directed = direct;    
    noEdge = e;    
    verts = 0;   
    edges = 0;
    maxVertex = DefaultNumVertex;

    //为存顶点的一维数组和存边的二维数组创建空间
    verList = new verType[maxVertex];
    edgeMatrix = new edgeType*[maxVertex];
    
    //初始化图结构g，direct为是否有向图标志，e为无边数据
    for (i = 0; i < maxVertex; i++)
        edgeMatrix[i] = new edgeType[maxVertex];

    //初始化二维数组，边的个数为0
    for (i = 0; i < maxVertex; i++)
            for (j = 0; j < maxVertex; j++)
                if (i == j)   
                    edgeMatrix[i][j] = 0; //对角线元素
                else   
                    edgeMatrix[i][j] = noEdge; //无边
}

template <class verType, class edgeType>
Graph<verType, edgeType>::~Graph()
{
    int i;
    delete []verList;
    for (i = 0; i < maxVertex; i++)
        delete []edgeMatrix[i];
    delete []edgeMatrix;
}

//返回顶点为vertex值的元素在顶点表中的下标
template <class verType, class edgeType>
int Graph<verType, edgeType>::getVertex(verType vertex) const
{  
    int i;
    for (i = 0; i < verts; i++)
        if (verList[i] == vertex)
            return i;
    return -1;
}

//判断某两个顶点是否有边
template <class verType, class edgeType>
bool Graph<verType, edgeType>::
existEdge(verType vertex1,verType vertex2) const
{  
    int i, j;
    //找到vertex1和vertex2的下标
    for (i = 0; i < verts; i++)
        if (verList[i] == vertex1)
            break;
     for (j = 0; j < verts; j++)
        if (verList[j] == vertex2)
            break;
    
    if (i == verts || j == verts)   
        return false;
    if (i ==j) 
        return false;
    if (edgeMatrix[i][j] == noEdge) 
        return false;
    return true;
}

//删除顶点
template <class verType, class edgeType>
void Graph<verType, edgeType>::removeVertex(verType vertex)
//删除顶点
{  
    int i, j, k;
    //找到该顶点在顶点表中的下标
    for (i = 0; i < verts; i++)
        if (verList[i] == vertex)  
            break;
    if (i == verts) 
        return;
    //在顶点表中删除顶点
    for (j = i; j < verts-1; j++)
        verList[j] = verList[j+1];

    //计数删除顶点射出的边,边数减少
    for (j = 0; j < verts; j++)
        if ((j != i) && (edgeMatrix[i][j]!= noEdge))
            edges--;

    //如果是有向图，计数删除顶点射入的边,边数减少
    if (directed)
    {    
        for (k = 0; k < verts; k++)
            if (((k != i) && edgeMatrix[k][i] != noEdge))
                edges--;
    }
    //第i行之后所有行上移
    for (j = i; j < verts-1; j++)
    {   
        for (k = 0; k < verts; k++)
            edgeMatrix[j][k] = edgeMatrix[j+1][k];   
    }
    //第i列之后所有列前移
    for (j = i; j < verts-1; j++)
    {
        for (k = 0; k < verts; k++)
            edgeMatrix[k][j] = edgeMatrix[k][j+1];
    }

    verts--;
}

template <class verType, class edgeType>
void Graph<verType, edgeType>::topoSort() const // 拓扑排序的实现
// 时间复杂度O(n^2)；若用邻接表，O(n+e)
{   
    int *inDegree;      
    seqStack<int> s;   
    int i, j;

    //创建空间并初始化计算每个顶点的入度,
    //邻接矩阵每一列元素相加,加完入度为零的压栈
    inDegree = new int[verts];
    for (j = 0; j < verts; j++)
    {   
        inDegree[j] = 0;
        for (i = 0; i < verts; i++)
        {     
            if (( i!= j) && (edgeMatrix[i][j] != noEdge))   
                inDegree[j]++;   
        }
        if (inDegree[j]==0) 
            s.push(j);
    }
        
    //逐一处理栈中的元素
    while (!s.isEmpty())
    {   
        i = s.top(); 
        s.pop();
        cout << i << "  ";

        //将i射出的边指示的邻接点入度减一，减为零时压栈
        for (j = 0; j < verts; j++)
            if ((j != i) && (edgeMatrix[i][j] != noEdge))
            {    
                inDegree[j]--;    
                if (inDegree[j] == 0) 
                    s.push(j);
            }
    }
    cout << endl;
}

template <class verType, class edgeType>
void Graph<verType, edgeType>::keyActivity(verType start, verType end) const
// 求关键路径的算法实现，时间复杂度O(n^2)
{
    int *inDegree;
    edgeType *verEarly, *verLast; //事件-顶点的最早发生时间、最迟发生时间
    keyEdge<edgeType> *edgeEL; //记录每个活动-边的最早发生时间、最迟发生时间
    seqStack<int> s1; //s1保存入度为0的顶点
    seqStack<int> s2; //s2保存确定顶点最早发生时间的顶点顺序

    int i, j, k;    
    int u, v;   
    int intStart, intEnd;

    //创建动态数组空间
    inDegree = new int[verts];
    verEarly = new edgeType[verts];      
    verLast = new edgeType[verts];
    edgeEL = new keyEdge<edgeType>[edges];

    //找到起点和终点的下标
    intStart = intEnd = -1;
    for (i = 0; i < verts; i++)
    {   
        if (verList[i] == start)     
            intStart = i;
        if (verList[i]==end)      
            intEnd = i;
    }
    if ((intStart == -1) || (intEnd == -1)) 
        throw outOfBound();
    
    //计算每个顶点的入度，邻接矩阵每一列有边的元素个数相加
    for (j = 0; j < verts; j++)
    {   
        inDegree[j] = 0;
        for (i = 0; i < verts; i++)
        {     
            if ((i != j) && (edgeMatrix[i][j] != noEdge))
              inDegree[j]++;
        }
    }

    //初始化顶点最早发生时间，全部设为0
    for (i = 0; i < verts; i++)
    {    
        verEarly[i] = 0;      
    }

    //计算每个顶点的最早发生时间
    //初始化起点的最早发生时间
    verEarly[intStart] = 0;  
    i = intStart;  
    s2.push(i);

    //计算其他顶点的最早发生时间
    while (i != intEnd) //当终点因为入度为零压栈、出栈时，计算结束
    {   
        for (j = 0; j < verts; j++)
        {   
            if ((i != j) && (edgeMatrix[i][j] != noEdge)) // 处理i的出度
            {   
                inDegree[j]--;
                if (inDegree[j] == 0) 
                    s1.push(j); //入度为0，进栈
                if (verEarly[j] < verEarly[i] + edgeMatrix[i][j]) // 更新
                    verEarly[j] = verEarly[i] + edgeMatrix[i][j];
            }
        }
        i = s1.top(); 
        s1.pop();     
        s2.push(i); //当前确定了最早发生时间的顶点入栈，s2为逆序栈
    }
        
    //初始化顶点最迟发生时间，全部设为终点的最迟发生时间（总工期）
    for (i = 0; i < verts; i++)    
        verLast[i] = verEarly[intEnd];

    //按照计算顶点最早发生时间逆序依次计算顶点最迟发生时间
    while (!s2.isEmpty())
    {   
        j = s2.top(); 
        s2.pop();

        //修改所有射入顶点j的边的箭尾顶点的最迟发生时间
        for (i = 0; i < verts; i++)
            if ((i != j) && (edgeMatrix[i][j] != noEdge))
                if (verLast[i] > verLast[j] - edgeMatrix[i][j])
                    verLast[i] = verLast[j] - edgeMatrix[i][j];
    }
        
    //建立边信息数组
    k = 0;
    for (i = 0; i < verts; i++)
        for (j = 0; j < verts; j++)
            if ((i != j) && (edgeMatrix[i][j] != noEdge))
            {   
                edgeEL[k].u = i;    
                edgeEL[k].v = j;
                edgeEL[k].weight = edgeMatrix[i][j];     
                k++;
            }

    //将边的最早发生时间<u,v>设置为箭尾顶点u的最早发生时间
    //将边的最迟发生时间<u,v>设置为箭头顶点v的最迟发生时间-<u,v>边的权重
    for (k = 0; k < edges; k++)
    {   
        u = edgeEL[k].u;    
        v = edgeEL[k].v;
        edgeEL[k].early = verEarly[u];   
        edgeEL[k].last  = verLast[v] - edgeEL[k].weight;
    }
        
    //输出关键活动
    cout << "关键活动：" << endl;
    for (k = 0; k < edges; k++)
        if (edgeEL[k].early == edgeEL[k].last)
        {
            u = edgeEL[k].u;
            v = edgeEL[k].v;
            cout << verList[u] << "->" << verList[v] << endl;
            cout << "early: " << edgeEL[k].early << "  "
                 <<"last: " << edgeEL[k].last;
            cout << endl << endl;
        }
}

template <class verType, class edgeType>
void Graph<verType, edgeType>::Dijkstra (verType start) const
// 如果图用邻接矩阵来存储，可以看出时间复杂度为O(𝑛^2)
{
    DijkstraNode<edgeType> *DList;
    int i, j, startInt;
    int cnt; //记录集合U中顶点的个数
    int min; //选出的当前离集合最短的顶点
    int dist; 
    
    //查找起始点下标    
    for (i = 0; i < verts; i++)    
        if (verList[i] == start)   
            break;
    if (i == verts) 
        return;
  
    //创建空间并初始化DList[i]数组
    startInt = i;    
    DList = new DijkstraNode<edgeType>[verts];
    for (i = 0; i < verts; i++)       
    {  
        DList[i].source = -1;   
        DList[i].dist = noEdge;  
        DList[i].selected = false;    
    }

    //从下标为startInt的点开始
    min = startInt;
    cnt = 1;
    DList[startInt].source = startInt ;
    DList[startInt].dist = 0;
    DList[startInt].selected = true;
    
    while (cnt < verts) //包含n-1的节点结束
    {  
        //根据min顶点发出的边，判断是否修正相邻顶点的最短距离
        for (j = 0; j < verts; j++)
        {  
            if (edgeMatrix[min][j] == 0) //对角线元素 
                continue;                      
            if (DList[j].selected) //已经加入集合S 
                continue;                      
            if (edgeMatrix[min][j] == noEdge) //无边  
                continue;               
            if (DList[min].dist + edgeMatrix[min][j] < DList[j].dist) //修正相邻顶点的最短距离
            {  
                DList[j].dist = DList[min].dist+edgeMatrix[min][j];
                DList[j].source = min;
            }
        }
            
        //搜索当前距离标签最小的顶点
        min = -1;     
        dist = noEdge;
        for (i = 0; i < verts; i++)
        {  
            if (DList[i].selected) 
                continue;
            if (DList[i].dist < dist) 
            {    
                min = i; 
                dist = DList[i].dist;  
            }
        }

        //此时min一定为某个顶点的下标，如果仍然为-1表示该无相图不连通
        //将顶点min加入集合S
        cnt++;     
        DList[min].selected = true;
    } 
}

#endif