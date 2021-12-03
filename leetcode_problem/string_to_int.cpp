#include<iostream>
#include<string>
#include<vector>

int string_to_int(std::string s);

int main() {
    std::string s1 = "123";
    std::string s2 = "-123";

    std::string s3 = s1.substr(0,1);

    int a = string_to_int(s1);
    int b = string_to_int(s2);

    std::cout << a << std::endl;
    std::cout << b << std::endl;

    system("pause");
    return 0;
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