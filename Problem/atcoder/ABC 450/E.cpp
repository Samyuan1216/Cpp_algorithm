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

void solve()
{
    auto X = std::string(), Y = std::string();
    std::cin >> X >> Y;

    constexpr int MAXK = 88;
    constexpr i64 INF = 2e18;

    auto pre_x = std::vector(std::ssize(X) + 1, std::vector<int>(26));
    for (int i = 1; i <= std::ssize(X); ++i)
    {
        for (int c = 0; c < 26; ++c)
        {
            pre_x[i][c] = pre_x[i - 1][c];
        }

        ++pre_x[i][X[i - 1] - 'a'];
    }

    auto pre_y = std::vector(std::ssize(Y) + 1, std::vector<int>(26));
    for (int i = 1; i <= std::ssize(Y); ++i)
    {
        for (int c = 0; c < 26; ++c)
        {
            pre_y[i][c] = pre_y[i - 1][c];
        }

        ++pre_y[i][Y[i - 1] - 'a'];
    }

    auto length = std::vector<i64>(MAXK + 1);
    length[0] = std::ssize(X), length[1] = std::ssize(Y);
    for (int i = 2; i < MAXK; ++i)
    {
        length[i] = std::min(INF, length[i - 1] + length[i - 2]);
    }

    auto pre = std::vector(MAXK, std::vector<i64>(26));
    for (int i = 0; i < 26; ++i)
    {
        char c = i + 'a';

        pre[0][i] = ranges::count(X, c), pre[1][i] = ranges::count(Y, c);
        for (int j = 2; j < MAXK; ++j)
        {
            pre[j][i] = std::min(INF, pre[j - 1][i] + pre[j - 2][i]);
        }
    }

    auto query = [&](this auto &&self, int k, i64 i, int c) -> i64
    {
        if (i == 0)
        {
            return 0;
        }

        if (k == 0)
        {
            return pre_x[i][c];
        }
        else if (k == 1)
        {
            return pre_y[i][c];
        }

        i64 left_cnt = length[k - 1];
        if (i <= left_cnt)
        {
            return self(k - 1, i, c);
        }
        else
        {
            return pre[k - 1][c] + self(k - 2, i - left_cnt, c);
        }
    };

    int q;
    std::cin >> q;

    while (q--)
    {
        char c;
        i64 l, r;
        std::cin >> l >> r >> c;

        std::cout << query(MAXK - 1, r, int(c - 'a')) - query(MAXK - 1, l - 1, int(c - 'a')) << "\n";
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
