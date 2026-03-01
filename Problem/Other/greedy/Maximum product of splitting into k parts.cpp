#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int f(int rest, int k)
{
    if (k == 1)
    {
        return rest;
    }

    int ans = INT32_MIN;
    for (int cur = 1; cur <= rest && (rest - cur) >= (k - 1); cur++)
    {
        int cur_ans = cur * f(rest - cur, k - 1);
        ans = max(ans, cur_ans);
    }

    return ans;
}

int max_value1(int n, int k)
{
    return f(n, k);
}

ll power(ll x, int n, int mod)
{
    ll ans = 1;
    while (n > 0)
    {
        if ((n & 1) == 1)
        {
            ans = (ans * x) % mod;
        }

        x = (x * x) % mod;
        n >>= 1;
    }

    return ans;
}

int max_value2(int n, int k)
{
    int mod = 1000000007;

    ll a = n / k;
    int b = n % k;
    ll part1 = power(a + 1, b, mod);
    ll part2 = power(a, k - b, mod);

    return (int)(part1 * part2) % mod;
}

random_device rd;
mt19937 gen(rd());
uniform_real_distribution dis(0.0, 1.0);

int main()
{
    int N = 30;
    int test_time = 2000;

    cout << "测试开始" << endl;
    for (int i = 0; i < test_time; i++)
    {
        int n = dis(gen) * N + 1;
        int k = dis(gen) * n + 1;

        int ans1 = max_value1(n, k);
        int ans2 = max_value2(n, k);

        if (ans1 != ans2)
        {
            cout << "出错了" << endl;
            break;
        }
    }
    cout << "测试完成" << endl;
}