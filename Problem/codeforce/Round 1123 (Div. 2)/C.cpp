#include <bits/extc++.h>
namespace ranges = std::ranges;

using i64 = long long;

#ifndef YUAN_DEBUG
struct __X
{
    __X& operator<<(const auto& str) {return *this;}
    void sp([[maybe_unused]] const std::string& str = "") {}
} dout;
#define debug(x)
#endif

void solve()
{
    static auto min_prime = [&](int n) -> std::vector<int>
    {
        std::vector<bool> visited(n + 1);
        std::vector<int> prime(n + 1);
    
        std::vector<int> min_prime(n + 1);
        min_prime[1] = 1;
    
        int cnt = 0;
        for (int i = 2; i <= n; ++i)
        {
            if (!visited[i])
            {
                prime[cnt++] = i;
                min_prime[i] = i;
            }
    
            for (int j = 0; j < cnt; ++j)
            {
                if (i * prime[j] > n)
                {
                    break;
                }
    
                visited[i * prime[j]] = true;
                min_prime[i * prime[j]] = prime[j];
    
                if (i % prime[j] == 0)
                {
                    break;
                }
            }
        }
    
        return min_prime;
    } (3e5 + 10);

    int n, x;
    std::cin >> n >> x;

    std::map<int, i64> cnt;
    for (int i = 0, num; i < n; ++i)
    {
        std::cin >> num;

        int tmpn = num;
        while (tmpn > 1)
        {
            int tmp = min_prime[tmpn];
            cnt[tmp] += num;

            while (tmpn % tmp == 0)
            {
                tmpn /= tmp;
            }
        }
    }

    if (x == 1)
    {
        std::cout << 0 << "\n";
        return;
    }

    i64 max = -1, msum = 0;
    for (auto &[key, sum]: cnt)
    {
        if (std::gcd(key, x) == 1)
        {
            continue;
        }

        if (msum < sum)
        {
            max = key;
            msum = sum;
        }
    }

    std::cout << (max == -1? 0ll: msum) << "\n";
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int t = 1;
    std::cin >> t;
    while (t--)
    {
        solve();
    }
}
