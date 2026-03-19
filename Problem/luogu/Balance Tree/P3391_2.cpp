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
        bool reverse = false;
    };

    std::vector<Node> tr;
    int head = 0;

    int new_node(const T &num)
    {
        int i = tr.size();
        tr.emplace_back(num, 0, 0, 1, head, false);
        tr[head].right = i;

        return i;
    }

    void up(int i)
    {
        tr[i].size = tr[tr[i].left].size + tr[tr[i].right].size + 1;
    }

    void down(int i)
    {
        if (tr[i].reverse)
        {
            std::swap(tr[i].left, tr[i].right);

            tr[tr[i].left].reverse = !tr[tr[i].left].reverse, tr[tr[i].right].reverse = !tr[tr[i].right].reverse;
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
public:
    Splay()
    {
        tr.emplace_back();
    }

    void add(const T &x)
    {
        splay(new_node(x), 0);
    }

    void reverse(int l, int r)
    {
        int i = find(l - 1), j = find(r + 1);
        splay(i, 0), splay(j, i);

        tr[tr[tr[head].right].left].reverse = !tr[tr[tr[head].right].left].reverse;
    }

    void print()
    {
        auto ans = std::vector<int>();
        auto inorder = [&](auto &&self, int u) -> void
        {
            if (u != 0)
            {
                down(u);

                self(self, tr[u].left);
                ans.emplace_back(tr[u].key);
                self(self, tr[u].right);
            }
        };

        inorder(inorder, head);
        for (int i = 1; i < std::ssize(ans) - 1; ++i)
        {
            std::cout << ans[i] << " \n"[i == std::ssize(ans) - 2];
        }
    }
};

void solve()
{
    int n, m;
    std::cin >> n >> m;

    Splay tree;
    tree.add(0);

    for (int i = 1; i <= n; ++i)
    {
        tree.add(i);
    }
    tree.add(0);

    for (int i = 1, x, y; i <= m; ++i)
    {
        std::cin >> x >> y;

        tree.reverse(x + 1, y + 1);
    }

    tree.print();
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
