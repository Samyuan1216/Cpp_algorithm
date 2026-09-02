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
    int n, k;
    std::cin >> n >> k;

    if (n == 1)
    {
        std::cout << k << "\n";
        return;
    }

    std::vector<std::vector<int>> sq;
    for (int i = k / n; i >= 0; --i)
    {
        std::vector<int> path{i};
        [&](this auto &&self, int num, int rem) -> void
        {
            if (rem == 0)
            {
                sq.push_back(path);
                for (int j = 0; j < num; ++j)
                {
                    sq.back().push_back(0);
                }

                return;
            }

            if (num == 1)
            {
                sq.push_back(path);
                sq.back().push_back(rem);

                return;
            }

            for (int j = rem / num; j >= 0; --j)
            {
                path.push_back(j);
                self(num - 1, rem - j * num);
                path.pop_back();
            }
        } (n - 1, k - i * n);
    }

    for (auto &line: sq)
    {
        ranges::reverse(line);
    }

    ranges::sort(sq);
    for (auto &line: sq)
    {
        for (int i = 0; i < n; ++i)
        {
            std::cout << line[i] << " \n"[i == n - 1];
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
