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
    int n;
    std::string str;
    std::cin >> n >> str;

    int f = 1;
    while (f < n - 1 && str[f] == str[f - 1])
    {
        ++f;
    }

    int e = n - 2;
    while (e > 0 && str[e] == str[e + 1])
    {
        --e;
    }

    for (int l = f, r = f; l <= e && r <= e;)
    {
        while (r <= e && str[l] == str[r])
        {
            ++r;
        }

        if (r - l == 1)
        {
            str.erase(l, 1);
            break;
        }

        l = r;
    }

    auto [l, r] = ranges::unique(str);
    str.erase(l, r);

    std::cout << std::ssize(str) << "\n";
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
