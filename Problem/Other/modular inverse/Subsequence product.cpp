// https://www.nowcoder.com/share/jump/1961392931768297087279

#include <bits/stdc++.h>

long long power(long long x, int n, long long mod)
{
    long long ans = 1;
    while (n > 0)
    {
        if (n & 1)
        {
            ans = (ans * x) % mod;
        }

        x = (x * x) % mod;
        n >>= 1;
    }

    return ans;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    constexpr long long mod = 1000000007;
    int n, q;
    std::cin >> n >> q;

    std::vector<int> arr(n + 1);
    for (int i = 1; i <= n; i++)
    {
        std::cin >> arr[i];
    }

    std::vector<long long> mut(n + 1, 1);
    for (int i = 1; i <= n; i++)
    {
        mut[i] = (mut[i - 1] * arr[i]) % mod;
    }

    std::vector<long long> inv(n + 1, 1);
    for (int i = 1; i <= n; i++)
    {
        inv[i] = power(mut[i], mod - 2, mod);
    }

    for (int i = 1; i <= q; i++)
    {
        int l, r;
        std::cin >> l >> r;

        std::cout << mut[r] * inv[l - 1] % mod << " \n"[i == q];
    }
}