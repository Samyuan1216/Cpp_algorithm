#include <bits/stdc++.h>
using namespace std;

int f(vector<int> &nums, int i, int s)
{
    if (i == nums.size())
    {
        return (s % 7 == 0? s: 0);
    }

    return max(f(nums, i + 1, s), f(nums, i + 1, s + nums[i]));
}

int max_sum1(vector<int> &nums)
{
    return f(nums, 0, 0);
}

int max_sum2(vector<int> &nums)
{
    int n = nums.size();
    vector<vector<int>> dp(n + 1, vector<int>(7));
    fill(dp[0].begin(), dp[0].end(), -1);
    dp[0][0] = 0;

    for (int i = 1, x = 0, cur = 0, need = 0; i <= n; i++)
    {
        x = nums[i - 1];
        cur = nums[i - 1] % 7;

        for (int j = 0; j < 7; j++)
        {
            dp[i][j] = dp[i - 1][j];
            need = (cur <= j? j - cur: j - cur + 7);

            if (dp[i - 1][need] != -1)
            {
                dp[i][j] = max(dp[i][j], dp[i - 1][need] + x);
            }
        }
    }

    return dp[n][0];
}

random_device rd;
mt19937 gen(rd());
uniform_int_distribution dis1(1, 15), dis2(0, 30);

vector<int> random_array()
{
    int len = dis1(gen);
    vector<int> arr(len);

    for (auto &x: arr)
    {
        x = dis2(gen);
    }

    return arr;
}

int main()
{
    cout << "测试开始" << endl;

    for (int i = 0; i < 20000; i++)
    {
        vector<int> arr = random_array();

        int ans1 = max_sum1(arr);
        int ans2 = max_sum2(arr);

        if (ans1 != ans2)
        {
            cout << "出错了" << endl;

            cout << "arr: [ ";
            for (auto &x: arr)
            {
                cout << x << " ";
            }
            cout << "]" << endl;
        }
    }

    cout << "测试结束" << endl;
}