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

    std::vector<bool> visited(n);
    int cnt = 0;

    while (m--)
    {
        int a, b;
        std::cin >> a >> b;

        if (a + 1 == b && !visited[a])
        {
            visited[a] = true;
            ++cnt;
        }
    }

    std::cout << (cnt == n - 1? "Yes\n": "No\n");
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
