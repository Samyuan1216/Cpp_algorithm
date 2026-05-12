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
    i64 n, k;
    std::cin >> n >> k;

    std::vector<i64> l(n);
    std::vector<std::vector<int>> a(n);

    for (int i = 0; i < n; ++i)
    {
        std::cin >> l[i];
        for (int j = 0, x; j < l[i]; ++j)
        {
            std::cin >> x;

            a[i].push_back(x);
        }
    }

    std::vector<i64> c(n);
    for (auto &x: c)
    {
        std::cin >> x;
    }

    std::vector<i64> idx(n);
    idx[0] = l[0] * c[0];

    for (int i = 1; i < n; ++i)
    {
        idx[i] = idx[i - 1] + l[i] * c[i];
    }

    int index = ranges::distance(idx.begin(), ranges::lower_bound(idx, k));
    if (index > 0)
    {
        k -= idx[index - 1];
    }

    std::cout << a[index][(k - 1 + l[index]) % l[index]] << "\n";
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
