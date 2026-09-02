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
    int n, k;
    std::cin >> n >> k;

    std::vector<std::vector<int>> g(n);
    std::vector<int> arr(n);

    for (int i = 0; i < n; ++i)
    {
        std::cin >> arr[i];
        --arr[i];

        g[i].push_back(arr[i]);
        g[arr[i]].push_back(i);
    }

    if (k == 1)
    {
        for (int i = 0; i < n; ++i)
        {
            if (arr[i] != i)
            {
                std::cout << "NO\n";
                return;
            }
        }

        std::cout << "YES\n";
        return;
    }

    std::vector<int> dfn(n, -1), from(n);
    int cnt = 0;

    for (int i = 0; i < n; ++i)
    {
        if (dfn[i] != -1)
        {
            continue;
        }

        int size = 0;
        [&](this auto &&self, int u) -> void
        {
            dfn[u] = cnt++;
            for (auto &v: g[u])
            {
                if (dfn[v] == -1)
                {
                    from[v] = u;
                    self(v);
                }
                else if (dfn[u] < dfn[v])
                {
                    ++size;
                    for (int i = v; i != u; i = from[i])
                    {
                        ++size;
                    }
                }
            }
        } (i);

        if (size != k)
        {
            std::cout << "NO\n";
            return;
        }
    }

    std::cout << "YES\n";
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
