// 抽象，纯数学题……

#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<int> priority;
    int cnt_0=0, cnt_1=0, cnt_2=0;
    for (int i = 0; i < n; i++)
    {
        int p;
        cin >> p;
        priority.push_back(p);

        if (p == 0) 
            cnt_0++;
        else if (p == 1) 
            cnt_1++;
        else 
            cnt_2++;
    }

    int len = n;
    int misplace_1_in_0=0, misplace_2_in_0=0;
    int misplace_0_in_1=0, misplace_2_in_1=0;
    int misplace_0_in_2=0, misplace_1_in_2=0;
    for (int i = 0; i < n; i++)
    {
        if (i < cnt_0)
        {
            if (priority[i] == 1) 
                misplace_1_in_0++;
            else if (priority[i] == 2)
                misplace_2_in_0++; 
            else
                len--;             
        }
        else if (i < cnt_0 + cnt_1)
        {
            if (priority[i] == 0) 
                misplace_0_in_1++;
            else if (priority[i] == 2)
                misplace_2_in_1++;  
            else
                len--;  
        }
        else
        {
            if (priority[i] == 0) 
                misplace_0_in_2++;
            else if (priority[i] == 1)
                misplace_1_in_2++; 
            else
                len--; 
        }
    }

    int ans = 0;
    int swap_0_1 = min(misplace_1_in_0, misplace_0_in_1);
    ans += swap_0_1;
    int swap_0_2 = min(misplace_2_in_0, misplace_0_in_2);
    ans += swap_0_2;
    int swap_1_2 = min(misplace_1_in_2, misplace_2_in_1);
    ans += swap_1_2;

    ans += 2 * (len - 2 * swap_0_1 - 2 * swap_0_2 - 2 * swap_1_2) / 3;

    cout << ans;

    return 0;
}