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
    int n;
    std::cin >> n;

    std::vector<i64> arr(n);
    i64 total = 0, max = 0;

    using u64 = unsigned long long;
    for (auto &x: arr)
    {
        std::cin >> x;

        max = std::max(max, i64(std::bit_width(u64(x))));
        total ^= x;
    }

    if (std::bit_width(u64(total)) == max)
    {
        std::cout << total << "\n";
        return;
    }

    Basis base;
    i64 mask = (~total) & ((1ll << 60) - 1);

    for (auto &x: arr)
    {
        base.insert(x & mask);
    }

    std::cout << base.query() << "\n";
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
