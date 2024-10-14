#include <iostream> 
#include "seqQueue.h"

using namespace std;

int main()
{
    seqQueue<int> que; 
    int i, x;

    for(i = 0; i < 15; i++)
        que.enQueue(i);

    while(!que.isEmpty())
    {
        x = que.front();
        que.deQueue(); 
        cout << x << ""; 
    }
    cout << endl;
    
    return 0;
}