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

void solve()
{
    i64 t, w, k;
    std::cin >> t >> w >> k;

    while (t--)
    {
        int n, m;
        std::cin >> n >> m;

        struct Node
        {
            i64 v;
            int id;

            bool operator<(const Node &other) const
            {
                if (v != other.v)
                {
                    return v < other.v;
                }

                return id > other.id;
            }
        };

        using pq = __gnu_pbds::priority_queue<Node>;
        std::vector<pq> arr(n + 1);
        std::vector<pq::point_iterator> iter(n + 1);

        for (int i = 1, x; i <= n; ++i)
        {
            std::cin >> x;

            iter[i] = arr[i].push({x, i});
        }

        std::vector<int> father(n + 1);
        ranges::iota(father, 0);

        auto find = [&](this auto &&find, int i) -> int
        {
            father[i] = (father[i] == i? i: find(father[i]));
            return father[i];
        };

        for (int i = 0; i < m; ++i)
        {
            int op;
            std::cin >> op;

            if (op == 2)
            {
                int a;
                std::cin >> a;

                arr[find(a)].modify(iter[a], {0, a});
            }
            else if (op == 3)
            {
                int a, b;
                std::cin >> a >> b;

                Node top = arr[find(a)].top();
                arr[find(a)].modify(iter[top.id], {std::max(0ll, top.v - b), top.id});
            }
            else
            {
                int a, b;
                std::cin >> a >> b;

                a = find(a), b = find(b);
                if (a != b)
                {
                    father[b] = a;
                    arr[a].join(arr[b]);
                }
            }
        }

        i64 ans = 0, max = 0;
        for (int i = 1; i <= n; ++i)
        {
            if (father[i] != i)
            {
                continue;
            }

            ans += arr[i].top().v;
            max = std::max(max, arr[i].top().v);
        }

        if (w == 2)
        {
            ans -= max;
        }
        else if (w == 3)
        {
            ans += max;
        }

        if (ans == 0)
        {
            std::cout << "Gensokyo " << ans << "\n";
        }
        else if (ans > k)
        {
            std::cout << "Hell " << ans << "\n";
        }
        else
        {
            std::cout << "Heaven " << ans << "\n";
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
