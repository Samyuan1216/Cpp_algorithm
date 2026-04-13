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

    auto g = std::vector(6, std::vector<std::string>());
    for (int i = 0; i < q; ++i)
    {
        auto a = std::string(), b = std::string();
        std::cin >> a >> b;

        g[b[0] - 'a'].push_back(a);
    }

    auto ans = std::set<std::string>();
    auto dfs = [&](this auto &&self, std::string &path) -> void
    {
        if (std::ssize(path) == n)
        {
            ans.insert(path);
            return;
        }

        char c = path[0];
        for (auto &str: g[c - 'a'])
        {
            path.replace(0, 1, str);
            self(path);
            path.replace(0, str.size(), 1, c);
        }
    };

    auto s = std::string{"a"};
    dfs(s);

    std::cout << std::ssize(ans) << "\n";
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
