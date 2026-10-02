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

template<typename T = int, typename F = std::plus<T>>
struct BIT
{
    int n;
    T init;
    F compute;
    std::vector<T> tree;

    static constexpr int lowbit(int i)
    {
        return i & -i;
    }

    BIT(int size, F func = F{}, T i = T{}): n(size), init(i), compute(func), tree(size + 1, i) {}

    void update(int i, T v)
    {
        ++i;
        while (i <= n)
        {
            tree[i] = compute(tree[i], v);
            i += lowbit(i);
        }
    }

    T query(int i)
    {
        ++i;
        T ans = init;
        while (i > 0)
        {
            ans = compute(ans, tree[i]);
            i -= lowbit(i);
        }

        return ans;
    }
};

void solve()
{
    int n;
    std::cin >> n;

    std::vector<int> p(n), pos(n);
    for (int i = 0; i < n; ++i)
    {
        std::cin >> p[i];
        --p[i];

        pos[p[i]] = i;
    }

    BIT bad(n);
    for (int i = 0; i < n - 1; ++i)
    {
        bad.update(i, (pos[i] < pos[i + 1]? 0: 1));
    }

    int q;
    std::cin >> q;

    while (q--)
    {
        int op, x, y;
        std::cin >> op >> x >> y;
        --x, --y;

        if (op == 1)
        {
            std::cout << bad.query(y - 1) - (x == 0? 0: bad.query(x - 1)) + 1 << "\n";
        }
        else
        {
            int u = p[x], v = p[y];
            std::vector<int> t{u - 1, u, v - 1, v};

            ranges::sort(t);
            auto [l, r] = ranges::unique(t);
            t.erase(l, r);

            for (auto &x: t)
            {
                if (x < 0 || x >= n - 1)
                {
                    continue;
                }

                bad.update(x, -1 * (pos[x] <= pos[x + 1]? 0: 1));
            }

            std::swap(p[x], p[y]);
            pos[u] = y, pos[v] = x;

            for (auto &x: t)
            {
                if (x < 0 || x >= n - 1)
                {
                    continue;
                }

                bad.update(x, (pos[x] <= pos[x + 1]? 0: 1));
            }
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
