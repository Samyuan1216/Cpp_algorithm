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

struct Seg_Tree
{
private:
    int n, cnt = 0;
    std::vector<int> info, size, left, right, root;

    int new_node()
    {
        info.push_back(0);
        size.push_back(0);
        left.push_back(-1);
        right.push_back(-1);

        return cnt++;
    }

    int clone(int x)
    {
        int i = new_node();
        info[i] = info[x];
        size[i] = size[x] + 1;
        left[i] = left[x];
        right[i] = right[x];

        return i;
    }

    int build(int l, int r)
    {
        int rt = new_node();
        if (l < r)
        {
            int mid = std::midpoint(l, r);
            left[rt] = build(l, mid);
            right[rt] = build(mid + 1, r);
        }

        return rt;
    }

    int modify(int l, int r, int i, int jobi)
    {
        int rt = clone(i);
        if (l < r)
        {
            int mid = std::midpoint(l, r);
            if (jobi <= mid)
            {
                left[rt] = modify(l, mid, left[rt], jobi);
            }
            else
            {
                right[rt] = modify(mid + 1, r, right[rt], jobi);
            }
        }

        return rt;
    }

    int query(int l, int r, int u, int v, int jobk)
    {
        if (l == r)
        {
            return l;
        }

        int lsize = size[left[v]] - size[left[u]];

        int mid = std::midpoint(l, r);
        if (lsize >= jobk)
        {
            return query(l, mid, left[u], left[v], jobk);
        }
        else
        {
            return query(mid + 1, r, right[u], right[v], jobk - lsize);
        }
    }
public:
    Seg_Tree(int size, int v) : n(size), root(v + 1)
    {
        if (n > 0)
        {
            root[0] = build(0, n - 1);
        }
    }
    
    void modify(int jobi, int v)
    {
        root[v] = modify(0, n - 1, root[v - 1], jobi);
    }

    int query(int jobk, int u, int v)
    {
        return query(0, n - 1, root[u], root[v], jobk);
    }
};

void solve()
{
    int n, m;
    std::cin >> n >> m;

    std::vector<int> arr(n);
    for (auto &x: arr)
    {
        std::cin >> x;
    }

    auto sorted = arr;
    ranges::sort(sorted);

    auto [lit, rit] = ranges::unique(sorted);
    sorted.erase(lit, rit);

    int s = std::ssize(sorted);
    Seg_Tree tr(s, n);

    for (int i = 1, x; i <= n; ++i)
    {
        x = std::distance(sorted.begin(), ranges::lower_bound(sorted, arr[i - 1]));
        tr.modify(x, i);
    }

    for (int i = 0, l, r, k, rank; i < m; ++i)
    {
        std::cin >> l >> r >> k;

        rank = tr.query(k, l - 1, r);
        std::cout << sorted[rank] << "\n";
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
