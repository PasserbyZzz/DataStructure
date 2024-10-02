#include <iostream>
using namespace std;

template <class elemType>
class arr {
private:
    elemType *a;
    int maxSize, count;

public:
    arr(int size); 

    // 参数前加 const，保护参数在函数执行中不被修改
    void append(const elemType &x);

    // 参数表后加 const，保护调用函数的对象的值不被修改
    void find(const elemType &x) const;

    ~arr() {
        delete[] a;
    }
};

template <class elemType>
arr<elemType>::arr(int size) {
    a = new elemType[size];
    maxSize = size;
    count = 0;
}

template <class elemType>
void arr<elemType>::append(const elemType &x) {
    if (count == maxSize) return;
    a[count] = x;
    count++;
}

template <class elemType>
void arr<elemType>::find(const elemType &x) const {
    int i;
    for (i = 0; i < count; i++) {
        if (a[i] == x) break;
    }
    if (i == count)
        cout << x << " doesn't exist in the array!" << endl;
    else
        cout << x << " exists in the array!" << endl;
}

int main() {
    arr<int> obj1(10);       // <int>使类模板实例化
    const arr<int> obj2(20); // const <int>对象 只能调用带const的成员函数

    int a;
    const int b = 100;

    // 将 1, 3, 5... 等奇数放入 obj1
    for (int i = 0; i < 10; i++) {
        obj1.append(2 * i + 1);
    }

    cout << "a = ";
    cin >> a;

    cout << "In obj1: ";
    obj1.find(a);

    cout << "In obj1: ";
    obj1.find(b);

    cout << "In obj2: ";
    obj2.find(a);

    return 0;
}
