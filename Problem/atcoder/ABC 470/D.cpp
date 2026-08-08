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
    int n, q;
    std::cin >> n >> q;

    std::vector<int> p1(n);
    for (auto &x: p1)
    {
        std::cin >> x;
        --x;
    }

    std::vector<int> p2(n);
    for (int i = 0; i < n; ++i)
    {
        p2[p1[i]] = i;
    }

    while (q--)
    {
        int op;
        std::cin >> op;

        if (op == 1)
        {
            int x, y;
            std::cin >> x >> y;
            --x, --y;

            std::swap(p1[x], p1[y]);
            std::swap(p2[p1[x]], p2[p1[y]]);
        }
        else
        {
            std::swap(p1, p2);
        }
    }

    for (int i = 0; i < n; ++i)
    {
        std::cout << p1[i] + 1 << " \n"[i == n - 1];
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
