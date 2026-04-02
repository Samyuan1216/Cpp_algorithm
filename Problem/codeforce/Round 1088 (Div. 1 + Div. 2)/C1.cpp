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
    int n, k;
    std::cin >> n >> k;

    auto a = std::vector<int>(n);
    for (auto &x: a)
    {
        std::cin >> x;
    }

    auto b = std::vector<int>(n);
    for (auto &x: b)
    {
        std::cin >> x;
    }

    auto in = std::vector<bool>(n);
    auto allowed = std::set<int>();
    for (int i = n - k; i <= k - 1; ++i)
    {
        in[i] = true;
        allowed.insert(a[i]);
    }

    auto used = std::set<int>();
    bool status = true;
    for (int i = 0; i < n; ++i)
    {
        if (b[i] == -1)
        {
            continue;
        }

        if (in[i])
        {
            if (!allowed.contains(b[i]) || used.contains(b[i]))
            {
                status = false;
                break;
            }
            else
            {
                used.insert(b[i]);
            }
        }
        else
        {
            if (b[i] != a[i])
            {
                status = false;
                break;
            }
        }
    }

    std::cout << (status? "YES\n": "NO\n");
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
