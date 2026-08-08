#include <bits/extc++.h>
namespace ranges = std::ranges;

using i64 = long long;

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

    std::vector<i64> arr(n);
    for (auto &x: arr)
    {
        std::cin >> x;
    }

    auto g = std::vector(n, std::vector<i64>(m));
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            std::cin >> g[i][j];
        }

        ranges::sort(g[i], std::greater());
    }

    std::priority_queue<i64, std::vector<i64>, std::greater<>> heap;
    i64 sum = 0, size = m;

    for (int i = 0; i < m; ++i)
    {
        sum += g[n - 1][i];
        heap.push(g[n - 1][i]);

        if (sum >= arr[n - 1])
        {
            size = i + 1;
            break;
        }
    }

    for (int i = n - 2; i >= 0; --i)
    {
        for (int j = 0; j < m; ++j)
        {
            if (g[i][j] > heap.top())
            {
                sum -= heap.top();
                heap.pop();

                heap.push(g[i][j]);
                sum += g[i][j];
            }
        }

        if (sum >= arr[i])
        {
            while (sum - heap.top() >= arr[i])
            {
                sum -= heap.top();
                heap.pop();

                --size;
            }
        }
    }

    std::cout << size << "\n";
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
