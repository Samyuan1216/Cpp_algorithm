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

    auto s = std::string(), t = std::string();
    std::cin >> s >> t;

    s = "(" + s + ")";
    t = "(" + t + ")";
    n += 2;

    int idx;
    auto dfs = [&](this auto &&self, const auto &str, int depth) -> std::array<int, 2>
    {
        if (str[idx] == ')')
        {
            ++idx;
            return {1, -1};
        }

        auto u = std::array{0, -1};
        int child = 0;

        while (idx < n && str[idx] == '(')
        {
            ++idx;
            auto v = self(str, depth + 1);

            u[0] += v[0];
            if (u[1] == -1 && v[1] != -1)
            {
                u[1] = v[1];
            }

            ++child;
        }

        ++idx;
        if (child >= 2)
        {
            u[1] = depth;
        }

        return u;
    };

    idx = 1;
    auto sd = dfs(s, 0);

    idx = 1;
    auto td = dfs(t, 0);

    std::cout << (sd == td? "YES\n": "NO\n");
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
