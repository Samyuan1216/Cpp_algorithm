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

struct DSU
{
    std::vector<int> father, size;

    DSU(int n): father(n), size(n, 1)
    {
        ranges::iota(father, 0);
    }

    int find(int i)
    {
        return father[i] = (father[i] == i? i: find(father[i]));
    }

    void merge(int x, int y)
    {
        x = find(x), y = find(y);
        if (x == y)
        {
            return;
        }

        if (size[x] < size[y])
        {
            std::swap(x, y);
        }

        father[y] = x;
        size[x] += size[y];
    }

    bool same(int u, int v)
    {
        return find(u) == find(v);
    }
};

void solve()
{
    int n, q;
    std::cin >> n >> q;

    constexpr int bit = 12;
    std::vector s(1 << bit, DSU(n));

    auto insert = [&](this auto &&self, int u, int v, int m) -> void
    {
        if (s[m].same(u, v))
        {
            return;
        }

        s[m].merge(u, v);
        for (int p = m, lowbit; p != 0; p &= p - 1)
        {
            lowbit = p & -p;
            self(u, v, m ^ lowbit);
        }
    };

    auto query = [&](int u, int v) -> int
    {
        if (!s[0].same(u, v))
        {
            return -1;
        }

        int ans = 0;
        for (int p = bit - 1, t; p >= 0; --p)
        {
            t = ans | (1 << p);
            if (s[t].same(u, v))
            {
                ans = t;
            }
        }

        return ans;
    };

    i64 sum = 0;
    while (q--)
    {
        char op;
        std::cin >> op;

        if (op == '+')
        {
            int u, v, w;
            std::cin >> u >> v >> w;
            --u, --v;

            insert(u, v, w);
        }
        else
        {
            int u, v;
            std::cin >> u >> v;
            --u, --v;

            sum += query(u, v);
        }
    }

    std::cout << sum << "\n";
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
