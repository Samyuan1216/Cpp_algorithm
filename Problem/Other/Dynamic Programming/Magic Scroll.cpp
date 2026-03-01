#include <bits/stdc++.h>
using namespace std;

int must_one(vector<int> &nums, int l, int r)
{
    int ans = 0;
    for (int a = l; a <= r; a++)
    {
        for (int b = a; b <= r; b++)
        {
            int cursum = 0;
            for (int i = l; i < a; i++)
            {
                cursum += nums[i];
            }

            for (int i = b + 1; i <= r; i++)
            {
                cursum += nums[i];
            }

            ans = max(ans, cursum);
        }
    }

    return ans;
}

int max_sum1(vector<int> &nums)
{
    int n = nums.size();

    int p1 = 0;
    for (auto &x: nums)
    {
        p1 += x;
    }

    int p2 = must_one(nums, 0, n - 1);

    int p3 = 0;
    for (int i = 1; i < n; i++)
    {
        p3 = max(p3, must_one(nums, 0, i - 1) + must_one(nums, i, n - 1));
    }

    return max(p1, max(p2, p3));
}

int max_sum2(vector<int> &nums)
{
    int n = nums.size(), sum = 0, maxsum = 0;

    int p1 = 0;
    for (auto &x: nums)
    {
        p1 += x;
    }

    vector<int> prefix(n);
    sum = nums[0];
    maxsum = max(0, nums[0]);

    for (int i = 1; i < n; i++)
    {
        prefix[i] = max(prefix[i - 1] + nums[i], maxsum);
        sum += nums[i];
        maxsum = max(maxsum, sum);
    }

    int p2 = prefix[n - 1];

    vector<int> suffix(n);
    sum = nums[n - 1];
    maxsum = max(0, nums[n - 1]);

    for (int i = n - 2; i >= 0; i--)
    {
        suffix[i] = max(suffix[i + 1] + nums[i], maxsum);
        sum += nums[i];
        maxsum = max(maxsum, sum);
    }

    int p3 = 0;
    for (int i = 1; i < n; i++)
    {
        p3 = max(p3, prefix[i - 1] + suffix[i]);
    }

    return max(p1, max(p2, p3));
}

random_device rd;
mt19937 gen(rd());
uniform_int_distribution disn(1, 50), disv(-100, 100);

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

        int ans1 = max_sum1(nums);
        int ans2 = max_sum2(nums);

        if (ans1 != ans2)
        {
            cout << "出错了！" << endl;

            cout << "nums: [ ";
            for (auto &x: nums)
            {
                cout << "x ";
            }
            cout << "]" << endl;

            break;
        }
    }

    cout << "测试结束" << endl;
}