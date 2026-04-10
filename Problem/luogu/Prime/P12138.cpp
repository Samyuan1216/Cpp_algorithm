#include <bits/extc++.h>
namespace ranges = std::ranges;

using i64 = long long;

template<typename T>
using lim = std::numeric_limits<T>;

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
        auto visited = std::vector<bool>(n + 1);
        auto prime = std::vector<int>(n / 2 + 1);
    
        int cnt = 0;
        for (int i = 2; i <= n; ++i)
        {
            if (!visited[i])
            {
                prime[cnt++] = i;
            }
    
            for (int j = 0; j < cnt; ++j)
            {
                if (i * prime[j] > n)
                {
                    break;
                }
    
                visited[i * prime[j]] = true;
                if (i % prime[j] == 0)
                {
                    break;
                }
            }
        }
    
        prime.resize(cnt);
        return prime;
    };

    auto prime = euler(30000);
    std::cout << prime[2024] << "\n";
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int t = 1;
    while (t--)
    {
        solve();
    }
}
