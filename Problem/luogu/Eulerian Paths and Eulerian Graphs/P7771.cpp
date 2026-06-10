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
    int n, m;
    std::cin >> n >> m;

    std::vector<std::array<int, 2>> edges(m);
    for (auto &[u, v]: edges)
    {
        std::cin >> u >> v;
        --u, --v;
    }

    ranges::sort(edges, {}, [](auto &a) { return std::array{a[0], -a[1]}; });

    std::vector<int> head(n), next(m + 1), to(m + 1);
    int cnt = 0;

    auto add_edge = [&](int u, int v) -> void
    {
        next[++cnt] = head[u];
        to[cnt] = v;
        head[u] = cnt;
    };

    std::vector<int> out(n), in(n);
    for (auto &[u, v]: edges)
    {
        add_edge(u, v);
        ++out[u], ++in[v];
    }

    auto start = [&]() -> std::optional<int>
    {
        std::optional<int> start, end;
        for (int i = 0; i < n; ++i)
        {
            int v = out[i] - in[i];
            if (v < -1 || v > 1 || (v == 1 && start) || (v == -1 && end))
            {
                return std::nullopt;
            }

            if (v == 1)
            {
                start = i;
            }

            if (v == -1)
            {
                end = i;
            }
        }

        if (start.has_value() ^ end.has_value())
        {
            return std::nullopt;
        }

        if (start)
        {
            return start;
        }

        for (int i = 0; i < n; ++i)
        {
            if (out[i] > 0)
            {
                return i;
            }
        }

        return std::nullopt;
    } ();

    if (!start)
    {
        std::cout << "No\n";
        return;
    }

    std::vector<int> cur = head, path;
    [&](this auto &&dfs, int u) -> void
    {
        for (int ei = cur[u]; ei > 0; ei = cur[u])
        {
            cur[u] = next[ei];
            dfs(to[ei]);
        }

        path.push_back(u);
    } (*start);

    if (std::ssize(path) != m + 1)
    {
        std::cout << "No\n";
        return;
    }

    for (int i = std::ssize(path) - 1; i >= 0; --i)
    {
        std::cout << path[i] + 1 << " \n"[i == 0];
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
