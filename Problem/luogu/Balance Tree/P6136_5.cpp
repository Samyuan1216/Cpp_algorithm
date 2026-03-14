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
class Treap
{
    struct Node
    {
        T key = T{};
        int left = 0;
        int right = 0;
        int size = 0;
        int count = 0;
        double priority = 0;
    };

    std::vector<Node> tr;
    std::vector<int> free_list;
    int head = 0;

    std::mt19937 gen{std::random_device{}()};
    std::uniform_real_distribution<double> dis{0.0, 1.0};

    int new_node(const T &num)
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
            tr.push_back({});
        }

        tr[i] = {num, 0, 0, 1, 1, dis(gen)};
        return i;
    }

    void up(int i)
    {
        tr[i].size = tr[tr[i].left].size + tr[tr[i].right].size + tr[i].count;
    }

    int left_rotate(int i)
    {
        int r = tr[i].right;
        std::tie(tr[i].right, tr[r].left) = std::tuple(tr[r].left, i);

        up(i), up(r);
        return r;
    }

    int right_rotate(int i)
    {
        int l = tr[i].left;
        std::tie(tr[i].left, tr[l].right) = std::tuple(tr[l].right, i);

        up(i), up(l);
        return l;
    }

    int add(int i, const T &num)
    {
        if (i == 0)
        {
            return new_node(num);
        }

        if (tr[i].key == num)
        {
            ++tr[i].count;
        }
        else if (tr[i].key > num)
        {
            tr[i].left = add(tr[i].left, num);
        }
        else
        {
            tr[i].right = add(tr[i].right, num);
        }

        up(i);
        if (tr[i].left != 0 && tr[tr[i].left].priority > tr[i].priority)
        {
            return right_rotate(i);
        }

        if (tr[i].right != 0 && tr[tr[i].right].priority > tr[i].priority)
        {
            return left_rotate(i);
        }

        return i;
    }

    int remove(int i, const T &num)
    {
        if (i == 0)
        {
            return 0;
        }

        if (tr[i].key < num)
        {
            tr[i].right = remove(tr[i].right, num);
        }
        else if (tr[i].key > num)
        {
            tr[i].left = remove(tr[i].left, num);
        }
        else
        {
            if (tr[i].count > 1)
            {
                --tr[i].count;
            }
            else
            {
                if (tr[i].left == 0 && tr[i].right == 0)
                {
                    free_list.push_back(i);

                    return 0;
                }
                else if (tr[i].left != 0 && tr[i].right == 0)
                {
                    free_list.push_back(i);
                    i = tr[i].left;
                }
                else if (tr[i].left == 0 && tr[i].right != 0)
                {
                    free_list.push_back(i);
                    i = tr[i].right;
                }
                else
                {
                    if (tr[tr[i].left].priority >= tr[tr[i].right].priority)
                    {
                        i = right_rotate(i);
                        tr[i].right = remove(tr[i].right, num);
                    }
                    else
                    {
                        i = left_rotate(i);
                        tr[i].left = remove(tr[i].left, num);
                    }
                }
            }
        }

        up(i);
        return i;
    }

    int small(int i, const T &num)
    {
        if (i == 0)
        {
            return 0;
        }

        if (tr[i].key >= num)
        {
            return small(tr[i].left, num);
        }

        return tr[tr[i].left].size + tr[i].count + small(tr[i].right, num);
    }

    std::optional<T> index(int i, int x)
    {
        if (i == 0)
        {
            return std::nullopt;
        }

        if (tr[tr[i].left].size >= x)
        {
            return index(tr[i].left, x);
        }

        if (tr[tr[i].left].size + tr[i].count < x)
        {
            return index(tr[i].right, x -  tr[tr[i].left].size - tr[i].count);
        }

        return tr[i].key;
    }

    std::optional<T> pre(int i, const T &num)
    {
        if (i == 0)
        {
            return std::nullopt;
        }

        if (tr[i].key >= num)
        {
            return pre(tr[i].left, num);
        }

        auto right_res = pre(tr[i].right, num);
        return (right_res? right_res: tr[i].key);
    }

    std::optional<T> post(int i, const T &num)
    {
        if (i == 0)
        {
            return std::nullopt;
        }

        if (tr[i].key <= num)
        {
            return post(tr[i].right, num);
        }

        auto left_res = post(tr[i].left, num);
        return (left_res? left_res: tr[i].key);
    }
public:
    Treap()
    {
        tr.push_back({});
    }

    void add(const T &num)
    {
        head = add(head, num);
    }

    void remove(const T &num)
    {
        head = remove(head, num);
    }
    
    int rank(const T &num)
    {
        return small(head, num) + 1;
    }
    
    std::optional<T> index(int x)
    {
        return index(head, x);
    }
    
    std::optional<T> pre(const T &num)
    {
        return pre(head, num);
    }
    
    std::optional<T> post(const T &num)
    {
        return post(head, num);
    }
};

void solve()
{
    int n, m;
    std::cin >> n >> m;

    Treap tree;
    for (int i = 0, x; i < n; ++i)
    {
        std::cin >> x;

        tree.add(x);
    }

    int ans = 0;
    for (int i = 0, last = 0, op, x; i < m; ++i)
    {
        std::cin >> op >> x;

        x ^= last;
        if (op == 1)
        {
            tree.add(x);
        }
        else if (op == 2)
        {
            tree.remove(x);
        }
        else if (op == 3)
        {
            last = tree.rank(x);
            ans ^= last;
        }
        else if (op == 4)
        {
            last = *tree.index(x);
            ans ^= last;
        }
        else if (op == 5)
        {
            last = *tree.pre(x);
            ans ^= last;
        }
        else
        {
            last = *tree.post(x);
            ans ^= last;
        }
    }

    std::cout << ans << "\n";
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
