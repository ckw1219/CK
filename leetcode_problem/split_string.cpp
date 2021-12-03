#include<iostream>
#include<string>
#include<vector>

// using namespace std;
std::vector<std::string> split(std::string);
int main() {
    std::string s = "1,1,2,3,4,5";
    std::vector<std::string> res = split(s);

    for (std::string ss : res) {
        std::cout << ss<< std::endl;
    }
    system("pause");
    return 0;

}

std::vector<std::string> split(std::string data) {
    std::vector<std::string> res;

    int n = data.size();
    int start = 0;
    for (int i = 0; i < n; i++) {
        if (i == n-1) { //最后一个字符不以‘,’判断
            res.push_back(data.substr(start));
        }
        if (data[i] == ',') {
            res.push_back(data.substr(start,i-start));
            start = i+1;
        }
    }

    return res;
}