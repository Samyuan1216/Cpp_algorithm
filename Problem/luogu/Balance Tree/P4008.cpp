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
        char key = {};
        int left = 0;
        int right = 0;
        int size = 0;
        double priority = 0;
    };

    std::vector<Node> tr;
    int head = 0;
    int pos = 0;

    std::mt19937 gen{std::random_device{}()};
    std::uniform_real_distribution<double> dis{0.0, 1.0};

    int new_node(const char &c)
    {
        int i = tr.size();
        tr.emplace_back(c, 0, 0, 1, dis(gen));

        return i;
    }

    void up(int i)
    {
        tr[i].size = tr[tr[i].left].size + tr[tr[i].right].size + 1;
    }

    void split(int &l, int &r, int i, int rank)
    {
        if (i == 0)
        {
            l = r = 0;
            return;
        }

        if (tr[tr[i].left].size + 1 <= rank)
        {
            l = i;
            split(tr[i].right, r, tr[i].right, rank - tr[tr[i].left].size - 1);
        }
        else
        {
            r = i;
            split(l, tr[i].left, tr[i].left, rank);
        }

        up(i);
    }

    int merge(int l, int r)
    {
        if (l == 0 || r == 0)
        {
            return l + r;
        }

        if (tr[l].priority > tr[r].priority)
        {
            tr[l].right = merge(tr[l].right, r);

            up(l);
            return l;
        }
        else
        {
            tr[r].left = merge(l, tr[r].left);

            up(r);
            return r;
        }
    }
public:
    FHQ_Treap()
    {
        tr.emplace_back();
    }

    void Move(int k)
    {
        pos = k;
    }

    void Insert(int n, const std::string &str)
    {
        int l, r;
        split(l, r, head, pos);

        for (const auto &c: str)
        {
            l = merge(l, new_node(c));
        }

        head = merge(l, r);
    }

    void Delete(int n)
    {
        int l, m, r;
        split(l, r, head, pos + n);
        split(l, m, l, pos);

        head = merge(l, r);
    }

    void Get(int n)
    {
        int l, m, r;
        split(l, r, head, pos + n);
        split(l, m, l, pos);

        auto ans = std::string();
        auto inorder = [&](auto &&self, int i) -> void
        {
            if (i == 0)
            {
                return;
            }

            self(self, tr[i].left);
            ans += tr[i].key;
            self(self, tr[i].right);
        };

        inorder(inorder, m);
        std::cout << ans << "\n";

        head = merge(merge(l, m), r);
    }

    void Prev()
    {
        --pos;
    }

    void Next()
    {
        ++pos;
    }
};

void solve()
{
    int n;
    std::cin >> n;

    FHQ_Treap tree;
    while (n--)
    {
        auto op = std::string();
        std::cin >> op;

        if (op[0] == 'M')
        {
            int k;
            std::cin >> k;

            tree.Move(k);
        }
        else if (op[0] == 'I')
        {
            int n;
            std::cin >> n;

            auto str = std::string();
            for (int i = 0; i < n;)
            {
                char c = std::cin.get();
                if (c >= 32 && c <= 126)
                {
                    str += c;
                    ++i;
                }
            }

            tree.Insert(n, str);
        }
        else if (op[0] == 'D')
        {
            int n;
            std::cin >> n;

            tree.Delete(n);
        }
        else if (op[0] == 'G')
        {
            int n;
            std::cin >> n;

            tree.Get(n);
        }
        else if (op[0] == 'P')
        {
            tree.Prev();
        }
        else
        {
            tree.Next();
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
