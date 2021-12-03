#include<vector>
#include<iostream>
#include<queue>

using namespace std;

int main ()
{
    vector<vector<int>> nums{{1,4,3,1,3,2},
                {3,2,1,3,2,4},{2,3,3,2,3,1}};
    int m = nums.size();
    int n = nums[0].size();
    vector<vector<int>> used(m,vector<int>(n, 0));
    priority_queue<vector<int>,vector<vector<int>>,greater<vector<int>>> pq;

    int level = 1;
    int res = 0;
    for (int i = 0; i < n; i++)
    {
        vector<int> temp{nums[0][i],0, i};
        pq.push(temp);
        vector<int> temp1{nums[m-1][i],m-1, i};
        pq.push(temp1);

        used[0][i] = 1;
        used[m-1][i] = 1;
    }

    for (int i = 1; i < m-1; i++)
    {
        vector<int> temp{nums[i][0], i, 0};
        pq.push(temp);
        vector<int> temp1{nums[i][n-1], i, n-1};
        pq.push(temp1);
        
        used[i][0] = 1;
        used[i][n-1] = 1;
    }


    while (!pq.empty())
    {
        while (!pq.empty() && pq.top()[0] <= level)
        {
            vector<int> vec = pq.top();
            pq.pop();
            if (vec[0] < level)
            {
                res += level - vec[0];
            }

            int indexh = vec[1], indexl = vec[2];
            if (indexh - 1 >= 0 && used[indexh-1][indexl] == 0) 
            {
                vector<int> t{nums[indexh-1][indexl], indexh-1, indexl};
                pq.push(t);
                used[indexh-1][indexl] = 1;
            }
            if (indexh + 1 < m && used[indexh+1][indexl] == 0) 
            {
                vector<int> t {nums[indexh+1][indexl], indexh+1, indexl};
                pq.push(t);
                used[indexh+1][indexl] = 1;
            }

            if (indexl-1 >= 0 && used[indexh][indexl-1] == 0)
            {
                vector<int> t {nums[indexh][indexl-1], indexh, indexl-1};
                pq.push(t);
                used[indexh][indexl-1] = 1;
            }
            if (indexl+1 < n && used[indexh][indexl+1] == 0)
            {
                vector<int> t {nums[indexh][indexl+1], indexh, indexl+1};
                pq.push(t);
                used[indexh][indexl+1] = 1;
            }
        }
        level++;
    }

    cout << res << endl;
    system("pause");
    return 0;
}