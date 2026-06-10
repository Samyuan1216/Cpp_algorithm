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

template<typename T = int, typename F = std::plus<T>>
struct BIT
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
        ++i;
        while (i <= n)
        {
            tree[i] = compute(tree[i], v);
            i += lowbit(i);
        }
    }

    T query(int i)
    {
        ++i;
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
    int n, q;
    std::cin >> n >> q;

    BIT<int> rows(q + 1), cols(q + 1);
    rows.update(0, n), cols.update(0, n);

    std::vector<int> row(n), col(n);

    i64 ans = 0;
    for (int t = 1; t <= q; ++t)
    {
        int op, x;
        std::cin >> op >> x;
        --x;

        if (op == 1)
        {
            ans += cols.query(t - 1) - cols.query(row[x] - 1);

            rows.update(row[x], -1);
            row[x] = t;
            rows.update(t, 1);
        }
        else
        {
            ans -= n - rows.query(col[x]);

            cols.update(col[x], -1);
            col[x] = t;
            cols.update(t, 1);
        }

        std::cout << ans << "\n";
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
