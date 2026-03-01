#include <bits/stdc++.h>
#include <bits/extc++.h>
namespace ranges = std::ranges;
namespace views = std::views;

using i64 = int64_t;
using i128 = __int128;
using u64 = uint64_t;
using u128 = unsigned __int128;
using f64 = double;
using f128 = long double;

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
    int n, x, y;
    std::cin >> n >> x >> y;

    int minn = lim<int>::max();
    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i)
    {
        std::cin >> arr[i];

        if (i >= x && i < y)
        {
            minn = std::min(minn, arr[i]);
        }
    }

    std::vector<int> sub;
    if (minn != lim<int>::max())
    {
        std::vector<int> temp;

        int i = x;
        while (arr[i] != minn)
        {
            temp.push_back(arr[i]);
            ++i;
        }

        while (i < y)
        {
            sub.push_back(arr[i]);
            ++i;
        }

        sub.insert(sub.end(), temp.begin(), temp.end());
    }

    std::vector<int> ans;
    bool add = false;
    for (int i = 0; i < n; ++i)
    {
        if (i >= x && i < y)
        {
            continue;
        }

        int num = arr[i];
        if (!sub.empty() && !add && sub[0] < num)
        {
            ans.insert(ans.end(), sub.begin(), sub.end());
            add = true;
        }

        ans.push_back(num);
    }

    if (!add)
    {
        ans.insert(ans.end(), sub.begin(), sub.end());
    }

    for (int i = 0; i < int(ans.size()); ++i)
    {
        std::cout << ans[i] << " \n"[i == int(ans.size()) - 1];
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
