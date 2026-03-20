#include <bits/extc++.h>
namespace ranges = std::ranges;

using i64 = int64_t;

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
    int n;
    std::cin >> n;

    auto arr = std::vector<i64>(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        std::cin >> arr[i];
    }

    auto g = std::vector(n + 1, std::vector<int>());
    for (int i = 1, u, v; i < n; ++i)
    {
        std::cin >> u >> v;

        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }

    struct Info
    {
        int size = 0;
        i64 min = 0;
        i64 surplus = 0;
    };

    auto info = std::vector<Info>(n + 1);
    auto ans = std::vector<i64>(n + 1);
    auto dfs = [&](auto &&self, int u, int f) -> Info
    {
        Info infou{1, arr[u], 0};

        bool status = false;
        i64 minv = lim<i64>::max();
        for (auto &v: g[u])
        {
            if (v != f)
            {
                auto infov = self(self, v, u);
                minv = std::min(minv, infov.min);
                info[v] = infov;

                status = true;
            }
        }

        if (!status)
        {
            ans[u] = infou.min;
            return infou;
        }

        if (minv < infou.min)
        {
            infou.surplus = infou.min - minv;
            infou.min = minv;
        }

        for (auto &v: g[u])
        {
            if (v != f)
            {
                infou.surplus += info[v].size * (info[v].min - minv) + info[v].surplus;
                infou.size += info[v].size;
            }
        }

        if (infou.min + infou.surplus >= minv)
        {
            infou.surplus -= minv - infou.min;
            infou.min =  minv;
        }
        else
        {
            infou.min += infou.surplus;
            infou.surplus = 0;

            i64 sizev = infou.size - 1, k = (minv - infou.min + sizev) / (sizev + 1);
            infou.surplus = k * (sizev + 1) - (minv - infou.min);
            infou.min = minv - k;
        }

        ans[u] = infou.min;
        return infou;
    };

    dfs(dfs, 1, 0);

    for (int i = 1; i <= n; ++i)
    {
        std::cout << ans[i] << " \n"[i == n];
    }
}

int main()
{
    int size(256<<20);
    __asm__ ( "movq %0, %%rsp\n"::"r"((char*)malloc(size)+size));

    std::cin.tie(nullptr)->sync_with_stdio(false);

    int t = 1;
    std::cin >> t;
    while (t--)
    {
        solve();
    }

    exit(0);
}
