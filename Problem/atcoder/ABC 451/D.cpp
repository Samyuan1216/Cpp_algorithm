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
    auto pow2 = std::vector<std::string>();
    for (int i = 1; i <= 1000000000; i <<= 1)
    {
        pow2.push_back(std::to_string(i));
    }

    auto s = std::vector<i64>();
    auto dfs = [&](this auto &&self, int i, const std::string &path) -> void
    {
        auto str = path + pow2[i];
        s.push_back(std::stoi(str));

        for (int j = 0; j < std::ssize(pow2); ++j)
        {
            if (std::ssize(str) + std::ssize(pow2[j]) < 10)
            {
                self(j, str);
            }
        }
    };

    for (int i = 0; i < std::ssize(pow2); ++i)
    {
        dfs(i, "");
    }

    ranges::sort(s);
    auto [l, r] = ranges::unique(s);
    s.erase(l, r);

    int n;
    std::cin >> n;
    std::cout << s[n - 1] << "\n";
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
