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
    int k;
    std::cin >> k;

    int m = std::pow(2, k - 1);
    std::vector<int> cur(m);

    std::string path;
    [&](this auto &&dfs, int u, int ei) -> void
    {
        while (cur[u] < 2)
        {
            int ne = cur[u]++;
            dfs((u * 2 + ne) % m, ne);
        }

        path += (ei == -1? std::string(k - 1, '0'): std::to_string(ei));
    } (0, -1);

    ranges::reverse(path);
    std::cout << m * 2 << " " << path.substr(0, m * 2) << "\n";
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
