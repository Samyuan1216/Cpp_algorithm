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
class Skip_List
{
    static constexpr int MAXL = 20;
    struct Node
    {
        T key = T{};
        int count = 0;
        int level = 0;
        std::array<int, MAXL + 1> next;
        std::array<int, MAXL + 1> len;
    };

    std::vector<Node> tr;

    int random()
    {
        static std::mt19937 gen(std::random_device{}());
        static std::bernoulli_distribution coin(0.5);

        int ans = 1;
        while (coin(gen) && ans < MAXL)
        {
            ++ans;
        }

        return ans;
    }

    int new_node(const T &num)
    {
        int i = tr.size();
        tr.push_back({num, 1, random(), {}, {}});

        return i;
    }

    std::optional<int> find(int i, int h, T num)
    {
        while (tr[i].next[h] != 0 && tr[tr[i].next[h]].key < num)
        {
            i = tr[i].next[h];
        }

        if (h == 1)
        {
            if (tr[i].next[h] != 0 && tr[tr[i].next[h]].key == num)
            {
                return tr[i].next[h];
            }
            else
            {
                return std::nullopt;
            }
        }

        return find(i, h - 1, num);
    }

    void add_count(int i, int h, T num)
    {
        while (tr[i].next[h] != 0 && tr[tr[i].next[h]].key < num)
        {
            i = tr[i].next[h];
        }

        if (h == 1)
        {
            ++tr[tr[i].next[h]].count;
        }
        else
        {
            add_count(i, h - 1, num);
        }

        ++tr[i].len[h];
    }

    int add_node(int i, int h, int j)
    {
        int right_cnt = 0;
        while (tr[i].next[h] != 0 && tr[tr[i].next[h]].key < tr[j].key)
        {
            right_cnt += tr[i].len[h];
            i = tr[i].next[h];
        }

        if (h == 1)
        {
            std::tie(tr[i].next[h], tr[j].next[h]) = std::tuple(j, tr[i].next[h]);
            std::tie(tr[i].len[h], tr[j].len[h]) = std::tuple(tr[tr[i].next[h]].count, tr[tr[j].next[h]].count);

            return right_cnt;
        }

        int down_cnt = add_node(i, h - 1, j);
        if (h > tr[j].level)
        {
            ++tr[i].len[h];
        }
        else
        {
            std::tie(tr[i].next[h], tr[j].next[h]) = std::tuple(j, tr[i].next[h]);
            std::tie(tr[i].len[h], tr[j].len[h]) = std::tuple(down_cnt + tr[j].count, tr[i].len[h] + 1 - down_cnt - tr[j].count);
        }

        return right_cnt + down_cnt;
    }

    void remove_count(int i, int h, T num)
    {
        while (tr[i].next[h] != 0 && tr[tr[i].next[h]].key < num)
        {
            i = tr[i].next[h];
        }

        if (h == 1)
        {
            --tr[tr[i].next[h]].count;
        }
        else
        {
            remove_count(i, h - 1, num);
        }

        --tr[i].len[h];
    }

    void remove_node(int i, int h, int j)
    {
        if (h < 1)
        {
            return;
        }

        while (tr[i].next[h] != 0 && tr[tr[i].next[h]].key < tr[j].key)
        {
            i = tr[i].next[h];
        }

        if (h > tr[j].level)
        {
            --tr[i].len[h];
        }
        else
        {
            tr[i].next[h] = tr[j].next[h];
            tr[i].len[h] += tr[j].len[h] - 1;
        }

        remove_node(i, h - 1, j);
    }

    int small(int i, int h, T num)
    {
        int right_cnt = 0;
        while (tr[i].next[h] != 0 && tr[tr[i].next[h]].key < num)
        {
            right_cnt += tr[i].len[h];
            i = tr[i].next[h];
        }

        return right_cnt + (h == 1? 0: small(i, h - 1, num));
    }

    std::optional<T> index(int i, int h, int x)
    {
        int c = 0;
        while (tr[i].next[h] != 0 && c + tr[i].len[h] < x)
        {
            c += tr[i].len[h];
            i = tr[i].next[h];
        }

        if (h == 1)
        {
            return tr[tr[i].next[h]].key;
        }

        return index(i, h - 1, x - c);
    }

    std::optional<T> pre(int i, int h, T num)
    {
        while (tr[i].next[h] != 0 && tr[tr[i].next[h]].key < num)
        {
            i = tr[i].next[h];
        }

        if (h == 1)
        {
            if (i == 1)
            {
                return std::nullopt;
            }

            return tr[i].key;
        }

        return pre(i, h - 1, num);
    }

    std::optional<T> post(int i, int h, T num)
    {
        while (tr[i].next[h] != 0 && tr[tr[i].next[h]].key < num)
        {
            i = tr[i].next[h];
        }

        if (h == 1)
        {
            if (tr[i].next[h] == 0)
            {
                return std::nullopt;
            }

            if (tr[tr[i].next[h]].key > num)
            {
                return tr[tr[i].next[h]].key;
            }

            i = tr[i].next[h];
            if (tr[i].next[h] == 0)
            {
                return std::nullopt;
            }

            return tr[tr[i].next[h]].key;
        }

        return post(i, h - 1, num);
    }
public:
    Skip_List()
    {
        tr.resize(2);
        tr[1] = {lim<T>::min(), {}, MAXL, {}, {}};
    }

    void add(T num)
    {
        if (find(1, MAXL, num))
        {
            add_count(1, MAXL, num);
        }
        else
        {
            int new_idx = new_node(num);
            add_node(1, MAXL, new_idx);
        }
    }

    void remove(T num)
    {
        auto j_opt = find(1, MAXL, num);
        if (j_opt)
        {
            int j = *j_opt;
            if (tr[j].count > 1)
            {
                remove_count(1, MAXL, num);
            }
            else
            {
                remove_node(1, MAXL, j);
            }
        }
    }

    int rank(T num)
    {
        return small(1, MAXL, num) + 1;
    }

    std::optional<T> index(int x)
    {
        return index(1, MAXL, x);
    }

    std::optional<T> pre(T num)
    {
        return pre(1, MAXL, num);
    }

    std::optional<T> post(T num)
    {
        return post(1, MAXL, num);
    }
};

void solve()
{
    int n;
    std::cin >> n;

    Skip_List b;
    for (int i = 0, op, x; i < n; ++i)
    {
        std::cin >> op >> x;

        if (op == 1)
        {
            b.add(x);
        }
        else if (op == 2)
        {
            b.remove(x);
        }
        else if (op == 3)
        {
            std::cout << b.rank(x) << "\n";
        }
        else if (op == 4)
        {
            std::cout << *b.index(x) << "\n";
        }
        else if (op == 5)
        {
            std::cout << *b.pre(x) << "\n";
        }
        else
        {
            std::cout << *b.post(x) << "\n";
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
