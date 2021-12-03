#include<iostream>
#include<vector>

using namespace std;

int count(int);

int main()
{
    int n = 3;
    int res = count(n);
    cout << res << endl;
    return res;
}

int count(int n)
{
    vector<int> dp(n+1, 0);
    dp[0] = 1,dp[1] = 1;
    
    for (int i = 2; i <= n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            dp[i] += dp[i-1-j]*dp[j];
        }
    }

    return dp[n];
}