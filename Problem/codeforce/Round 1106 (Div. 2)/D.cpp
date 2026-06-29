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
    auto euler = [&](int n) -> std::vector<int>
    {
        std::vector<bool> visited(n + 1);
        std::vector<int> prime(n / 2 + 1);
        std::vector<int> min_prime(n + 1);
    
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
    };

    static auto min_prime = euler(1000000);

    auto C = [&](int n) -> std::vector<std::vector<int>>
    {
        auto c = std::vector(n + 1, std::vector<int>(n + 1));
        c[0][0] = 1;

        for (int i = 1; i <= n; ++i)
        {
            c[i][0] = 1;
            for (int j = 1; j <= i; ++j)
            {
                c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
            }
        }
    
        return c;
    };

    static auto c = C(300);

    int n;
    std::cin >> n;

    int cnt1 = 0, cnt2 = 0;
    while (n > 1)
    {
        ++cnt1;

        int p = min_prime[n];
        while (n % p == 0)
        {
            ++cnt2;
            n /= p;
        }
    }

    std::cout << cnt1 + cnt2 - 1 << "\n";
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
