#include <bits/stdc++.h>
using namespace std;

vector<int> del(vector<int> &nums, int index)
{
    int len = nums.size() - 1;
    vector<int> ans(len);

    int i = 0;
    for (int j = 0; j < nums.size(); j++)
    {
        if (j != index)
        {
            ans[i++] = nums[j];
        }
    }

    return ans;
}

int lenKmaxSum(vector<int> nums, int k)
{
    int n = nums.size();

    int ans = INT32_MIN;
    for (int i = 0; i <= n - k; i++)
    {
        int cur = 0;
        for (int j = i, cnt = 0; cnt < k; j++, cnt++)
        {
            cur += nums[j];
        }
        ans = max(ans, cur);
    }

    return ans;
}

int max_sum1(vector<int> nums, int k)
{
    int n = nums.size();
    if (n <= k)
    {
        return 0;
    }

    int ans = INT32_MIN;
    for (int i = 0; i < n; i++)
    {
        vector<int> rest = del(nums, i);
        ans = max(ans, lenKmaxSum(rest, k));
    }
    return ans;
}

int max_sum2(vector<int> &nums, int k)
{
    int n = nums.size();
    if (n <= k)
    {
        return 0;
    }

    vector<int> dq(n);
    int l = 0, r = 0;

    long long sum = 0;
    int ans = INT32_MIN;
    for (int i = 0; i < n; i++)
    {
        while (l < r && nums[i] <= nums[dq[r - 1]])
        {
            r--;
        }

        dq[r++] = i;

        sum += nums[i];
        if (i >= k)
        {
            ans = max(ans, (int)(sum - nums[dq[l]]));
            if (dq[l] == i - k)
            {
                l++;
            }

            sum -= nums[i - k];
        }
    }

    return ans;
}

random_device rd;
mt19937 gen(rd());
uniform_int_distribution disn(1, 200), disv(-1000, 1000);

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

    for (int i = 0; i < 10000; i++)
    {
        vector<int> nums = random_array();
        int k = disn(gen);

        int ans1 = max_sum1(nums, k);
        int ans2 = max_sum2(nums, k);

        if (ans1 != ans2)
        {
            cout << "出错了！" << endl;

            cout << "nums: [ ";
            for (auto &x: nums)
            {
                cout << x << " ";
            }
            cout << "]" << endl;
            
            cout << k << endl;

            cout << ans1 << " " << ans2 << endl;

            break;
        }
    }

    cout << "测试结束" << endl;
}