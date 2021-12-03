#include<string>
#include<iostream>
#include<vector>
#include<stack>

/*
计算中缀表达式的字符串数值
*/

int caculate(std::string);
int string_to_int(std::string s);
std::string change(std::string s);


int main() 
{
    std::string ss = "1*3+2*3";
    int res = caculate(ss);
    std::cout << res << std::endl;


    std::string s1 = "1+3*5-4*(7-5)";
    std::cout << change(s1) << std::endl;
    system("pause");
    return 0;
}

int caculate(std::string s) 
{
    std::stack<int> stk_num;
    std::stack<int> stk_s;

    int n = s.size();
    int i = 0;
    while (i < n)
    {
        if (!isdigit(s[i]))
        {
            if (stk_s.empty()) 
            {
                int val = -1;
                if (s[i] == '*') val = 1;
                else if (s[i] == '+') val = 0;
                else val = -1;
                stk_s.push(val);
                i++;
            }
            else 
            {
                int val = -1;
                if (s[i] == '*') val = 1;
                else {
                    val = s[i] == '+' ? 0 : -1;
                }
                while (!stk_s.empty() && stk_s.top() > val)
                {
                    int val1 = stk_num.top();
                    stk_num.pop();
                    int val2 = stk_num.top();
                    stk_num.pop();

                    stk_num.push(val1*val2);
                    stk_s.pop();
                }

                stk_s.push(val);
                i++;
            }
        }
        else 
        {
            // 是数字的话，自己加入堆栈
            std::string s_temp = "";
            while (isdigit(s[i])) 
            {
                s_temp += s[i];
                i++;
            }
            stk_num.push(string_to_int(s_temp));
        }

    }

    while (!stk_s.empty()) 
    {
        int index = stk_s.top();
        stk_s.pop();


        int num1 = stk_num.top();
        stk_num.pop();

        int num2 = stk_num.top();
        stk_num.pop();

        if (index == 1) 
        {
            stk_num.push(num1*num2);
        }
        else if (index == 0)
        {
            stk_num.push(num1+num2);
        }
        else 
        {
            stk_num.push(num1-num2);
        }
    }

    return stk_num.top();
}

int string_to_int(std::string s) {
    int res = 0;
    int n = s.size();
    int flag = 0;

    for (int i = 0; i < n; i++) {
        if (i == 0) {
            if (s[i] == '-') { //判断是否为负数
                flag = 1;
                continue;
            }
        }

        int val = s[i]-'0';
        res = res * 10 + val;
    }

    return flag == 0 ? res : -res;
}


/* 将中缀表达式转成后缀表达式(逆波兰表达式)
例如：中缀表达式："1+3*5-4*(7-5)"
后缀表达式：135*475-*-+  
*/

std::string change(std::string s)//字符串的中缀表达式转后缀表达式
{
    int n = s.size();
    std::stack<char> stk;

    std::string res;
    int i = 0;
    while (i < n)
    {
        if (isdigit(s[i]))
        {
            std::string temp;
            while (isdigit(s[i]))
            {
                temp += s[i];
                i++;
            }
            res += temp;
        }
        else 
        {
            if (stk.empty())
            {
                stk.push(s[i]);
            }
            else
            {
                if (s[i] == ')')
                {
                    while (!stk.empty() && stk.top() != '(')
                    {
                        res += stk.top();
                        stk.pop();
                    }
                    stk.pop(); //弹出'('
                }
                else
                {
                    if (s[i] == '+' || s[i] =='-')
                    {
                        while (!stk.empty() && (stk.top() == '*' || stk.top() == '/'))
                        {
                            res += stk.top();
                            stk.pop();
                        }
                        stk.push(s[i]);
                    }
                    else 
                    {
                        stk.push(s[i]);
                    }
                }
            }
            i++;
        }
    }
    while (!stk.empty())
    {
        res += stk.top();
        stk.pop();
    }

    return res;
}