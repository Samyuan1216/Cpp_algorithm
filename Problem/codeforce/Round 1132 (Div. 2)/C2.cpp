#include <bits/extc++.h>
namespace ranges = std::ranges;

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

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
    
        prime.resize(cnt);
        return prime;
    };

    static auto prime = euler(2e5 + 10);

    int a, b;
    std::cin >> a >> b;
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