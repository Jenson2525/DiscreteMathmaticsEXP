#pragma once
#include <iostream>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <stack>
#include "transform.h"
using namespace std;
short int IsTrue[128]; //存储为真的真值指派
bool getTrue[128][7]; //存储所有的真值指派
int loc;  //表示第几个真值指派类型
bool state[27]; //表示命题变元对应的真值

void set_getTrue()
{
    for(int i = 0; i < 128; i++)
    {
        for(int j = 0; j < 7; j++)
        {
            getTrue[i][j] = 0;
        }
    }
}
//求后缀表达式的值
void valueOfExpress(int nn, express exp)
{
    int flag = exp.checkExpression();
    //表达式非法，则退出
    if(flag == false)
    {
        cout << "ERROR::ILLEGAL EXPRESSION" << endl;
    }
    else
    {
        stack<int> saveValue;
        int i = 0, j = 0;
        int n1 = 0, n2 = 0;
        string postfix = exp.getPostfix();
        int lenPostfix = postfix.length();
        for(int k = 0; k < nn; k++)
        {
            cout << ' ' << getTrue[loc][k] << ' ';
        }
        while(i <= lenPostfix)
        {
            //如果是操作数，则直接压入栈中
            if(postfix[i] >= 65 && postfix[i] <= 90)
            {
                int temp = 0;
                temp = getTrue[loc][postfix[i] - 65];
                i++;
                saveValue.push(temp);
            }
            //非操作，弹出栈顶元素并运算
            else if(postfix[i] == '!')
            {
                n1 = saveValue.top();
                saveValue.pop();
                n1 = 1 - n1;
                saveValue.push(n1);
            }
        }
    }
    
}
