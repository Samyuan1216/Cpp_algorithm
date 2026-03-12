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
class AVL
{
private:
    struct Node
    {
        T key = T{};
        int height = 0;
        int left = 0;
        int right = 0;
        int count = 0;
        int size = 0;
    };

    std::vector<Node> tr;
    std::vector<int> free_list;
    int head = 0;

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

        tr[i] = {num, 1, 0, 0, 1, 1};
        return i;
    }

    void up(int i)
    {
        tr[i].size = tr[tr[i].left].size + tr[tr[i].right].size + tr[i].count;
        tr[i].height = std::max(tr[tr[i].left].height, tr[tr[i].right].height) + 1;
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

    int maintain(int i)
    {
        int lh = tr[tr[i].left].height, rh = tr[tr[i].right].height;
        if (lh - rh > 1)
        {
            if (tr[tr[tr[i].left].left].height < tr[tr[tr[i].left].right].height)
            {
                tr[i].left = left_rotate(tr[i].left); 
            }

            i = right_rotate(i);
        }
        else if (rh - lh > 1)
        {
            if (tr[tr[tr[i].right].right].height < tr[tr[tr[i].right].left].height)
            {
                tr[i].right = right_rotate(tr[i].right);
            }

            i = left_rotate(i);
        }

        return i;
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
        return maintain(i);
    }

    int remove_most_left(int i, int most_left)
    {
        if (i == most_left)
        {
            return tr[i].right;
        }

        tr[i].left = remove_most_left(tr[i].left, most_left);

        up(i);
        return maintain(i);
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
                    int ret = tr[i].left;
                    free_list.push_back(i);

                    return ret;
                }
                else if (tr[i].left == 0 && tr[i].right != 0)
                {
                    int ret = tr[i].right;
                    free_list.push_back(i);

                    return ret;
                }
                else
                {
                    int most_left = tr[i].right;
                    while (tr[most_left].left != 0)
                    {
                        most_left = tr[most_left].left;
                    }

                    tr[i].right = remove_most_left(tr[i].right, most_left);
                    std::tie(tr[most_left].left, tr[most_left].right) = std::tuple(tr[i].left, tr[i].right);

                    free_list.push_back(i);
                    i = most_left;
                }
            }
        }

        up(i);
        return maintain(i);
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

    T index(int i, int x)
    {
        if (i == 0)
        {
            return T{};
        }

        if (tr[tr[i].left].size >= x)
        {
            return index(tr[i].left, x);
        }

        if (tr[tr[i].left].size + tr[i].count < x)
        {
            return index(tr[i].right, x - tr[tr[i].left].size - tr[i].count);
        }

        return tr[i].key;
    }

    T pre(int i, const T &num)
    {
        if (i == 0)
        {
            return lim<T>::lowest();
        }

        if (tr[i].key >= num)
        {
            return pre(tr[i].left, num);
        }

        return std::max(tr[i].key, pre(tr[i].right, num));
    }

    T post(int i, const T &num)
    {
        if (i == 0)
        {
            return lim<T>::max();
        }

        if (tr[i].key <= num)
        {
            return post(tr[i].right, num);
        }

        return std::min(tr[i].key, post(tr[i].left, num));
    }
public:
    AVL()
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
    
    T index(int x)
    {
        return index(head, x);
    }
    
    T pre(const T &num)
    {
        return pre(head, num);
    }
    
    T post(const T &num)
    {
        return post(head, num);
    }
};

void solve()
{
    int n, m;
    std::cin >> n >> m;

    AVL tree;
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
            last = tree.index(x);
            ans ^= last;
        }
        else if (op == 5)
        {
            last = tree.pre(x);
            ans ^= last;
        }
        else
        {
            last = tree.post(x);
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
