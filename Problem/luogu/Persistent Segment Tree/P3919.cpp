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
    std::vector<int> info, left, right;
    int n, cnt = 0;

    int new_node()
    {
        info.push_back(0);
        left.push_back(-1);
        right.push_back(-1);

        return cnt++;
    }

    int clone(int x)
    {
        int i = new_node();
        info[i] = info[x];
        left[i] = left[x];
        right[i] = right[x];

        return i;
    }

    int build(int l, int r, const std::vector<int> &init_arr)
    {
        int rt = new_node();
        if (l == r)
        {
            info[rt] = init_arr[l];
        }
        else
        {
            int mid = std::midpoint(l, r);
            left[rt] = build(l, mid, init_arr);
            right[rt] = build(mid + 1, r, init_arr);
        }

        return rt;
    }

    int modify(int l, int r, int i, int jobi, int jobv)
    {
        int rt = clone(i);
        if (l == r)
        {
            info[rt] = jobv;
        }
        else
        {
            int mid = std::midpoint(l, r);
            if (jobi <= mid)
            {
                left[rt] = modify(l, mid, left[rt], jobi, jobv);
            }
            else
            {
                right[rt] = modify(mid + 1, r, right[rt], jobi, jobv);
            }
        }

        return rt;
    }

    int query(int l, int r, int i, int jobi)
    {
        if (l == r)
        {
             return info[i];
        }

        int mid = std::midpoint(l, r);

        if (jobi <= mid)
        {
            return query(l, mid, left[i], jobi);
        }
        else if (jobi >= mid + 1)
        {
            return query(mid + 1, r, right[i], jobi);
        }

        return 0;
    }
public:
    Seg_Tree(const std::vector<int>& init_arr, int &root): n(init_arr.size())
    {
        if (n > 0)
        {
            root = build(0, n - 1, init_arr);
        }
    }
    
    void modify(int jobi, int jobv, int v, int &root)
    {
        root = modify(0, n - 1, v, jobi, jobv);
    }

    int query(int jobi, int v)
    {
        return query(0, n - 1, v, jobi);
    }
};

void solve()
{
    int n, m;
    std::cin >> n >> m;

    std::vector<int> init(n);
    for (auto &x: init)
    {
        std::cin >> x;
    }

    std::vector<int> root(m + 1);
    Seg_Tree tr(init, root[0]);

    for (int i = 1, v, op, x, y; i <= m; ++i)
    {
        std::cin >> v >> op >> x;
        --x;

        if (op == 1)
        {
            std::cin >> y;

            tr.modify(x, y, root[v], root[i]);
        }
        else
        {
            root[i] = root[v];

            std::cout << tr.query(x, root[i]) << "\n";
        }
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
