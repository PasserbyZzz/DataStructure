// 核心而简单的算术表达式中括号匹配检测程序
// 假设只有小括号

#include <iostream>
#include "linkStack.h"

using namespace std;

int main()
{   
    char str[20];
    linkStack<char> s;  //建立一个字符栈
    char ch;
    int i;

    cout << "Input the string: ";
    cin.getline(str, 20, '\n'); //只能输入19个字母，最后一项为\0
    cout << "str: " << str <<endl;

    i = 0;    
    ch = str[i++];
    while (ch != '\0')
    {   
        switch(ch)
        {  
            case '(': //如果读入的是开括号，将其进栈
                s.push(ch);    
                break;
            case ')':      
                if (s.isEmpty())
                {    
                    //读入一个闭括号，栈却空，找不到匹配的开括号
                    cout << "An opening bracket '(' is expected!\n";
                    return 1;
                }
                else //如果读入的是闭括号但栈不空，将栈中的开括号出栈
                    s.pop(); 
                break;
        }
        ch = str[i++]; //继续从文件中读入下一个符号
    }

    if (!s.isEmpty()) //式子读入结束，发现栈中还有多余的开括号
       	cout << "A closing bracket ')' is expected!\n";
    else
        cout << "Nothing is wrong!\n";

   return 0;
}


