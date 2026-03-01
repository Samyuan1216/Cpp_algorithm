#include <bits/stdc++.h>

using ll = long long;
using vi = std::vector<int>;
using vll = std::vector<ll>;
using v2ll = std::vector<vll>;

ll f(v2ll &dp, vi &arr, int i, int p)
{
    if (p <= 0 || i == -1)
    {
        return 0;
    }

    if (dp[i][p] != -1)
    {
        return dp[i][p];
    }

    int cur = std::min(arr[i], p);
    ll next = f(dp, arr, i - 1, cur - 1);
    ll ans = (ll)cur + next;

    dp[i][p] = ans;
    return ans;
}

ll max_sum1(vi &arr)
{
    int n = arr.size();
    int maxn = 0;
    for (auto &x: arr)
    {
        maxn = std::max(maxn, x);
    }

    ll ans = 0;
    v2ll dp(n, vll(maxn + 1, -1));
    for (int i = 0; i < n; i++)
    {
        ans = std::max(ans, f(dp, arr, i, arr[i]));
    }

    return ans;
}

ll sum(int maxn, int n)
{
    n = std::min(maxn, n);
    return (((ll)maxn * 2 - n + 1) * n) / 2;
}

ll max_sum2(vi &arr)
{
    int n = arr.size();
    
    vi sta(n);
    int size = 0;

    vll dp(n);
    ll ans = 0;
    for (int i = 0, cur_idx, cur_val; i < n; i++)
    {
        cur_idx = i, cur_val = arr[i];
        while (cur_val > 0 && size > 0)
        {
            int top_idx = sta[size - 1], top_val = arr[sta[size - 1]];
            if (top_val >= cur_val)
            {
                size--;
            }
            else
            {
                int idx_diff = cur_idx - top_idx, val_diff = cur_val - top_val;
                if (val_diff >= idx_diff)
                {
                    dp[i] += sum(cur_val, idx_diff) + dp[top_idx];
                    
                    cur_val = 0;
                    cur_idx = 0;

                    break;
                }
                else
                {
                    dp[i] += sum(cur_val, idx_diff);
                    
                    cur_val -= idx_diff;
                    cur_idx = top_idx;
                    size--;
                }
            }
        }

        if (cur_val > 0)
        {
            dp[i] += sum(cur_val, cur_idx + 1);
        }

        sta[size++] = i;
        ans = std::max(ans, dp[i]);
    }

    return ans;
}

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution dis(0.0, 1.0);

vi random_array(int n, int v)
{
    vi arr(n);
    for (int i = 0; i < n; i++)
    {
        arr[i] = dis(gen) * v;
    }

    return arr;
}

int main()
{
    int n = 100, v = 100, test_times = 50000;

    std::cout << "测试开始\n";
    for (int i = 1; i <= test_times; i++)
    {
        int size = dis(gen) * n + 1;
        vi arr = random_array(size, v);

        ll ans1 = max_sum1(arr), ans2 = max_sum2(arr);
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

        if (i % 100 == 0)
        {
            std::cout << "已测试 " << i << " 组数据\n";
        }
    }
    std::cout << "测试结束\n";
}