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
    int n, x, y;
    std::cin >> n >> x >> y;

    std::vector<int> arr(n);
    for (auto &x: arr)
    {
        std::cin >> x;
    }

    std::vector<int> father(n);
    ranges::iota(father, 0);

    auto find = [&](this auto &&find, int i) -> int
    {
        return (father[i] = (father[i] == i? i: find(father[i])));
    };

    auto merge = [&](int x, int y) -> void
    {
        father[find(x)] = find(y);
    };

    auto link = [&](int num) -> void
    {
        for (int r = 0; r < num; ++r)
        {
            for (int i = r + num; i < n; i += num)
            {
                merge(i, i - num);
            }
        }
    };

    link(x), link(y);

    std::map<int, int> mp;
    int cnt = 0;

    for (int i = 0; i < n; ++i)
    {
        if (find(i) == i)
        {
            mp[i] = cnt++;
        }
    }

    std::vector<std::vector<int>> sort_val(cnt), sort_idx(cnt);
    for (int i = 0; i < n; ++i)
    {
        sort_val[mp[find(i)]].push_back(arr[i]);
        sort_idx[mp[find(i)]].push_back(i);
    }

    std::vector<int> ans(n);
    for (int i = 0; i < cnt; ++i)
    {
        ranges::sort(sort_val[i]);
        for (int j = 0; j < std::ssize(sort_idx[i]); ++j)
        {
            ans[sort_idx[i][j]] = sort_val[i][j];
        }
    }

    for (int i = 1; i < n; ++i)
    {
        if (ans[i] < ans[i - 1])
        {
            std::cout << "NO\n";
            return;
        }
    }

    std::cout << "YES\n";
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
