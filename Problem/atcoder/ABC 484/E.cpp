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

struct BIT
{
    int n;
    std::vector<int> tree;

    static constexpr int lowbit(int i)
    {
        return i & -i;
    }

    BIT(int size): n(size), tree(size + 1) {}

    void update(int i, int v)
    {
        assert(0 <= i && i < n);

        ++i;
        while (i <= n)
        {
            tree[i] += v;
            i += lowbit(i);
        }
    }

    int query(int i)
    {
        if (i < 0)
        {
            return 0;
        }

        assert(i < n);

        ++i;
        int ans = 0;
        while (i > 0)
        {
            ans += tree[i];
            i -= lowbit(i);
        }

        return ans;
    }
};

void solve()
{
    i64 n, l, r;
    std::cin >> n >> l >> r;

    std::vector<i64> arr(n);
    for (auto &x: arr)
    {
        std::cin >> x;
    }

    std::vector<i64> pre(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        pre[i] = pre[i - 1] + arr[i - 1];
    }

    std::vector<i64> sorted = pre;
    {
        ranges::sort(sorted);
        auto [l, r] = ranges::unique(sorted);
        sorted.erase(l, r);
    }

    BIT tr(std::ssize(sorted));
    auto add = [&](i64 x) -> void
    {
        tr.update(std::distance(sorted.begin(), ranges::lower_bound(sorted, x)), 1);
    };

    auto cnt_le = [&](i64 x) -> int
    {
        return tr.query(std::distance(sorted.begin(), ranges::upper_bound(sorted, x)) - 1);
    };

    auto cnt_lt = [&](i64 x) -> int
    {
        return tr.query(std::distance(sorted.begin(), ranges::lower_bound(sorted, x)) - 1);
    };

    i64 ans = 0;

    add(pre[0]);
    for (int i = 1; i <= n; ++i)
    {
        ans += cnt_le(pre[i] - l) - cnt_lt(pre[i] - r);
        add(pre[i]);
    }

    std::cout << ans << "\n";
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int t = 1;
    // std::cin >> t;
    while (t--)
    {
        solve();
    }
}