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
    int n, q;
    std::cin >> n >> q;

    struct Point
    {
        i64 x;
        i64 y;
    };

    auto points = std::vector<Point>(n);
    for (auto &p: points)
    {
        std::cin >> p.x >> p.y;
    }

    auto ord = std::vector<int>(n);
    ranges::iota(ord, 0);

    auto cmp = [&](const Point &a, const Point &b) -> bool
    {
        int ah = (a.y < 0 || (a.y == 0 && a.x < 0)), bh = (b.y < 0 || (b.y == 0 && b.x < 0));
        if (ah != bh)
        {
            return ah < bh;
        }

        return (a.x * b.y - a.y * b.x) > 0;
    };

    ranges::sort(ord, [&](int i, int j)
    {
        return cmp(points[i], points[j]);
    });
    ranges::reverse(ord);

    auto rev = std::vector<int>(n);
    for (int i = 0; i < n; ++i)
    {
        rev[ord[i]] = i;
    }

    auto l = std::vector<int>(n);
    l[0] = 0;
    for (int i = 1; i < n; ++i)
    {
        l[i] = (cmp(points[ord[i]], points[ord[i - 1]])? i: l[i - 1]);
    }

    auto r = std::vector<int>(n);
    r[n - 1] = n;
    for (int i = n - 2; i >= 0; --i)
    {
        r[i] = (cmp(points[ord[i + 1]], points[ord[i]])? i + 1: r[i + 1]);
    }

    while (q--)
    {
        int a, b;
        std::cin >> a >> b;

        a = l[rev[a - 1]], b = r[rev[b - 1]];
        std::cout << (a < b? b - a: n - a + b) << "\n";
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
