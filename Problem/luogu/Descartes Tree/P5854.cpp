#include <bits/extc++.h>
namespace ranges = std::ranges;

using i64 = int64_t;

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

template<typename T = int>
class Descartes_Tree
{
    const std::vector<T> &arr;
    std::vector<int> lc;
    std::vector<int> rc;
    std::vector<int> stk;
    int n;
public:
    int root = 0;

    Descartes_Tree(const std::vector<T> &input, int size): arr(input), lc(size + 1), rc(size + 1), stk(size + 1), n(size)
    {
        for (int i = 1, top = 0, pos = 0; i <= n; ++i)
        {
            pos = top;
            while (pos > 0 && arr[stk[pos]] > arr[i])
            {
                --pos;
            }

            if (pos > 0)
            {
                rc[stk[pos]] = i;
            }

            if (pos < top)
            {
                lc[i] = stk[pos + 1];
            }

            stk[++pos] = i;
            top = pos;
        }

        if (n > 0)
        {
            root = stk[1];
        }
    }

    int left(int u) const
    {
        return lc[u];
    }

    int right(int u) const
    {
        return rc[u];
    }
};

void solve()
{
    int n;
    std::cin >> n;

    std::vector<int> arr(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        std::cin >> arr[i];
    }

    Descartes_Tree tree(arr, n);

    i64 ans1 = 0, ans2 = 0;
    for (int i = 1; i <= n; ++i)
    {
        ans1 ^= i64(i) * (tree.left(i) + 1);
        ans2 ^= i64(i) * (tree.right(i) + 1);
    }

    std::cout << ans1 << " " << ans2 << "\n";
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
