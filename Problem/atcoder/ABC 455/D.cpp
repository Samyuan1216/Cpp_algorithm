#include <bits/extc++.h>
namespace ranges = std::ranges;

using i64 = long long;

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
    int n, q;
    std::cin >> n >> q;

    std::vector<int> head(n + 1), bottom(n + 1), prev(n + 1), next(n + 1);
    ranges::iota(head, 0);
    ranges::iota(bottom, 0);

    while (q--)
    {
        int c, p;
        std::cin >> c >> p;

        int b = prev[c];
        if (b != 0)
        {
            next[b] = 0;
        }
        else
        {
            head[bottom[c]] = 0;
        }

        next[p] = c, prev[c] = p;
    }

    for (int i = 1, cnt = 0; i <= n; ++i, cnt = 0)
    {
        for (int j = head[i]; j != 0; j = next[j])
        {
            ++cnt;
        }

        std::cout << cnt << " \n"[i == n];
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
