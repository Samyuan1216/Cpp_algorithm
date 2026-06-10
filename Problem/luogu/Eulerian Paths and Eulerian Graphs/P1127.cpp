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
    int n;
    std::cin >> n;

    std::vector<std::string> strs(n);
    for (auto &str: strs)
    {
        std::cin >> str;
    }

    ranges::sort(strs, [](auto &a, auto &b) -> bool
    {
        if (a[0] != b[0])
        {
            return a[0] < b[0];
        }

        return a > b;
    });

    std::vector<int> head(26, -1), next(n, -1), to(n, -1), weight(n, -1);
    int cnt = 0;

    auto add_edge = [&](int u, int v, int i) -> void
    {
        next[cnt] = head[u];
        to[cnt] = v;
        weight[cnt] = i;
        head[u] = cnt++;
    };

    std::vector<int> out(26), in(26);
    for (int i = 0; i < n; ++i)
    {
        add_edge(strs[i][0] - 'a', strs[i].back() - 'a', i);
        ++out[strs[i][0] - 'a'], ++in[strs[i].back() - 'a'];
    }

    auto start = [&]() -> std::optional<int>
    {
        std::optional<int> start, end;
        for (int i = 0, v; i < 26; ++i)
        {
            v = out[i] - in[i];
            if (v > 1 || v < -1 || (v == 1 && start) || (v == -1 && end))
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

        for (int i = 0; i < 26; ++i)
        {
            if (out[i] != 0)
            {
                return i;
            }
        }

        return std::nullopt;
    } ();

    if (!start)
    {
        std::cout << "***\n";
        return;
    }

    std::vector<int> path, cur = head;
    [&](this auto &&dfs, int u, int w) -> void
    {
        for (int ei = cur[u]; ei != -1; ei = cur[u])
        {
            cur[u] = next[ei];

            dfs(to[ei], weight[ei]);
        }

        if (w != -1)
        {
            path.push_back(w);
        }
    } (*start, -1);

    if (std::ssize(path) != n)
    {
        std::cout << "***\n";
        return;
    }

    ranges::reverse(path);
    for (int i = 0; i < std::ssize(path); ++i)
    {
        std::cout << strs[path[i]] << ".\n"[i == std::ssize(path) - 1];
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
