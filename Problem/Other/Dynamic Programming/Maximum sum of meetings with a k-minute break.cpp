#include <bits/stdc++.h>

using ll = long long;
using vi = std::vector<int>;
using vll = std::vector<ll>;

ll best1(vi &arr, int k)
{
    int n = arr.size();
    vll dp(n + 1);

    for (int i = n - 1, j, sum; i >= 0; i--)
    {
        for (j = i + 1, sum = 0; j < n && sum < k; j++)
        {
            sum += arr[j];
        }

        dp[i] = std::max(dp[i + 1], dp[j] + arr[i]);
    }

    return dp[0];
}

ll best2(vi &arr, int k)
{
    int n = arr.size();
    vi jump(n);

    for (int i = 0, l = 1, r = 1, sum = 0; i < n - 1; i++, l++)
    {
        while (r < n && sum < k)
        {
            sum += arr[r++];
        }

        jump[i] = r;
        sum -= arr[l];
    }

    jump[n - 1] = n;

    vll dp(n + 1);
    for (int i = n - 1; i >= 0; i--)
    {
        dp[i] = std::max(dp[i + 1], dp[jump[i]] + arr[i]);
    }

    return dp[0];
}

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution dis(0.0, 1.0);

vi random_array(int n, int v)
{
    vi arr(n);
    for (int i = 0; i < n; i++)
    {
        arr[i] = dis(gen) * v + 1;
    }

    return arr;
}

int main()
{
    int n = 1000, v = 3000, test_times = 10000;

    std::cout << "测试开始\n";
    for (int i = 1; i <= test_times; i++)
    {
        if (i % 100 == 0)
        {
            std::cout << "已测试 " << i << " 组数据\n";
        }

        int size = dis(gen) * n + 1;
        vi arr = random_array(size, v);
        int k = dis(gen) * v + 1;

        ll ans1 = best1(arr, k), ans2 = best2(arr, k);
        if (ans1 != ans2)
        {
            std::cout << "出错了\n";
            std::cout << ans1 << " " << ans2 << "\n";
            
            std::cout << "arr: [ ";
            for (auto &x: arr)
            {
                std::cout << x << " ";
            }
            std::cout << "]\n";

            break;
        }
    }
    std::cout << "测试结束\n";
}