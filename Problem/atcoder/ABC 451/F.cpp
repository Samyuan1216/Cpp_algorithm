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

    std::vector<int> father(n), dist(n);
    ranges::iota(father, 0);

    auto find = [&](this auto &&find, int i) -> int
    {
        if (father[i] != i)
        {
            int old = father[i];
            father[i] = find(old);
            dist[i] = (dist[i] + dist[old]) % 2;
        }

        return father[i];
    };

    std::vector<std::array<int, 2>> size(n, {1, 0});
    int ans = 0;

    auto merge = [&](int l, int r) -> void
    {
        if (int lf = find(l), rf = find(r); lf != rf)
        {
            ans -= std::min(size[lf][0], size[lf][1]) + std::min(size[rf][0], size[rf][1]);

            father[lf] = rf;
            dist[lf] = ((dist[r] - dist[l] + 1) % 2 + 2) % 2;

            if (dist[lf] == 0)
            {
                size[rf][0] += size[lf][0];
                size[rf][1] += size[lf][1];
            }
            else
            {
                size[rf][0] += size[lf][1];
                size[rf][1] += size[lf][0];
            }

            ans += std::min(size[rf][0], size[rf][1]);
        }
    };

    bool status = true;
    while (q--)
    {
        int u, v;
        std::cin >> u >> v;
        --u, --v;

        if (!status)
        {
            std::cout << "-1\n";
            continue;
        }

        if (find(u) == find(v))
        {
            if (dist[u] == dist[v])
            {
                status = false;

                std::cout << "-1\n";
                continue;
            }
        }
        else
        {
            merge(u, v);
        }

        std::cout << ans << "\n";
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
