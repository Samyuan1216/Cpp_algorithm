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
    int n, k;
    std::cin >> n >> k;

    std::vector<int> arr(n);
    for (auto &x: arr)
    {
        std::cin >> x;
    }

    std::map<int, int> mp;
    mp[arr[0]] = 1;

    for (int i = 1; i < n; ++i)
    {
        ++mp[arr[i]];
    }

    std::deque<int> count;
    for (auto &[val, cnt]: mp)
    {
        count.push_back(cnt);
    }

    ranges::sort(count);

    i64 ans = 0;
    for (int cnt = 0; !count.empty(); ++cnt)
    {
        if (cnt == count[0] - 1 && (k - n) % std::ssize(count) == 0 && count[0] - cnt + (k - n) / std::ssize(count) >= 1)
        {
            ++ans;
        }

        n -= std::ssize(count);
        while (!count.empty() && count[0] == cnt + 1)
        {
            count.pop_front();
        }
    }

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
