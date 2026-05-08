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
    unsigned s;
    std::cin >> n >> q >> s;

    std::vector<std::vector<int>> g(n + 1);
    int root = 0;

    for (int i = 1, x; i <= n; ++i)
    {
        std::cin >> x;

        if (x == 0)
        {
            root = i;
        }
        else
        {
            g[x].push_back(i);
        }
    }

    unsigned power = std::bit_width(unsigned(n)) - 1;
    std::vector<int> deep(n + 1), length(n + 1), son(n + 1);
    auto stjump = std::vector(n + 1, std::vector<int>(power + 1));

    [&](this auto &&dfs, int u, int f) -> void
    {
        stjump[u][0] = f;
        for (unsigned p = 1; p <= power; ++p)
        {
            stjump[u][p] = stjump[stjump[u][p - 1]][p - 1];
        }

        deep[u] = deep[f] + 1;

        for (auto &v: g[u])
        {
            dfs(v, u);

            if (length[son[u]] < length[v])
            {
                son[u] = v;
            }
        }

        length[u] = length[son[u]] + 1;
    } (root, 0);

    std::vector<int> top(n + 1), dfn(n + 1);
    int cnt = 0;

    [&](this auto &&dfs, int u, int t) -> void
    {
        top[u] = t;
        dfn[u] = ++cnt;

        if (son[u] == 0)
        {
            return;
        }

        dfs(son[u], t);
        for (auto &v: g[u])
        {
            if (v == son[u])
            {
                continue;
            }

            dfs(v, v);
        }
    } (root, root);

    std::vector<int> up(n + 1), down(n + 1);
    for (int u = 1; u <= n; ++u)
    {
        if (u != top[u])
        {
            continue;
        }

        for (int i = 0, a = u, b = u; i < length[u]; ++i, a = stjump[a][0], b = son[b])
        {
            up[dfn[u] + i] = a;
            down[dfn[u] + i] = b;
        }
    }

    auto get = [&](unsigned x)
    {
        x ^= x << 13;
        x ^= x >> 17;
        x ^= x << 5;

        return (s = x);
    };

    i64 ans = 0;
    for (int i = 1, last_ans = 0, x, k; i <= q; ++i)
    {
        x = ((get(s) ^ last_ans) % n) + 1, k = (get(s) ^ last_ans) % deep[x];
        if (k == 0)
        {
            last_ans = x;
        }
        else if (k == (int)std::bit_floor(unsigned(k)))
        {
            last_ans = stjump[x][std::bit_width(unsigned(k)) - 1];
        }
        else
        {
            x = stjump[x][std::bit_width(unsigned(k)) - 1];
            k -= std::bit_floor(unsigned(k));
            k -= deep[x] - deep[top[x]];
            x = top[x];
            last_ans = (k >= 0? up[dfn[x] + k]: down[dfn[x] - k]);
        }

        ans ^= i64(i) * last_ans;
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
