#include <bits/extc++.h>
namespace ranges = std::ranges;

using i64 = int64_t;

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

class Splay
{
    struct Node
    {
        int key = 0;
        int left = 0;
        int right = 0;
        int size = 0;
        int father = 0;
        int all = -1000000001;
        int pre = 0;
        int suf = 0;
        int sum = 0;
        bool update = false;
        int change = 0;
        bool reverse = false;
    };

    std::vector<Node> tr;
    std::vector<int> free_list;
    int head = 0;

    int new_node(int num)
    {
        int i;
        if (!free_list.empty())
        {
            i = free_list.back();
            free_list.pop_back();
        }
        else
        {
            i = tr.size();
            tr.emplace_back();
        }

        tr[i] = {num, 0, 0, 1, 0, num, std::max(num, 0), std::max(num, 0), num, false, 0, false};
        return i;
    }

    void up(int i)
    {
        int l = tr[i].left, r = tr[i].right;
        tr[i].size = tr[l].size + tr[r].size + 1;
        tr[i].sum = tr[l].sum + tr[r].sum + tr[i].key;
        tr[i].pre = std::max(tr[l].pre, tr[l].sum + tr[i].key + tr[r].pre);
        tr[i].suf = std::max(tr[r].suf, tr[l].suf + tr[i].key + tr[r].sum);
        tr[i].all = std::max(std::max(tr[l].all, tr[r].all), tr[l].suf + tr[i].key + tr[r].pre);
    }

    void set_update(int i, int val)
    {
        if (i == 0)
        {
            return;
        }

        tr[i].update = true;
        tr[i].change = val;
        tr[i].key = val;
        tr[i].sum = tr[i].size * val;
        tr[i].all = std::max(tr[i].sum, val);
        tr[i].pre = std::max(tr[i].sum, 0);
        tr[i].suf = std::max(tr[i].sum, 0);
    }

    void set_reverse(int i)
    {
        if (i == 0)
        {
            return;
        }

        std::swap(tr[i].pre, tr[i].suf);
        tr[i].reverse = !tr[i].reverse;
    }

    void down(int i)
    {
        if (tr[i].update)
        {
            set_update(tr[i].left, tr[i].change);
            set_update(tr[i].right, tr[i].change);

            tr[i].update = false;
        }

        if (tr[i].reverse)
        {
            std::swap(tr[i].left, tr[i].right);

            set_reverse(tr[i].left);
            set_reverse(tr[i].right);

            tr[i].reverse = false;
        }
    }

    int lr(int i)
    {
        return (tr[tr[i].father].right == i? 1: 0);
    }

    void rotate(int i)
    {
        int f = tr[i].father, g = tr[f].father, soni = lr(i), sonf = lr(f);
        if (soni == 1)
        {
            tr[f].right = tr[i].left;
            if (tr[f].right != 0)
            {
                tr[tr[f].right].father = f;
            }

            tr[i].left = f;
        }
        else
        {
            tr[f].left = tr[i].right;
            if (tr[f].left != 0)
            {
                tr[tr[f].left].father = f;
            }

            tr[i].right = f;
        }

        if (g != 0)
        {
            (sonf == 1? tr[g].right: tr[g].left) = i;
        }

        tr[f].father = i, tr[i].father = g;
        up(f), up(i);
    }

    void splay(int i, int goal)
    {
        int f = tr[i].father, g = tr[f].father;
        while (f != goal)
        {
            if (g != goal)
            {
                lr(i) == lr(f)? rotate(f): rotate(i);
            }

            rotate(i);
            f = tr[i].father, g = tr[f].father;
        }

        if (goal == 0)
        {
            head = i;
        }
    }

    int find(int rank)
    {
        int i = head;
        while (i != 0)
        {
            down(i);

            if (tr[tr[i].left].size + 1 == rank)
            {
                return i;
            }
            else if (tr[tr[i].left].size >= rank)
            {
                i = tr[i].left;
            }
            else
            {
                rank -= tr[tr[i].left].size + 1;
                i = tr[i].right;
            }
        }

        return 0;
    }

    int build(const auto &arr, int l, int r)
    {
        int mid = std::midpoint(l, r);
        int root = new_node(arr[mid]);

        if (l < mid)
        {
            tr[root].left = build(arr, l, mid - 1);
            tr[tr[root].left].father = root;
        }

        if (r > mid)
        {
            tr[root].right = build(arr, mid + 1, r);
            tr[tr[root].right].father = root;
        }

        up(root);
        return root;
    }

    void recycle(int i)
    {
        if (i == 0)
        {
            return;
        }

        free_list.emplace_back(i);
        recycle(tr[i].left);
        recycle(tr[i].right);
    }
public:
    Splay()
    {
        tr.emplace_back();
    }

    void insert(const auto &arr, int posi, int tot)
    {
        if (posi == 0)
        {
            head = build(arr, 1, tot);
            return;
        }

        int l = find(posi), r = find(posi + 1);
        splay(l, 0), splay(r, l);

        tr[r].left = build(arr, 1, tot);
        tr[tr[r].left].father = r;

        up(r), up(l);
    }

    void remove(int posi, int tot)
    {
        int l = find(posi - 1), r = find(posi + tot);
        splay(l, 0), splay(r, l);

        recycle(tr[r].left);
        tr[r].left = 0;

        up(r), up(l);
    }

    void make_same(int posi, int tot, int c)
    {
        int l = find(posi - 1), r = find(posi + tot);
        splay(l, 0), splay(r, l);

        set_update(tr[r].left, c);

        up(r), up(l);
    }

    void reverse(int posi, int tot)
    {
        int l = find(posi - 1), r = find(posi + tot);
        splay(l, 0), splay(r, l);

        set_reverse(tr[r].left);

        up(r), up(l);
    }

    int get_sum(int posi, int tot)
    {
        int l = find(posi - 1), r = find(posi + tot);
        splay(l, 0), splay(r, l);

        return tr[tr[r].left].sum;
    }

    int max_sum()
    {
        return tr[head].all;
    }
};

void solve()
{
    int n, m;
    std::cin >> n >> m;

    auto arr = std::vector<int>(n + 3);
    arr[1] = arr[n + 2] = -1000000001;

    for (int i = 2; i <= n + 1; ++i)
    {
        std::cin >> arr[i];
    }

    Splay tree;
    tree.insert(arr, 0, n + 2);

    std::string op;
    for (int i = 1; i <= m; ++i)
    {
        std::cin >> op;

        if (op[0] == 'I')
        {
            int posi, tot;
            std::cin >> posi >> tot;

            ++posi;
            arr = std::vector<int>(tot + 1);

            for (int i = 1; i <= tot; ++i)
            {
                std::cin >> arr[i];
            }

            tree.insert(arr, posi, tot);
        }
        else if (op[0] == 'D')
        {
            int posi, tot;
            std::cin >> posi >> tot;

            ++posi;
            tree.remove(posi, tot);
        }
        else if (op[0] == 'M' && std::ssize(op) == 9)
        {
            int posi, tot, c;
            std::cin >> posi >> tot >> c;

            ++posi;
            tree.make_same(posi, tot, c);
        }
        else if (op[0] == 'R')
        {
            int posi, tot;
            std::cin >> posi >> tot;

            ++posi;
            tree.reverse(posi, tot);
        }
        else if (op[0] == 'G')
        {
            int posi, tot;
            std::cin >> posi >> tot;

            ++posi;
            std::cout << tree.get_sum(posi, tot) << "\n";
        }
        else
        {
            std::cout << tree.max_sum() << "\n";
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
