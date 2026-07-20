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

template<class R>
struct Mat
{
    using T = typename R::T;

    int n, m;
    std::vector<std::vector<T>> a;

    Mat(int n = 0, int m = 0, T val = R::zero()): n(n), m(m), a(n, std::vector<T>(m, val)) {}

    void eye()
    {
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                a[i][j] = (i == j? R::one(): R::zero());
            }
        }
    }

    Mat operator+(const Mat &b) const
    {
        Mat res(n, m);
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                res.a[i][j] = R::add(a[i][j], b.a[i][j]);
            }
        }

        return res;
    }

    Mat operator*(const Mat &b) const
    {
        Mat res(n, b.m, R::zero());
        for (int i = 0; i < n; ++i)
        {
            for (int k = 0; k < m; ++k)
            {
                if (a[i][k] == R::zero())
                {
                    continue;
                }

                for (int j = 0; j < b.m; ++j)
                {
                    res.a[i][j] = R::add(res.a[i][j], R::mul(a[i][k], b.a[k][j]));
                }
            }
        }

        return res;
    }

    Mat qpow(long long p) const
    {
        Mat res(n, n), base = *this;
        res.eye();

        while (p > 0)
        {
            if (p & 1)
            {
                res = res * base;
            }

            base = base * base;
            p >>= 1;
        }

        return res;
    }
};

void solve()
{
    int n, c, q;
    std::cin >> n >> c >> q;

    std::vector<int> cur_jump(n);
    for (auto &x: cur_jump)
    {
        std::cin >> x;
        --x;
    }

    constexpr i64 INF = 4e18;
    struct R
    {
        using T = i64;

        static T zero() { return INF; }
        static T one() { return 0; }

        static T add(T x, T y)
        {
            return std::min(x, y);
        }

        static T mul(T x, T y)
        {
            if (x >= INF / 2 || y >= INF / 2)
            {
                return INF;
            }

            return x + y;
        }
    };

    std::vector<Mat<R>> cur_mat(n, Mat<R>(c, c));
    for (int i = 0; i < n; ++i)
    {
        for (int u = 0; u < c; ++u)
        {
            for (int v = 0; v < c; ++v)
            {
                std::cin >> cur_mat[i].a[u][v];
            }
        }
    }

    struct Q
    {
        int cur, s, t;
        i64 k;
    };

    std::vector<Q> query(q);
    std::vector<Mat<R>> ans(q, Mat<R>(1, c));

    for (int i = 0; i < q; ++i)
    {
        std::cin >> query[i].cur >> query[i].k >> query[i].s >> query[i].t;
        --query[i].cur;

        ans[i].a[0][query[i].s] = 0;
    }

    std::vector<int> next_jump(n);
    std::vector<Mat<R>> next_mat(n, Mat<R>(c, c));

    constexpr int limit = 30;
    for (int p = 0; p < limit; ++p)
    {
        for (int i = 0; i < q; ++i)
        {
            if ((query[i].k >> p) & 1)
            {
                ans[i] = ans[i] * cur_mat[query[i].cur];
                query[i].cur = cur_jump[query[i].cur];
            }
        }

        if (p < limit - 1)
        {
            for (int i = 0; i < n; ++i)
            {
                next_jump[i] = cur_jump[cur_jump[i]];
                next_mat[i] = cur_mat[i] * cur_mat[cur_jump[i]];
            }

            std::swap(cur_jump, next_jump);
            std::swap(cur_mat, next_mat);
        }
    }

    for (int i = 0; i < q; ++i)
    {
        std::cout << ans[i].a[0][query[i].t] << "\n";
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
