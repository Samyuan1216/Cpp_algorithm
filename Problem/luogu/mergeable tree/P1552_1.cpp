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
    std::vector<i64> num, sum;
    std::vector<int> left, right, father, dist, size;

    Leftist_Tree(int n, const auto &arr): num(arr), sum(arr), left(n + 1), right(n + 1), father(n + 1), dist(n + 1), size(n + 1, 1)
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

        if (num[i] < num[j])
        {
            std::swap(i, j);
        }

        right[i] = merge(right[i], j);
        if (dist[left[i]] < dist[right[i]])
        {
            std::swap(left[i], right[i]);
        }

        dist[i] = dist[right[i]] + 1;
        father[left[i]] = father[right[i]] = i;

        return i;
    }

    int pop(int i)
    {
        father[left[i]] = left[i], father[right[i]] = right[i];
        father[i] = merge(left[i], right[i]);

        left[i] = right[i] = dist[i] = 0;
        return father[i];
    }
};

void solve()
{
    int n, m;
    std::cin >> n >> m;

    std::vector<i64> leader(n + 1), cost(n + 1), ability(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        std::cin >> leader[i] >> cost[i] >> ability[i];
    }

    Leftist_Tree tr(n, cost);

    i64 ans = 0;
    for (int i = n; i >= 1; --i)
    {
        int h = tr.find(i), hsize = tr.size[h];
        i64 hsum = tr.sum[h];

        while (hsum > m)
        {
            tr.pop(h);

            --hsize;
            hsum -= tr.num[h];

            h = tr.find(i);
        }

        ans = std::max(ans, i64(hsize) * ability[i]);
        if (i > 1)
        {
            int p = tr.find(leader[i]), psize = tr.size[p];
            i64 psum = tr.sum[p];

            tr.father[p] = tr.father[h] = tr.merge(p, h);
            tr.size[tr.father[p]] = psize + hsize;
            tr.sum[tr.father[p]] = psum + hsum;
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
