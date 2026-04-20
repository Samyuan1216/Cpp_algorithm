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
    std::vector<int> left, right, dist, father;

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
public:
    Leftist_Tree(int n, const auto &arr): num(arr), left(n + 1), right(n + 1), dist(n + 1), father(n + 1)
    {
        dist[0] = -1;
        ranges::iota(father, 0);
    }

    int fight(int x, int y)
    {
        x = find(x), y = find(y);
        if (x == y)
        {
            return -1;
        }

        int l = pop(x), r = pop(y);
        num[x] /= 2, num[y] /= 2;

        father[x] = father[y] = father[l] = father[r] = merge(merge(l, x), merge(r, y));
        return num[father[x]];
    }
};

void solve(int n)
{
    std::vector<int> arr(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        std::cin >> arr[i];
    }

    Leftist_Tree tr(n, arr);

    int m;
    std::cin >> m;

    while (m--)
    {
        int x, y;
        std::cin >> x >> y;
        std::cout << tr.fight(x, y) << "\n";
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int t = 1;
    while (std::cin >> t)
    {
        solve(t);
    }
}
