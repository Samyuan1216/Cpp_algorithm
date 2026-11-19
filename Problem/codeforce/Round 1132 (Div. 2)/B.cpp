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
    int n, k;
    std::cin >> n >> k;

    std::vector<int> arr(n);
    for (auto &x: arr)
    {
        std::cin >> x;
    }

    ranges::sort(arr);

    std::vector<int> ans;
    for (int i = n - k; i < n; ++i)
    {
        ans.push_back(arr[i]);
    }

    for (int i = n - k - 1; i >= 0; --i)
    {
        ans.push_back(arr[i]);
    }

    i64 ck = 1, avg = ans[0];
    for (int i = 1; i < n; ++i)
    {
        if (i64(ans[i]) * i >= avg)
        {
            ++ck;
        }

        avg += ans[i];
    }

    if (ck != k)
    {
        std::cout << "NO\n";
        return;
    }

    std::cout << "YES\n";
    for (int i = 0; i < n; ++i)
    {
        std::cout << ans[i] << " \n"[i == n - 1];
    }
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