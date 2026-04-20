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
    std::vector<int> left, right, father, dist, size;

    Leftist_Tree(int n, const auto &arr): num(arr), left(n + 1), right(n + 1), father(n + 1), dist(n + 1), size(n + 1, 1)
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
    int n;
    std::cin >> n;

    std::vector<i64> arr(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        std::cin >> arr[i];

        arr[i] -= i;
    }

    Leftist_Tree tr(n, arr);

    std::vector<int> from(n + 1), to(n + 1);
    ranges::iota(from, 0);
    ranges::iota(to, 0);

    std::stack<int> sta;
    for (int i = 1, pre, cur, s; i <= n; ++i)
    {
        while (!sta.empty())
        {
            pre = tr.find(sta.top()), cur = tr.find(i);
            if (tr.num[pre] <= tr.num[cur])
            {
                break;
            }

            s = tr.size[pre] + tr.size[cur];
            cur = tr.merge(pre, cur);

            while (s > (i - from[pre] + 1 + 1) / 2)
            {
                cur = tr.pop(cur);
                --s;
            }

            from[cur] = from[pre];
            to[cur] = i;
            tr.size[cur] = s;

            sta.pop();
        }

        sta.push(i);
    }

    i64 sum = 0;
    std::vector<i64> ans(n + 1);

    while (!sta.empty())
    {
        int cur = tr.find(sta.top());
        for (int i = from[cur]; i <= to[cur]; ++i)
        {
            ans[i] = tr.num[cur];
            sum += std::abs(ans[i] - tr.num[i]);
        }

        sta.pop();
    }

    std::cout << sum << "\n";
    for (int i = 1; i <= n; ++i)
    {
        std::cout << ans[i] + i << " \n"[i == n];
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
