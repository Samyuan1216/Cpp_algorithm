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
    int n, m, q;
    std::cin >> n >> m >> q;

    std::vector<int> father(n * m);
    ranges::iota(father, 0);

    constexpr i64 INF = -1e18;
    std::vector<i64> max(n * m, INF), size(n * m, 1), value(n * m);
    std::vector<bool> visited(n * m);

    auto find = [&](this auto &&find, int i) -> int
    {
        if (father[i] != i)
        {
            int old = father[i];
            father[i] = find(old);
            max[i] = std::max(max[i], max[old]);
        }

        return father[i];
    };

    auto get_idx = [&](int x, int y) -> int
    {
        return x * m + y;
    };

    static constexpr std::array dist{-1, 0, 1, 0, -1};

    i64 l = 0;
    while (q--)
    {
        int op;
        std::cin >> op;

        if (op == 1)
        {
            i64 x, y, v;
            std::cin >> x >> y >> v;
            x ^= l, y ^= l;
            --x, --y;

            int p = get_idx(x, y);
            visited[p] = true;
            value[p] = v;

            for (int i = 0, nx, ny; i < 4; ++i)
            {
                nx = x + dist[i], ny = y + dist[i + 1];
                if (nx < 0 || nx >= n || ny < 0 || ny >= m)
                {
                    continue;
                }

                int q = get_idx(nx, ny);
                if (!visited[q])
                {
                    continue;
                }

                int fq = find(q);
                if (fq != p)
                {
                    father[fq] = p;
                    max[fq] = value[p] - size[fq] + 1;
                    size[p] += size[fq];
                }
            }

            l = size[find(p)] - 1;
        }
        else
        {
            i64 x, y;
            std::cin >> x >> y;
            x ^= l, y ^= l;
            --x, --y;

            int p = get_idx(x, y);
            find(p);

            l = std::max(0ll, max[p] - value[p]);
        }

        std::cout << l << "\n";
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
