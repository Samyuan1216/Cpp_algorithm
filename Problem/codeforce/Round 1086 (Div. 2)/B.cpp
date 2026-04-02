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
    int n, k, p, m;
    std::cin >> n >> k >> p >> m;

    auto arr = std::vector<int>(n);
    for (auto &x: arr)
    {
        std::cin >> x;
    }

    auto s = std::multiset<int>();
    for (int i = 0; i < k; ++i)
    {
        s.insert(arr[i]);
    }

    int cost = 0;
    for (int i = k; i < p; ++i)
    {
        cost += *s.begin();
        s.erase(s.begin());
        s.insert(arr[i]);
    }

    cost += arr[p - 1];
    s.erase(s.find(arr[p - 1]));

    int ans = 0;
    if (cost > m)
    {
        std::cout << ans << "\n";
        return;
    }
    else
    {
        ++ans;
        m -= cost;
    }

    for (int i = std::max(k, p); i < n; ++i)
    {
        s.insert(arr[i]);
        cost += *s.begin();
        s.erase(s.begin());
    }

    ans += m / cost;
    std::cout << ans << "\n";
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
