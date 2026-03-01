#include <bits/stdc++.h>
using namespace std;

vector<int> top_k_sum1(vector<int> &nums, int k)
{
    int sum = 0;
    for (auto &x: nums)
    {
        sum += x;
    }

    vector<int> dp(sum + 1);
    dp[0] = 1;

    for (auto &x: nums)
    {
        for (int j = sum; j >= x; j--)
        {
            dp[j] += dp[j - x];
        }
    }

    vector<int> ans(k);
    int index = 0;
    for (int j = 0; j <= sum && index < k; j++)
    {
        for (int i = 0; i < dp[j] && index < k; i++)
        {
            ans[index++] = j;
        }
    }

    return ans;
}

vector<int> top_k_sum2(vector<int> &nums, int k)
{
    sort(nums.begin(), nums.end());

    struct compare
    {
        bool operator()(vector<int> &a, vector<int> &b)
        {
            return a[1] > b[1];
        }
    };

    priority_queue<vector<int>, vector<vector<int>>, compare> heap;
    heap.push(vector<int>{0, nums[0]});

    vector<int> ans(k);
    for (int i = 1; i < k; i++)
    {
        int last = heap.top()[0], sum = heap.top()[1];
        heap.pop();

        ans[i] = sum;
        if (last + 1 < nums.size())
        {
            heap.push(vector<int>{last + 1, sum - nums[last] + nums[last + 1]});
            heap.push(vector<int>{last + 1, sum + nums[last + 1]});
        }
    }

    return ans;
}

random_device rd;
mt19937 gen(rd());
uniform_int_distribution disn(1, 15), disv(0, 40);
uniform_real_distribution disk(0.0, 1.0);

vector<int> random_array(int len)
{
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
    for (int i = 1; i <= 500; i++)
    {
        int len = disn(gen);
        vector<int> nums = random_array(len);
        int k = disk(gen) * ((1 << len) - 1) + 1;
        vector<int> ans1 = top_k_sum1(nums, k);
        vector<int> ans2 = top_k_sum2(nums, k);

        if (ans1 != ans2)
        {
            cout << "出错了！" << endl;
            
            cout << "nums: [ ";
            for (auto &x: nums)
            {
                cout << x << " ";
            }
            cout << "]" << endl;

            cout << "ans1: [ ";
            for (auto &x: ans1)
            {
                cout << x << " ";
            }
            cout << "]" << endl;

            cout << "ans2: [ ";
            for (auto &x: ans2)
            {
                cout << x << " ";
            }
            cout << "]" << endl;

            break;
        }
    }

    cout << "测试结束" << endl;
}