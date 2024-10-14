// 计算表达式的值

#include <iostream>
#include "linkStack.h"

using namespace std;

/*
中缀式转后缀式算法：
1.对一个中缀表达式，从左至右顺序读入各操作数、运算符。
2.当读入的是操作数时，直接输出。
3.当读入的符号是开括号，直接进栈。
4.当读入的符号是闭括号，反复进行栈顶元素出栈、输出，直到弹栈的是开括号。
5.当读入的是操作符时，如果栈顶操作符的优先级更高，反复弹栈、输出直到栈顶元素优先级低于读入操作符的优先级，读入操作符压栈；如果栈顶操作符的优先级低，读入的运算符进栈。
*/
void inToSufForm(char *inStr, char *sufStr) //inStr中缀，sufStr后缀
{  
    linkStack<char> s; //用字符栈         
    int i,j;   
    char topCh;
   
    s.push('#'); //铺垫一个底垫               
    i = 0;
    j = 0;

    while (inStr[i] != '\0')
    {      
        if ((inStr[i] >= '0') && (inStr[i] <= '9')) //读入的是操作数时，直接输出
            sufStr[j++] = inStr[i++];

        else 
        {   
            switch (inStr[i])
            {   
                case '(': //读入的符号是开括号，直接进栈
                    s.push('('); 
                    break; //优先级最高，直接入栈

                case ')': //读入的符号是闭括号
                    //弹栈，弹出元素进入后缀式，直到弹出一个左括号
                    topCh = s.top(); 
                    s.pop();

                    while (topCh != '(')
                    {   
                        sufStr[j++] = topCh;
                        topCh = s.top(); 
                        s.pop();
                    } //')'字符不入栈
                    break;
                                
                case '*': 
                case '/':   
                    topCh = s.top();

                    while ((topCh == '*') || (topCh == '/'))
                    //*、/为左结合，故后来者优先级低，需先弹出栈顶优先级较高的*或/
                    {  
                        s.pop();
                        sufStr[j++] = topCh;
                        topCh = s.top();
                    }
                    s.push(inStr[i]); //再将*或/入栈 
                    break;
                
                case '+':
                case '-':   
                    topCh = s.top();
                    
                    while ((topCh != '(') && (topCh != '#'))
                    //只有左括号和底垫优先级比+、-低，其余的需先弹出
                    {   
                        s.pop();   
                        sufStr[j++] = topCh;   
                        topCh = s.top();     
                    }
                    s.push(inStr[i]); //再将+或-入栈
                    break;
            } //switch
            i++;
        } //else
    } //while

    //将栈中还没有弹出的操作符弹空
    topCh = s.top();
    while (topCh != '#')
    {   
        sufStr[j++] = topCh;
        s.pop();
        topCh = s.top();
    }

    sufStr[j] = '\0'; //后缀字符串加结束符'\0'
}

/*
计算后缀式：
1.声明一个操作数栈，依次读入后缀式中的字符。
2.若读到的是操作数，将其进栈；
3.若读到的是运算符，将栈顶的两个操作数出栈。后弹出的操作数为被操作数，先弹出的为操作数。将出栈的两个操作数完成运算符所规定的运算后将结果进栈。
4.继续读入后缀式中的字符，如上处理，最后直到后缀式中所有字符读入完毕。
5.当完成以上操作后，栈中只剩一个操作数，弹出该操作数，它就是表达式的计算结果。
*/
int calcPost(char *sufStr)
{   
    int op1, op2, op;   
    int tmp, i;   
    linkStack<int> s;
    i = 0;

    while (sufStr[i] != '\0')
    {   
        if ((sufStr[i] >= '0') && (sufStr[i] <= '9')) //数字转为整数后进栈
        {  
            tmp = sufStr[i] - '0'; //数字转为整数
            s.push(tmp);
        }

        else
        {   
            op2 = s.top(); //栈顶整数出栈
            s.pop();      
            op1 = s.top(); 
            s.pop();

            switch (sufStr[i])
            {  
                case '*': 
                    op = op1*op2; 
                    break; //如果是运算符为'*',则做*运算
                case '/': 
                    op = op1/op2; 
                    break;
                case '+': 
                    op = op1+op2; 
                    break;
                case '-':  
                    op = op1-op2; 
                    break;      
            };
            s.push(op); //每一步计算结果进栈
        }   
        i++;
    }

    op = s.top(); 
    s.pop();

    return op;        
}

int main()
{
    char inStr[80];
    char sufStr[80];
    int result;

    cout << "Input the expression in infix form:";
    cin >> inStr;

    inToSufForm(inStr, sufStr); //获得表达式的后缀式
    result = calcPost(sufStr); //计算表达式的值

    cout << "Output the expression in suffix form:";
    cout << sufStr << endl; //在屏幕上输出后缀式

    cout << "The result of the expression is:" << result << endl; //输出表达式结果
    
    return 0;
}
