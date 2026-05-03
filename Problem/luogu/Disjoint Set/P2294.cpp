#include <bits/extc++.h>
namespace ranges = std::ranges;
namespace pbds = __gnu_pbds;

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

    std::vector<int> father(n + 1);
    ranges::iota(father, 0);

    std::vector<int> dist(n + 1);
    auto find = [&](this auto &&find, int i) -> int
    {
        if (father[i] != i)
        {
            int old = father[i];
            father[i] = find(old);
            dist[i] += dist[old];
        }

        return father[i];
    };

    auto merge = [&](int l, int r, int v) -> void
    {
        if (int lf = find(l), rf = find(r); lf != rf)
        {
            father[lf] = rf;
            dist[lf] = dist[r] - dist[l] + v;
        }
    };

    auto check = [&](int l, int r, int v) -> bool
    {
        if (find(l) == find(r) && dist[l] - dist[r] != v)
        {
            return false;
        }

        return true;
    };

    bool ans = true;
    while (m--)
    {
        int s, t, v;
        std::cin >> s >> t >> v;

        if (check(s - 1, t, v))
        {
            merge(s - 1, t, v);
        }
        else
        {
            ans = false;
        }
    }

    std::cout << std::format("{}\n", ans);
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
