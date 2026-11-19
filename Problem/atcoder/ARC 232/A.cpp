#include <bits/extc++.h>
namespace ranges = std::ranges;

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

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

    std::vector<std::array<int, 2>> p(m);
    for (auto &[x, y]: p)
    {
        std::cin >> x >> y;
        --x, --y;
    }

    std::vector<int> diff(n + 1);
    auto mark = [&](int l, int r) -> void
    {
        if (l > r)
        {
            return;
        }

        ++diff[l], --diff[r + 1];
    };

    ranges::sort(p);
    {
        std::vector<std::array<int, 2>> tmp;
        for (int l = 0, r = 0; r < m;)
        {
            while (r < m && p[r][0] == p[l][0])
            {
                ++r;
            }

            tmp.push_back(p[l]);
            mark(p[l][1] + 1, p[r - 1][1]);
            l = r;
        }

        p.swap(tmp);
    }

    ranges::sort(p, std::greater());
    {
        std::vector<std::array<int, 2>> tmp;
        for (int i = 0, bestr = -1; i < std::ssize(p); ++i)
        {
            if (bestr == -1 || p[i][1] < bestr)
            {
                bestr = p[i][1];
                tmp.push_back(p[i]);
            }
            else
            {
                mark(p[i][0], tmp.back()[0] - 1);
                mark(tmp.back()[1] + 1, p[i][1]);
            }
        }

        p.swap(tmp);
    }

    ranges::sort(p);

    int k = std::ssize(p);
    std::vector<int> head(k + 1, -1), next(n << 1), to(n << 1), limit(n << 1);
    int cnt = 0;

    auto add = [&](int u, int v) -> void
    {
        next[cnt] = head[u];
        to[cnt] = v;
        limit[cnt] = 1;
        head[u] = cnt++;

        next[cnt] = head[v];
        to[cnt] = u;
        limit[cnt] = 0;
        head[v] = cnt++;
    };

    for (int i = 0, l = 0, r = 0, b = 0; i < n; ++i)
    {
        b += diff[i];
        if (r < k && p[r][0] <= i)
        {
            ++r;
        }

        if (l < k && p[l][1] < i)
        {
            ++l;
        }

        if (b == 0 && l < r)
        {
            add(l, r);
        }
    }

    std::vector<int> pre(k + 1);
    auto bfs = [&]() -> bool
    {
        ranges::fill(pre, -1);

        std::queue<int> q;
        q.push(0);

        std::vector<bool> vis(k + 1);
        vis[0] = true;

        while (!q.empty())
        {
            int u = q.front();
            q.pop();

            for (int ei = head[u], v, lim; ei != -1; ei = next[ei])
            {
                v = to[ei], lim = limit[ei];
                if (!vis[v] && lim == 1)
                {
                    pre[v] = ei;
                    vis[v] = true;

                    q.push(v);
                    if (v == k)
                    {
                        return true;
                    }
                }
            }
        }

        return false;
    };

    if (!bfs())
    {
        std::cout << "No\n";
        return;
    }

    for (int u = k; u != 0; u = to[pre[u] ^ 1])
    {
        limit[pre[u]] = 0;
        limit[pre[u] ^ 1] = 1;
    }

    std::cout << (bfs()? "Yes\n": "No\n");
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
