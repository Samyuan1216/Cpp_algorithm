#include <bits/extc++.h>
namespace ranges = std::ranges;

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

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

    std::vector<int> arr(n);
    for (auto &x: arr)
    {
        std::cin >> x;
    }

    std::set<int> s;
    for (int i = 0; i < n; ++i)
    {
        s.insert(i);
    }

    for (int i = 1; i <= n; ++i)
    {
        auto itl = s.lower_bound(i * arr[i - 1]), itr = s.lower_bound(i * (arr[i - 1] + 1));

        std::vector<int> bin;
        while (itl != itr)
        {
            bin.push_back(*itl);
            ++itl;
        }

        for (auto &x: bin)
        {
            s.erase(x);
        }
    }

    std::cout << std::ssize(s) << "\n";
    for (auto &x: s)
    {
        std::cout << x << " ";
    }
    std::cout << "\n";
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
