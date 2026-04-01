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
    int n, m;
    std::cin >> n >> m;

    auto s = std::string(), t = std::string();
    std::cin >> s >> t;

    auto sb = std::array<bool, 26>();
    for (auto &c: s)
    {
        sb[c - 'a'] = true;
    }

    auto tb = std::array<bool, 26>();
    for (auto &c: t)
    {
        tb[c - 'a'] = true;
    }

    int q;
    std::cin >> q;

    while (q--)
    {
        auto str = std::string();
        std::cin >> str;

        bool a = true, b = true;
        for (auto &c: str)
        {
            a = a && sb[c - 'a'];
            b = b && tb[c - 'a'];
        }

        if (a && b)
        {
            std::cout << "Unknown\n";
        }
        else if (a)
        {
            std::cout << "Takahashi\n";
        }
        else
        {
            std::cout << "Aoki\n";
        }
    }
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
