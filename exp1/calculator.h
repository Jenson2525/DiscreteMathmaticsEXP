//五种联结词优先级 ! * + @ $ 分别代表否定 合取 析取 单条件 双条件
//规定符号代换规则为 ┐:!  ∧:*  ∨:+  ->:@  <->:$
#pragma once
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <string>
#include <stack>
using namespace std;

class calculator
{
    private:
        char infix[32];  //中缀表达式
        char postfix[32];  //后缀表达式
    public:
        //构造函数
        calculator(char *exp)
        {
            strcpy(this->infix, exp);
            for(int i = 0; i < 32; i++)
            {
                postfix[i] = '\0';
            }  
        }
        //析构函数
        ~calculator()
        {
            delete[] infix;
            delete[] postfix;
        }
        //获取中缀表达式和后缀表达式
        void getInfix()
        {
            cout << infix << endl;
        }
        void getPostfix()
        {
            cout << postfix << endl;
        }
        //前缀表达式转后缀表达式
        void transform()
        {
            stack<char> save;  //构造一个栈
            int i = 0, j = 0;
            while(this->infix[i] != '\0')
            {
                //读取操作数
                if(this->infix[i] >= 65 && this->infix[i] <= 90)
                {
                    while(this->infix[i] >= 65 && this->infix[i] <= 90)
                    {
                        postfix[j] = this->infix[i];
                        j++; 
                        i++;
                    }
                }
                //读取操作符
                else
                {
                    if(this->infix[i] == '(' || this->infix[i] == ')')
                    {
                        //如果遇到'('，直接压入栈中
                        if(this->infix[i] == '(')
                        {
                            save.push(this->infix[i]);
                        }
                        //如果遇到一个')'，那么就将栈元素弹出并加到后缀表达式尾端，但左右括号并不输出
                        else if(this->infix[i] == ')')
                        {
                            //如果栈为空，则说明表达式错误
                            if(save.empty())
                            {
                                cout << "ERROR::WRONG EXPRESSION" << endl;
                                exit(0);
                            }
                            //如果不为空，则依次读取栈顶元素，直至遇到'('
                            while(!save.empty() && save.top() != '(')
                            {
                                this->postfix[j] = save.top();
                                j++;
                            }
                            //弹出栈顶元素
                            if(save.top() == '(')
                            {
                                save.pop();
                            }
                        }
                    }
                    else
                    {
                        if(save.empty())
                        {
                            save.push(this->infix[i]);
                        }
                        else
                        {
                            if(this->infix[i] == '!')
                            {
                                char temp = save.top();
                                while(temp == '!' && temp != '(' && !save.empty())
                                {
                                    this->postfix[j] = save.top();
                                    save.pop();
                                    temp = save.top();
                                    j++;
                                }
                                save.push(this->infix[i]);
                            }
                            else if(this->infix[i] == '*')
                            {
                                char temp = save.top();
                                while(temp == '+' && temp != '(' && !save.empty())
                                {
                                    this->postfix[j] = save.top();
                                    save.pop();
                                    temp = save.top();
                                    j++;
                                }
                                save.push(this->infix[i]);
                            }
                            else if(this->infix[i] == '+')
                            {
                                char temp = save.top();
                                while((temp == '*' || temp == '!') && !save.empty())
                                {
                                    this->postfix[j] = save.top();
                                    save.pop();
                                    temp = save.top();
                                    j++;
                                }
                                save.push(this->infix[i]);
                            }
                            else if(this->infix[i] == '@')
                            {
                                char temp = save.top();
                                while((temp == '*' || temp == '!' || temp == '+') && !save.empty())
                                {
                                    this->postfix[j] = save.top();
                                    save.pop();
                                    temp = save.top();
                                    j++;
                                }
                                save.push(this->infix[i]);
                            }
                            else if(this->infix[i] == '$')
                            {
                                char temp = save.top();
                                while((temp == '*' || temp == '!' || temp == '+' || temp == '@') && !save.empty())
                                {
                                    this->postfix[j] = save.top();
                                    save.pop();
                                    temp = save.top();
                                    j++;
                                }
                                save.push(this->infix[i]);
                            }
                        }
                    }
                    i++;
                }
            }
            //后缀表达式
            while(!save.empty())
            {
                postfix[j] = save.top();
                save.pop();
                j++;
            }
            postfix[j] = '\0';
        }
};
