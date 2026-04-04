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
    std::vector<int> num;
    std::vector<int> left;
    std::vector<int> right;
    std::vector<int> dist;
    std::vector<int> father;

    int find(int i)
    {
        father[i] = (father[i] == i? i: find(father[i]));
        return father[i];
    }

    int merge(int i, int j, int)
    {
        if (i == 0 || j == 0)
        {
            return i + j;
        }

        if (num[i] > num[j] || (num[i] == num[j] && i > j))
        {
            std::swap(i, j);
        }

        right[i] = merge(right[i], j, 0);
        if (dist[left[i]] < dist[right[i]])
        {
            std::swap(left[i], right[i]);
        }

        dist[i] = dist[right[i]] + 1;
        father[left[i]] = father[right[i]] = i;

        return i;
    }

    int pop(int i, int)
    {
        father[left[i]] = left[i], father[right[i]] = right[i];
        father[i] = merge(left[i], right[i], 0);
        left[i] = right[i] = dist[i] = 0;

        return father[i];
    }
public:
    Leftist_Tree(const auto &arr, int n): num(arr), left(n + 1), right(n + 1), dist(n + 1), father(n + 1)
    {
        dist[0] = -1;
        ranges::iota(father, 0);
    }

    void merge(int i, int j)
    {
        if ((num[i] == -1 || num[j] == -1) || (find(i) == find(j)))
        {
            return;
        }

        merge(find(i), find(j), 0);
    }

    int pop(int i)
    {
        if (num[i] == -1)
        {
            return -1;
        }

        int x = find(i), ans = num[x];
        pop(x, 0);

        num[x] = -1;
        return ans;
    }
};

void solve()
{
    int n, m;
    std::cin >> n >> m;

    auto arr = std::vector<int>(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        std::cin >> arr[i];
    }

    auto tr = Leftist_Tree(arr, n);
    while (m--)
    {
        int op;
        std::cin >> op;

        if (op == 1)
        {
            int x, y;
            std::cin >> x >> y;

            tr.merge(x, y);
        }
        else
        {
            int x;
            std::cin >> x;

            std::cout << tr.pop(x) << "\n";
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
