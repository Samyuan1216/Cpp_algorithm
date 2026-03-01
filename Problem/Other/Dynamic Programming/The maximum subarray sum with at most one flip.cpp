#include <bits/stdc++.h>
using namespace std;

int max_sum(vector<int> &nums)
{
    int n = nums.size(), ans = nums[0];
    for (int i = 1, pre = nums[0]; i < n; i++)
    {
        pre = max(nums[i], nums[i] + pre);
        ans = max(ans, pre);
    }

    return ans;
}

int max_sum1(vector<int> &nums)
{
    int n = nums.size(), ans = INT32_MIN;
    for (int l = 0; l < n; l++)
    {
        for (int r = l; r < n; r++)
        {
            reverse(nums.begin() + l, nums.begin() + r + 1);
            ans = max(ans, max_sum(nums));
            reverse(nums.begin() + l, nums.begin() + r + 1);
        }
    }

    return ans;
}

int max_sum2(vector<int> &nums)
{
    int n = nums.size();

    vector<int> start(n);
    start[n - 1] = nums[n - 1];
    for (int i = n - 2; i >= 0; i--)
    {
        start[i] = max(nums[i], nums[i] + start[i + 1]);
    }

    int ans = start[0], end = nums[0], maxend = nums[0];
    for (int i = 1; i < n; i++)
    {
        ans = max(ans, maxend + start[i]);
        end = max(nums[i], nums[i] + end);
        maxend = max(maxend, end);
    }

    ans = max(maxend, ans);

    return ans;
}

random_device rd;
mt19937 gen(rd());
uniform_int_distribution disn(1, 50), disv(-200, 200);

vector<int> random_array()
{
    int len = disn(gen);
    vector<int> nums(len);

    for (auto &x: nums)
    {
        x = disv(gen);
    }

    return nums;
}

int main()
{
    cout << "测试开始" << endl;

    for (int i = 0; i < 20000; i++)
    {
        vector<int> nums = random_array();

        int ans1 = max_sum1(nums);
        int ans2 = max_sum2(nums);

        if (ans1 != ans2)
        {
            cout << "出错了！" << endl;

            cout << "nums: [ ";
            for (auto &x: nums)
            {
                cout << x << " ";
            }
            cout << "]" << endl;

            cout << ans1 << " " << ans2 << endl;

            break;
        }
    }

    cout << "测试结束" << endl;
}