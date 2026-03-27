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

template<typename T = int, typename F = std::plus<T>>
class BIT
{
private:
    int n;
    T init;
    F compute;
    std::vector<T> tree;

    static constexpr int lowbit(int i)
    {
        return i & -i;
    }
public:
    BIT(int size, F func = F{}, T i = T{}): n(size), init(i), compute(func), tree(size + 1, i) {}

    void update(int i, T v)
    {
        while (i <= n)
        {
            tree[i] = compute(tree[i], v);
            i += lowbit(i);
        }
    }

    T query(int i)
    {
        T ans = init;
        while (i > 0)
        {
            ans = compute(ans, tree[i]);
            i -= lowbit(i);
        }

        return ans;
    }
};

void solve()
{
    int n, m;
    std::cin >> n >> m;

    auto arr = std::vector<int>(n);
    for (auto &x: arr)
    {
        std::cin >> x;
    }

    auto cnt = std::vector<int>(m + 1);
    for (auto &x: arr)
    {
        ++cnt[x];
    }

    auto times = std::vector(m, std::array<int, 2>());
    for (int i = 0; i < m; ++i)
    {
        times[i] = {cnt[i + 1], i + 1};
    }

    ranges::sort(times);

    auto len = std::vector<i64>(m + 1);
    len[0] = n;

    for (int i = 0; i < m - 1; ++i)
    {
        len[i + 1] = len[i] + i64(i + 1) * (times[i + 1][0] - times[i][0]);
    }
    len[m] = lim<i64>::max();

    int q;
    std::cin >> q;

    auto ans = std::vector<i64>(q);
    auto query = std::vector<std::array<i64, 3>>();
    query.reserve(q);

    for (int i = 0; i < q; ++i)
    {
        i64 x;
        std::cin >> x;

        if (x <= n)
        {
            ans[i] = arr[x - 1];
            continue;
        }

        i64 ok = ranges::lower_bound(len, x) - len.begin();
        i64 num = x - len[ok - 1] - 1;
        num %= ok;
        ++num;

        query.push_back({ok, num, i});
    }

    ranges::sort(query);

    BIT<int> tr(m);
    int idx = 0;

    for (auto &[ok, num, i]: query)
    {
        while (idx < ok)
        {
            tr.update(times[idx++][1], 1);
        }

        auto check = [&](int mid)
        {
            return tr.query(mid) >= num;
        };

        auto find = [&](auto l, auto r)
        {
            std::optional<decltype(l)> ans;
            while (l <= r)
            {
                auto mid = std::midpoint(l, r);
                if (check(mid))
                {
                    ans = mid;
                    r = mid - 1;
                }
                else
                {
                    l = mid + 1;
                }
            }
        
            return ans;
        };

        ans[i] = *find(1, m);
    }

    for (auto &x: ans)
    {
        std::cout << x << "\n";
    }
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
