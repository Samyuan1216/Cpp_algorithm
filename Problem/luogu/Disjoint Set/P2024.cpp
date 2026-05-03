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
    int n, k;
    std::cin >> n >> k;

    std::vector<int> father(n), dist(n);
    ranges::iota(father, 0);

    auto find = [&](this auto &&find, int i) -> int
    {
        if (father[i] != i)
        {
            int old = father[i];
            father[i] = find(old);
            dist[i] = (dist[i] + dist[old]) % 3;
        }

        return father[i];
    };

    auto merge = [&](int l, int r, int v) -> void
    {
        if (int lf = find(l), rf = find(r); lf != rf)
        {
            father[lf] = rf;
            dist[lf] = (dist[r] - dist[l] + v + 3) % 3;
        }
    };

    auto check = [&](int op, int l, int r) -> bool
    {
        if (l >= n || r >= n || (op == 2 && l == r))
        {
            return false;
        }

        if (find(l) != find(r))
        {
            return true;
        }

        if (op == 1)
        {
            if (dist[l] != dist[r])
            {
                return false;
            }
        }
        else
        {
            if ((dist[l] - dist[r] + 3) % 3 != 1)
            {
                return false;
            }
        }

        return true;
    };

    int ans = 0;
    while (k--)
    {
        int op, x, y;
        std::cin >> op >> x >> y;
        --x, --y;

        if (!check(op, x, y))
        {
            ++ans;
            continue;
        }

        if (op == 1)
        {
            merge(x, y, 0);
        }
        else
        {
            merge(x, y, 1);
        }
    }

    std::cout << ans << "\n";
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
