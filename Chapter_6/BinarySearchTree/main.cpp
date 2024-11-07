#include "binarySearchTree.h" 

using namespace std;

int main()
{
    binarySearchTree<int> BStree;
    int a[10] = {15,30,20,80,10,5,40,60,90,2};
    int x, i;

    for (i = 0; i < 10; i++)
        BStree.insert(a[i]); 
    BStree.levelTravese();

    BStree.remove(a[9]); //删除叶子结点
    BStree.levelTravese();

    BStree.remove(a[6]); //删除有一个孩子的结点
    BStree. levelTravese();

    BStree.remove(a[0]); //删除有两个孩子的结点
    BStree.levelTravese();

    cout << "x: ";
    cin >> x;
    if (BStree.search(x)) 
        cout << x << " is found" << endl;
    else
        cout << x << " is not found" << endl;

    return 0;
}