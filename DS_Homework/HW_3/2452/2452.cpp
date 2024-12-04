#include <iostream>

template <typename T>
int partition(T A[], int low, int high)
{
    T pivot = A[low]; // 随机选择一个点作为分界，不妨选第一个。
    while (low < high)
    {
        while (low < high && pivot <= A[high])
            --high;
        A[low] = A[high];
        while (low < high && A[low] <= pivot)
            ++low;
        A[high] = A[low];
    }
    // 最后结束时，low和high都被更新到分界点的位置，那么将pivot的值放入分界点处即可。
    A[low] = pivot;
    return low;
}

template <typename T>
void quickSort(T A[], int low, int high)
{
    if (low < high)
    {
        int pivot = partition(A, low, high);
        quickSort(A, low, pivot - 1);
        quickSort(A, pivot + 1, high);
    }
}

template <typename T>
void quickSort(T A[], int len)
{
    quickSort(A, 0, len - 1);
}

int main()
{
    int data[7];
    for (int i = 0; i < 7; i++) {
        std::cin >> data[i];
    }
    int cnt;
    std::cin >> cnt;
    quickSort(data, 7);
    std::cout << data[7 - cnt];
    return 0;
}