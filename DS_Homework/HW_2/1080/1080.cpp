#include <iostream>
#include <stack>
#include <string>

using namespace std;

int calcPost(string postStr)
{
    stack<int> s ;

    int i = 0;
    int op, op1, op2;
    while (postStr[i] != '@')
    {
        if ((postStr[i] >= '0') && (postStr[i] <= '9'))
        {
            for (int j = 1; ;j++)
            {
                if (postStr[i+j] == '.')
                {
                    string tmp = postStr.substr(i, j);
                    s.push(stoi(tmp));
                    i += (j+1);
                    break;
                }
            }
        }

        else
        {
            op2 = s.top();
            s.pop();
            op1 = s.top();
            s.pop();
        
            switch (postStr[i])
            {
                case '+':
                    op = op1 + op2;
                    break;
                
                case '-':
                    op = op1 - op2;
                    break;

                case '*':
                    op = op1 * op2;
                    break;

                case '/':
                    op = op1 / op2;
                    break;
            }

            s.push(op);
            i++;
        }
    }

    return s.top();
}

int main()
{
    string postStr;
    cin >> postStr;

    cout << calcPost(postStr);

    return 0;
}