#include <iostream>
#include <stack>

using namespace std;

bool isValid(int seq[], int n)
{
    stack<int> tmp;

    int j = 0; //检查seq的j号位
    int current = 1; //当前要入栈的数，从1开始

    while (j < n)
    {
        while (tmp.empty() || tmp.top() < seq[j])
        {
            tmp.push(current);
            current++;
        }
    
        if (tmp.top() != seq[j]) 
            return false;

        tmp.pop();
        j++;
    }

    return true;
}

int main() 
{
    int T;
    cin >> T;
    bool result[T];

    for (int i = 0; i < T; i++)
    {
        int n;
        cin >> n;

        int seq[n];
        for (int j = 0; j < n; j++)
        {
            int num;
            cin >> num;
            seq[j] = num;
        }

        result[i] = isValid(seq, n);
    } 

    for (int i = 0; i < T; i++)
    {
        if (result[i])
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    }

    return 0;
}