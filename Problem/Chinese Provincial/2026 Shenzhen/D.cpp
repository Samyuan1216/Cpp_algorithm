#include <bits/extc++.h>
namespace ranges = std::ranges;

using i64 = long long;

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

template<typename T = int, typename F = std::less_equal<T>>
class FHQ_Treap
{
    struct Node
    {
        T key = T{};
        T sum = T{};
        int left = 0;
        int right = 0;
        int size = 0;
        double priority = 0;
    };

    std::vector<Node> tr;
    int head = 0;

    inline static std::mt19937 gen{std::random_device{}()};
    inline static std::uniform_real_distribution<double> dis{0.0, 1.0};

    F compute;

    int new_node(const T &num)
    {
        int i = tr.size();
        tr.emplace_back(num, num, 0, 0, 1, dis(gen));

        return i;
    }

    void up(int i)
    {
        tr[i].size = tr[tr[i].left].size + tr[tr[i].right].size + 1;
        tr[i].sum = tr[tr[i].left].sum + tr[tr[i].right].sum + tr[i].key;
    }

    void split_key(int &l, int &r, int i, const T &num)
    {
        if (i == 0)
        {
            l = r = 0;
            return;
        }

        if (compute(tr[i].key, num))
        {
            l = i;
            split_key(tr[i].right, r, tr[i].right, num);
        }
        else
        {
            r = i;
            split_key(l, tr[i].left, tr[i].left, num);
        }

        up(i);
    }

    void split_rank(int &l, int &r, int i, int rank)
    {
        if (i == 0)
        {
            l = r = 0;
            return;
        }

        if (tr[tr[i].left].size + 1 <= rank)
        {
            l = i;
            split_rank(tr[i].right, r, tr[i].right, rank - tr[tr[i].left].size - 1);
        }
        else
        {
            r = i;
            split_rank(l, tr[i].left, tr[i].left, rank);
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

    void insert(const T &num)
    {
        int l, r;
        split_key(l, r, head, num);

        head = merge(merge(l, new_node(num)), r);
    }

    T query_num(int k)
    {
        int l, m, r;
        split_rank(l, r, head, k);
        split_rank(l, m, l, k - 1);

        T res = tr[m].key;
        head = merge(merge(l, m), r);

        return res;
    }

    T query_sum(int k)
    {
        if (k <= 0)
        {
            return T{};
        }
        else if (k >= tr[head].size)
        {
            return tr[head].sum;
        }

        int l, r;
        split_rank(l, r, head, k);

        T res = tr[l].sum;
        head = merge(l, r);

        return res;
    }

    int size()
    {
        return tr[head].size;
    }
};

void solve()
{
    int n;
    std::cin >> n;

    std::vector<std::pair<char, i64>> arr(n);
    for (auto &[op, x]: arr)
    {
        std::cin >> op;

        if (op == 'F')
        {
            std::cin >> x;
        }
    }

    std::vector<int> next(n);
    for (int i = n - 1, ne = n; i >= 0; --i)
    {
        next[i] = ne;
        if (arr[i].first == 'W')
        {
            ne = i;
        }
    }

    FHQ_Treap<i64, std::greater_equal<>> tr;

    int i = 0;
    while (i < n && arr[i].first == 'F')
    {
        tr.insert(arr[i].second);
        ++i;
    }

    std::priority_queue<i64, std::vector<i64>, std::greater<>> heap;
    std::vector<i64> pending;
    i64 ans = 0, res = 0;
    int cnt = 0;

    for (int last, j; i < n; ++i)
    {
        if (arr[i].first == 'W')
        {
            for (auto &x: pending)
            {
                tr.insert(x);
            }
            pending.clear();

            res = tr.query_sum(++cnt);

            last = i;
            j = cnt;
            heap = {};
        }
        else
        {
            pending.push_back(arr[i].second);

            i64 cur = arr[i].second * (next[i] - i);
            i64 min = lim<i64>::max(), status = 0;
            if (j > 0 || !heap.empty())
            {
                if (j > 0)
                {
                    min = tr.query_num(j) * (next[i] - last);
                    status = 1;
                }

                if (!heap.empty() && heap.top() < min)
                {
                    min = heap.top();
                    status = 2;
                }
            }

            if (cur > min)
            {
                ans += cur - min;
                if (status == 1)
                {
                    --j;
                }
                else
                {
                    heap.pop();
                }

                heap.push(cur);
            }
        }

        ans += res;
    }

    std::cout << ans << "\n";
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int t = 1;
    std::cin >> t;
    while (t--)
    {
        solve();
    }
}
