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
    int n, m;
    std::cin >> n >> m;

    std::vector<bool> visited(m);
    bool ans1 = true, ans2 = true;
    for (int i = 0, x; i < n; ++i)
    {
        std::cin >> x;

        if (visited[x - 1])
        {
            ans1 = false;
        }

        visited[x - 1] = true;
    }

    for (int i = 0; i < m; ++i)
    {
        if (!visited[i])
        {
            ans2 = false;
            break;
        }
    }

    std::cout << (ans1? "Yes\n": "No\n");
    std::cout << (ans2? "Yes\n": "No\n");
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
