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

struct Basis
{
    using u64 = unsigned long long;
    std::array<u64, 64> p{};

    bool insert(std::integral auto x)
    {
        auto u = u64(x);
        for (int i = 63; i >= 0; --i)
        {
            if (u >> i == 1)
            {
                if (p[i] == 0)
                {
                    p[i] = u;

                    return true;
                }

                u ^= p[i];
            }
        }

        return false;
    }

    u64 query() const
    {
        u64 ans = 0;
        for (int i = 63; i >= 0; --i)
        {
            ans = std::max(ans, ans ^ p[i]);
        }

        return ans;
    }
};

void solve()
{
    int n, m;
    std::cin >> n >> m;

    Basis base;
    for (int i = 0, u, v, w; i < m; ++i)
    {
        std::cin >> u >> v >> w;

        base.insert(u ^ v ^ w);
    }

    i64 ans = 1 ^ n;
    for (int i = 63; i >= 0; --i)
    {
        ans = std::min(ans, i64(ans ^ base.p[i]));
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
