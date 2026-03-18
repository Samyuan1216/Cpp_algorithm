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

template<typename T = int, typename Cmp = std::less<T>>
class Descartes_Tree
{
    Cmp compare;
public:
    const std::vector<T> &arr;
    std::vector<int> left;
    std::vector<int> right;
    std::vector<int> stack;
    int n;
    int root = 0;

    Descartes_Tree(const std::vector<T> &input, int size): arr(input), left(size + 1), right(size + 1), stack(size + 1), n(size)
    {
        for (int i = 1, top = 0, pos = 0; i <= n; ++i)
        {
            pos = top;
            while (pos > 0 && compare(arr[stack[pos]], arr[i]))
            {
                --pos;
            }

            if (pos > 0)
            {
                right[stack[pos]] = i;
            }

            if (pos < top)
            {
                left[i] = stack[pos + 1];
            }

            stack[++pos] = i;
            top = pos;
        }

        if (n > 0)
        {
            root = stack[1];
        }
    }
};

void solve()
{
    int n;
    std::cin >> n;

    auto arr = std::vector<int>(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        std::cin >> arr[i];
    }

    auto tr = Descartes_Tree(arr, n);
    int max_depth = 0;

    auto dfs = [&](auto &&self, int u, int d) -> void
    {
        if (u == 0)
        {
            max_depth = std::max(max_depth, d);
            return;
        }

        self(self, tr.left[u], d + 1);
        self(self, tr.right[u], d + 1);
    };

    dfs(dfs, tr.root, 0);

    std::cout << n - max_depth << "\n";
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int t = 1;
    std::cin >> t;
    while (t--)
    {
        solve();
    }
}
