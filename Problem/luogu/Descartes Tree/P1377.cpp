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
            while (pos > 0 && arr[stack[pos]] > arr[i])
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
    for (int i = 1, x; i <= n; ++i)
    {
        std::cin >> x;

        arr[x] = i;
    }

    Descartes_Tree tree(arr, n);
    auto dfs = [&](auto &&self, int u) -> void
    {
        if (u == 0)
        {
            return;
        }

        std::cout << u << " ";
        self(self, tree.left[u]);
        self(self, tree.right[u]);
    };

    dfs(dfs, tree.root);
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
