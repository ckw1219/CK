#include<iostream>
#include<vector>

using namespace std;

int count(int);

vector<vector<int>> res;
// vector<int> path;
int main()
{
    int n = 3;
    int res = count(n);
    cout << res << endl;
    return res;
}

void trackback(int n, int index, int lf, int rh)
{
    if (lf == rh)
}