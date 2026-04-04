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
    int n;
    std::cin >> n;

    auto a = std::vector<int>(n), b = std::vector<int>(n);
    for (int i = 0; i < n; ++i)
    {
        std::cin >> a[i] >> b[i];
    }

    int m;
    std::cin >> m;

    auto strs = std::vector(m, std::string());
    for (auto &str: strs)
    {
        std::cin >> str;
    }

    auto sorted = strs;
    ranges::sort(sorted, {}, &std::string::size);

    auto visited = std::vector(n, std::array<bool, 26>());
    for (int i = 0; i < n; ++i)
    {
        auto iter = ranges::equal_range(sorted, a[i], {}, [](const auto &s)
        {
            return s.size();
        });

        for (auto &str: iter)
        {
            visited[i][str[b[i] - 1] - 'a'] = true;
        }
    }

    for (auto &str: strs)
    {
        if (std::ssize(str) != n)
        {
            std::cout << "No\n";
            continue;
        }

        bool status = true;
        for (int i = 0; i < n; ++i)
        {
            if (!visited[i][str[i] - 'a'])
            {
                status = false;
                break;
            }
        }

        std::cout << (status? "Yes\n": "No\n");
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
