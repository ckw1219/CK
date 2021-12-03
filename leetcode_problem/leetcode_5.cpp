#include<string>
#include<vector>
#include<iostream>

using namespace std;
int longestPalindrome(string&, int, int);

//中心扩散法求最长回文子串
int main() {
    string s = "babad";
    int n = s.size();
    int maxLen = 1;
    for (int i = 0; i < n; i++) {
        int len1, len2;
        len1 = longestPalindrome(s, i, i);
        if (i+1 < n && s[i] == s[i+1]) {
           len2 = longestPalindrome(s, i, i+1);
        }

        maxLen = max(maxLen,max(len1,len2));
    }
    cout << maxLen << endl;
    system("pause");
    return maxLen;
}

int longestPalindrome(string& s, int index_lf, int index_rh) {
    int lf, rh;
    int n = s.size();
    lf = index_lf - 1;
    rh = index_rh + 1;

    while (lf >= 0 && rh < n) {
        if (s[lf] == s[rh]) {
            --lf;
            ++rh;
        }
        else {
            break;
        }
    } 

    return rh-lf-1;

}