#include <iostream>

using namespace std;

bool check(int row[])
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = i+1; j < 9; j++)
        {
            if (row[j] == row[i])
                return false;
        }
    }
    return true;
}

int main()
{
    int n;
    cin >> n;

    bool flag[n];

    for (int i = 0; i < n; i++) //检查行
    {
        flag[i] = true;

        int matrix[9][9];
        for (int j = 0; j < 9; j++)
        {
            int row[9];
            for (int k = 0; k < 9; k++)
            {
                cin >> matrix[j][k];
                row[k] = matrix[j][k];
            }
            if ((flag[i]) && !check(row)) 
            {
                flag[i] = false;
            }
        }      
        if (!flag[i])
        {
            continue;
        } 
        
        for (int j = 0; j < 9; j++) //检查列
        {
            int col[9];
            for (int k = 0; k < 9; k++)
            {
                col[k] = matrix[k][j];
            }
            if (!check(col)) 
            {
                flag[i] = false;
                break;
            } 
        }
        if (!flag[i])
        {
            continue;
        } 

        for (int j = 0; j < 9; j += 3) //检查方块
        {
            int square[9];
            for (int k = 0; k < 9; k += 3)
            {
                square[0] = matrix[j][k];
                square[1] = matrix[j][k+1];
                square[2] = matrix[j][k+2];
                square[3] = matrix[j+1][k];
                square[4] = matrix[j+1][k+1];
                square[5] = matrix[j+1][k+2];
                square[6] = matrix[j+2][k];
                square[7] = matrix[j+2][k+1];
                square[8] = matrix[j+2][k+2];
            }
            if (!check(square)) 
            {
                flag[i] = false;
                break;
            } 
        }        
    }

    for (int i = 0; i < n; i++)
    {
        if (flag[i]) 
            cout << "Right" << endl;
        else
            cout << "Wrong" << endl;
    }

    return 0;
}
// 1
// 5 8 1 4 9 3 7 6 2
// 9 6 3 7 1 2 5 8 4
// 2 7 4 8 6 5 9 3 1
// 1 2 9 5 4 6 3 7 8
// 4 3 6 1 8 7 2 9 5
// 7 5 8 3 2 9 1 4 6
// 8 9 2 6 7 1 4 5 3
// 6 1 5 9 3 4 8 2 7
// 3 4 7 2 5 8 6 1 9