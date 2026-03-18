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

class FHQ_Treap
{
    struct Node
    {
        int num = 0;
        int left = 0;
        int right = 0;
        int size = 0;
        double priority = 0;
        bool reverse = false;
    };

    std::vector<Node> tr;
    int head = 0;

    std::mt19937 gen{std::random_device{}()};
    std::uniform_real_distribution<double> dis{0.0, 1.0};

    int new_node(int num)
    {
        int i = std::ssize(tr);
        tr.emplace_back(num, 0, 0, 1, dis(gen), false);

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

            int &left = tr[i].left, &right = tr[i].right;
            tr[left].reverse = !tr[left].reverse, tr[right].reverse = !tr[right].reverse;

            tr[i].reverse = false;
        }
    }

    void split(int &l, int &r, int i, int rank)
    {
        if (i == 0)
        {
            l = r = 0;
            return;
        }

        down(i);

        int &left = tr[i].left, &right = tr[i].right;
        if (tr[left].size + 1 <= rank)
        {
            l = i;
            split(right, r, right, rank - tr[left].size - 1);
        }
        else
        {
            r = i;
            split(l, left, left, rank);
        }

        up(i);
    }

    int merge(int l, int r)
    {
        if (l == 0 || r == 0)
        {
            return l + r;
        }

        if (tr[l].priority >= tr[r].priority)
        {
            down(l);
            tr[l].right = merge(tr[l].right, r);

            up(l);
            return l;
        }
        else
        {
            down(r);
            tr[r].left = merge(l, tr[r].left);

            up(r);
            return r;
        }
    }
public:
    FHQ_Treap(int n)
    {
        tr.emplace_back();

        for (int i = 1; i <= n; ++i)
        {
            head = merge(head, new_node(i));
        }
    }

    void reverse(int left, int right)
    {
        int l, m, r;
        split(l, r, head, right);
        split(l, m, l, left - 1);

        tr[m].reverse = !tr[m].reverse;
        head = merge(merge(l, m), r);
    }

    void print()
    {
        auto ans = std::vector<int>();
        auto inorder = [&](auto &&self, int i) -> void
        {
            if (i == 0)
            {
                return;
            }

            down(i);

            self(self, tr[i].left);
            ans.emplace_back(tr[i].num);
            self(self, tr[i].right);
        };

        inorder(inorder, head);
        for (int i = 0; i < std::ssize(ans); ++i)
        {
            std::cout << ans[i] << " \n"[i == std::ssize(ans) - 1];
        }
    }
};

void solve()
{
    int n, m;
    std::cin >> n >> m;

    FHQ_Treap tree(n);
    for (int i = 0, l, r; i < m; ++i)
    {
        std::cin >> l >> r;

        tree.reverse(l, r);
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
