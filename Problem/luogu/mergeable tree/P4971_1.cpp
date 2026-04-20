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

class Leftist_Tree
{
public:
    std::vector<i64> num;
    std::vector<int> up, left, right, dist, father;

    Leftist_Tree(const auto &arr, int n): num(arr), up(n + 1), left(n + 1), right(n + 1), dist(n + 1), father(n + 1)
    {
        dist[0] = -1;
        ranges::iota(father, 0);
    }

    int find(int i)
    {
        father[i] = (father[i] == i? i: find(father[i]));
        return father[i];
    }

    int merge(int i, int j)
    {
        if (i == 0 || j == 0)
        {
            return i + j;
        }

        if (num[i] < num[j] || (num[i] == num[j] && i > j))
        {
            std::swap(i, j);
        }

        right[i] = merge(right[i], j);
        up[right[i]] = i;

        if (dist[left[i]] < dist[right[i]])
        {
            std::swap(left[i], right[i]);
        }

        dist[i] = dist[right[i]] + 1;
        father[left[i]] = father[right[i]] = i;

        return i;
    }

    int remove(int i)
    {
        int h = find(i);
        father[left[i]] = left[i], father[right[i]] = right[i];

        int s = merge(left[i], right[i]), f = up[i];
        father[i] = s;
        up[s] = f;

        if (h != i)
        {
            father[s] = h;
            (left[f] == i? left[f]: right[f]) = s;

            for (int d = dist[s]; dist[f] > d + 1; f = up[f], ++d)
            {
                dist[f] = d + 1;
                if (dist[left[f]] < dist[right[f]])
                {
                    std::swap(left[f], right[f]);
                }
            }
        }

        up[i] = left[i] = right[i] = dist[i] = 0;
        return father[s];
    }

    void reduce(int i, i64 v)
    {
        int h = remove(i);
        num[i] = std::max(num[i] - v, 0ll);
        father[h] = father[i] = merge(h, i);
    }
};

void solve()
{
    i64 t, w, k;
    std::cin >> t >> w >> k;

    while (t--)
    {
        i64 n, m;
        std::cin >> n >> m;

        std::vector<i64> arr(n + 1);
        for (int i = 1; i <= n; ++i)
        {
            std::cin >> arr[i];
        }

        Leftist_Tree tr(arr, n);
        for (int i = 1; i <= m; ++i)
        {
            int op;
            std::cin >> op;

            if (op == 2)
            {
                int a;
                std::cin >> a;

                tr.reduce(a, tr.num[a]);
            }
            else if (op == 3)
            {
                int a, b;
                std::cin >> a >> b;

                tr.reduce(tr.find(a), b);
            }
            else
            {
                int a, b;
                std::cin >> a >> b;

                if (tr.find(a) != tr.find(b))
                {
                    tr.merge(tr.find(a), tr.find(b));
                }
            }
        }

        i64 ans = 0, max = 0;
        for (int i = 1; i <= n; ++i)
        {
            if (tr.father[i] != i)
            {
                continue;
            }

            ans += tr.num[i];
            max = std::max(max, tr.num[i]);
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
