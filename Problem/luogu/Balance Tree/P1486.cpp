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
    int head = 0;

    int new_node(const T &num)
    {
        int i = tr.size();
        tr.emplace_back(num, 0, 0, 1, 0);

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
    Splay()
    {
        tr.emplace_back();
    }

    void add(const T &num)
    {
        if (int idx = new_node(num); head == 0)
        {
            head = idx;
        }
        else
        {
            int f = 0, i = head, son = 0;
            while (i != 0)
            {
                f = i;
                if (tr[i].key <= num)
                {
                    son = 1;
                    i = tr[i].right;
                }
                else
                {
                    son = 0;
                    i = tr[i].left;
                }
            }

            (son == 1? tr[f].right: tr[f].left) = idx;
            tr[idx].father = f;

            splay(idx, 0);
        }
    }

    void departure(int limit)
    {
        int i = head, ans = 0;
        while (i != 0)
        {
            if (tr[i].key > limit)
            {
                ans = i;
                i = tr[i].left;
            }
            else
            {
                i = tr[i].right;
            }
        }

        if (ans == 0)
        {
            head = 0;
        }
        else
        {
            splay(ans, 0);

            tr[head].left = 0;
            up(head);
        }
    }

    std::optional<T> index(int x)
    {
        int i = find(x);
        splay(i, 0);

        return (i != 0? std::optional(tr[i].key): std::nullopt);
    }

    int size()
    {
        return tr[head].size;
    }
};

void solve()
{
    int n, limit;
    std::cin >> n >> limit;

    Splay tree;
    int change = 0, enter = 0;

    for (int i = 0; i < n; ++i)
    {
        char op;
        int x;
        std::cin >> op >> x;

        if (op == 'I')
        {
            if (x >= limit)
            {
                ++enter;
                tree.add(x - change);
            }
        }
        else if (op == 'A')
        {
            change += x;
        }
        else if (op == 'S')
        {
            change -= x;
            tree.departure(limit - change - 1);
        }
        else
        {
            if (x > tree.size())
            {
                std::cout << "-1\n";
            }
            else
            {
                std::cout << *tree.index(tree.size() - x + 1) + change << "\n";
            }
        }
    }

    std::cout << enter - tree.size() << "\n";
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
