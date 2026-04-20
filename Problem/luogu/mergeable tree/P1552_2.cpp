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
    int n, m;
    std::cin >> n >> m;

    std::vector<i64> leader(n), cost(n), ability(n), sum(n);
    for (int i = 0; i < n; ++i)
    {
        std::cin >> leader[i] >> cost[i] >> ability[i];

        --leader[i];
        sum[i] = cost[i];
    }

    using pq = __gnu_pbds::priority_queue<i64>;
    std::vector<pq> arr(n);

    for (int i = 0; i < n; ++i)
    {
        arr[i].push(cost[i]);
    }

    std::vector<int> father(n), size(n, 1);
    ranges::iota(father, 0);

    auto find = [&](this auto &&find, int i) -> int
    {
        father[i] = (father[i] == i? i: find(father[i]));
        return father[i];
    };

    i64 ans = 0;
    for (int i = n - 1; i >= 0; --i)
    {
        int h = find(i), hsize = size[h];
        i64 hsum = sum[h];

        while (hsum > m)
        {
            hsum -= arr[i].top();
            arr[i].pop();

            --hsize;
        }

        ans = std::max(ans, i64(hsize) * ability[i]);
        if (i > 0)
        {
            int p = find(leader[i]), psize = size[p];
            i64 psum = sum[p];

            arr[p].join(arr[h]);
            father[h] = p;

            size[father[p]] = psize + hsize;
            sum[father[p]] = psum + hsum;
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
