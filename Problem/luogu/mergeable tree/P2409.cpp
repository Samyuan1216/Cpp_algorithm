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

struct Leftist_Tree
{
    static constexpr int INF = 1e9;

    std::vector<int> cost, idx, jdx, pre;
    std::vector<int> left, right, dist;

    Leftist_Tree()
    {
        cost.push_back(0);
        idx.push_back(0);
        jdx.push_back(0);
        pre.push_back(0);
        left.push_back(0);
        right.push_back(0);
        dist.push_back(-1);
    }

    int new_node(int i, int j, const auto &arr)
    {
        int id = std::ssize(cost);
        cost.push_back(j + 1 < std::ssize(arr)? arr[j + 1] - arr[j]: INF);
        idx.push_back(i);
        jdx.push_back(j);
        pre.push_back(0);
        left.push_back(0);
        right.push_back(0);
        dist.push_back(0);

        return id;
    }

    int clone(int i)
    {
        int id = std::ssize(cost);
        cost.push_back(cost[i]);
        idx.push_back(idx[i]);
        jdx.push_back(jdx[i]);
        pre.push_back(0);
        left.push_back(left[i]);
        right.push_back(right[i]);
        dist.push_back(dist[i]);

        return id;
    }

    int merge(int i, int j)
    {
        if (i == 0 || j == 0)
        {
            return i + j;
        }

        if (cost[i] > cost[j])
        {
            std::swap(i, j);
        }

        int h = clone(i);
        right[h] = merge(right[h], j);

        if (dist[left[h]] < dist[right[h]])
        {
            std::swap(left[h], right[h]);
        }

        dist[h] = dist[right[h]] + 1;
        return h;
    }

    int pop(int i)
    {
        if (left[i] == 0 && right[i] == 0)
        {
            return 0;
        }

        if (left[i] == 0 || right[i] == 0)
        {
            return clone(left[i] + right[i]);
        }

        return merge(left[i], right[i]);
    }
};

void solve()
{
    int n, k;
    std::cin >> n >> k;

    std::vector<std::vector<int>> arr(n);
    int first = 0;

    for (auto &a: arr)
    {
        int m;
        std::cin >> m;

        a.resize(m);
        for (auto &x: a)
        {
            std::cin >> x;
        }

        first += a[0];
    }

    Leftist_Tree tr;
    int head = 0;

    for (int i = 0; i < n; ++i)
    {
        head = tr.merge(head, tr.new_node(i, 0, arr[i]));
    }

    tr.pre[head] = first;

    std::vector<int> ans;
    ans.push_back(first);

    auto cmp = [&](int a, int b)
    {
        return tr.pre[a] + tr.cost[a] > tr.pre[b] + tr.cost[b];
    };

    std::priority_queue<int, std::vector<int>, decltype(cmp)> heap(cmp);
    heap.push(head);

    while (std::ssize(ans) < k)
    {
        head = heap.top();
        heap.pop();

        ans.push_back(tr.pre[head] + tr.cost[head]);

        int h1 = tr.pop(head);
        if (h1 != 0)
        {
            tr.pre[h1] = tr.pre[head];
            heap.push(h1);
        }

        if (tr.jdx[head] + 1 < std::ssize(arr[tr.idx[head]]))
        {
            int h2 = tr.merge(h1, tr.new_node(tr.idx[head], tr.jdx[head] + 1, arr[tr.idx[head]]));
            tr.pre[h2] = ans.back();
            heap.push(h2);
        }
    }

    for (int i = 0; i < std::ssize(ans); ++i)
    {
        std::cout << ans[i] << " \n"[i == std::ssize(ans) - 1];
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
