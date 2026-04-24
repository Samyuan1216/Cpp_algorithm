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
    std::vector<i64> attack, add, mul;
    std::vector<int> left, right, dist;

    Leftist_Tree(int n, const auto &arr): attack(arr), add(n + 1), mul(n + 1, 1), left(n + 1), right(n + 1), dist(n + 1)
    {
        dist[0] = -1;
    }

    void upgrade(int i, int t, i64 v)
    {
        if (t == 0)
        {
            attack[i] += v, add[i] += v;
        }
        else
        {
            attack[i] *= v, mul[i] *= v, add[i] *= v;
        }
    }

    void down(int i)
    {
        if (mul[i] == 1 && add[i] == 0)
        {
            return;
        }

        int l = left[i], r = right[i];
        if (l != 0)
        {
            attack[l] = attack[l] * mul[i] + add[i];
            mul[l] = mul[l] * mul[i];
            add[l] = add[l] * mul[i] + add[i];
        }

        if (r != 0)
        {
            attack[r] = attack[r] * mul[i] + add[i];
            mul[r] = mul[r] * mul[i];
            add[r] = add[r] * mul[i] + add[i];
        }

        mul[i] = 1, add[i] = 0;
    }

    int merge(int i, int j)
    {
        if (i == 0 || j == 0)
        {
            return i + j;
        }

        if (attack[i] > attack[j])
        {
            std::swap(i, j);
        }

        down(i);
        right[i] = merge(right[i], j);

        if (dist[left[i]] < dist[right[i]])
        {
            std::swap(left[i], right[i]);
        }

        dist[i] = dist[right[i]] + 1;
        return i;
    }

    int pop(int i)
    {
        down(i);
        int res = merge(left[i], right[i]);

        left[i] = right[i] = dist[i] = 0;
        return res;
    }
};

void solve()
{
    int n, m;
    std::cin >> n >> m;

    std::vector<i64> defend(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        std::cin >> defend[i];
    }

    std::vector<int> belong(n + 1), type(n + 1);
    std::vector<i64> gain(n + 1);

    for (int i = 2; i <= n; ++i)
    {
        std::cin >> belong[i] >> type[i] >> gain[i];
    }

    std::vector<i64> arr(m + 1);
    std::vector<int> first(m + 1);

    for (int i = 1; i <= m; ++i)
    {
        std::cin >> arr[i] >> first[i];
    }

    std::vector<int> deep(n + 1);
    deep[1] = 1;

    for (int i = 2; i <= n; ++i)
    {
        deep[i] = deep[belong[i]] + 1;
    }

    Leftist_Tree tr(m, arr);
    std::vector<int> top(n + 1);

    for (int i = 1; i <= m; ++i)
    {
        top[first[i]] = (top[first[i]] == 0? i: tr.merge(top[first[i]], i));
    }

    std::vector<int> die(m + 1), sacrifice(n + 1);
    for (int i = n; i >= 1; --i)
    {
        while (top[i] != 0 && tr.attack[top[i]] < defend[i])
        {
            die[top[i]] = i;
            ++sacrifice[i];

            top[i] = tr.pop(top[i]);
        }

        if (top[i] != 0)
        {
            tr.upgrade(top[i], type[i], gain[i]);
            top[belong[i]] = (top[belong[i]] == 0? top[i]: tr.merge(top[belong[i]], top[i]));
        }
    }

    for (int i = 1; i <= n; ++i)
    {
        std::cout << sacrifice[i] << "\n";
    }

    for (int i = 1; i <= m; ++i)
    {
        std::cout << deep[first[i]] - deep[die[i]] << "\n";
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
