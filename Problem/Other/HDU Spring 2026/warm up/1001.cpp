#include <bits/extc++.h>
namespace ranges = std::ranges;

using i64 = int64_t;

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
    int n;
    std::cin >> n;

    auto prime = std::vector<int>();
    int num = n;
    for (int i = 2; i * i <= num; ++i)
    {
        while (num % i == 0)
        {
            prime.push_back(i);
            num /= i;
        }
    }

    if (num > 1)
    {
        prime.push_back(num);
    }

    int ans;
    if (prime.empty() || n <= 2)
    {
        ans = 1;
    }
    else
    {
        int k = n;
        for (auto &p: prime)
        {
            if (p > 2)
            {
                k = p;
                break;
            }
        }

        if (n % 4 == 0)
        {
            k = std::min(k, 4);
        }

        ans = n / k;
    }

    std::cout << ans << "\n";
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
