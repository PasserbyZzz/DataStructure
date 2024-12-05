#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

void inToSufForm(string inStr)
{
    stack<char> s;
    s.push('#');
    char topCh;

    int i = 0;
    while (inStr[i] != '@')
    {
        // 当读入的是操作数时，直接输出
        if ((inStr[i] >= '0') && (inStr[i] <= '9'))
        {
            for (int j = 1; ;j++)
            {
                if (inStr[i+j] == '.')
                {
                    string tmp = inStr.substr(i, j+1);
                    cout << tmp;
                    i += (j+1);
                    break;
                }
            }
        }

        // 当读入的符号是开括号，直接进栈
        else
        {
            switch (inStr[i])
            {
                case '(':
                    s.push('(');
                    break;

                case ')':
                    topCh = s.top(); 
                    s.pop();

                    while (topCh != '(')
                    {   
                        cout << topCh;
                        topCh = s.top(); 
                        s.pop();
                    } 
                    break;

                case '*': 
                case '/':   
                    topCh = s.top();

                    while ((topCh == '*') || (topCh == '/'))
                    {  
                        s.pop();
                        cout << topCh;
                        topCh = s.top();
                    }
                    s.push(inStr[i]);
                    break;

                case '+':
                case '-':   
                    topCh = s.top();
                    
                    while ((topCh != '(') && (topCh != '#'))
                    {   
                        s.pop();   
                        cout << topCh;   
                        topCh = s.top();     
                    }
                    s.push(inStr[i]); //再将+或-入栈
                    break;
            }
            i++;
        }
    }

    topCh = s.top();
    while (topCh != '#')
    {   
        cout << topCh;
        s.pop();
        topCh = s.top();
    }

    cout << '@';
}

int main()
{
    string inStr;
    cin >> inStr;

    inToSufForm(inStr);

    return 0;
}