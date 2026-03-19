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

template<typename T = int>
class Splay
{
    struct Node
    {
        T key = T{};
        int left = 0;
        int right = 0;
        int size = 0;
        int father = 0;
    };

    std::vector<Node> tr;
    std::vector<int> pos;
    int head = 0;

    int new_node(const T &num)
    {
        int i = tr.size();
        tr.emplace_back(num, 0, 0, 1, head);

        pos[num] = i;
        tr[head].right = i;

        return i;
    }

    void up(int i)
    {
        tr[i].size = tr[tr[i].left].size + tr[tr[i].right].size + 1;
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
public:
    Splay(int n): pos(n + 2)
    {
        tr.emplace_back();
    }

    void add(int s)
    {
        splay(new_node(s), 0);
    }

    int ask(int s)
    {
        int i = pos[s];
        splay(i, 0);

        return tr[tr[i].left].size;
    }

    int query(int s)
    {
        int i = find(s);
        splay(i, 0);

        return tr[i].key;
    }

    void move(int a, int b)
    {
        int l = find(a - 1), r = find(a + 1);
        splay(l, 0), splay(r, l);

        int i = tr[r].left;
        tr[r].left = 0;

        up(r), up(l);

        l = find(b - 1), r = find(b);
        splay(l, 0), splay(r, l);

        tr[r].left = i;
        tr[i].father = r;

        up(r), up(l);
    }
};

void solve()
{
    int n, m;
    std::cin >> n >> m;

    Splay tree(n);
    tree.add(0);

    for (int i = 1, x; i <= n; ++i)
    {
        std::cin >> x;

        tree.add(x);
    }
    tree.add(n + 1);

    n = n + 2;

    std::string op;
    for (int i = 1, s, t, rank; i <= m; ++i)
    {
        std::cin >> op >> s;

        rank = tree.ask(s) + 1;
        if (op[0] == 'T')
        {
            tree.move(rank, 2);
        }
        else if (op[0] == 'B')
        {
            tree.move(rank, n - 1);
        }
        else if (op[0] == 'I')
        {
            std::cin >> t;

            tree.move(rank, rank + t);
        }
        else if (op[0] == 'A')
        {
            std::cout << rank - 2 << "\n";
        }
        else
        {
            std::cout << tree.query(s + 1) << "\n";
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
