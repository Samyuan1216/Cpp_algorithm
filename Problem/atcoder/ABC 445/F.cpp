#include <bits/stdc++.h>
#include <bits/extc++.h>
namespace ranges = std::ranges;
namespace views = std::views;

using i64 = int64_t;
using i128 = __int128;
using u64 = uint64_t;
using u128 = unsigned __int128;
using f64 = double;
using f128 = long double;

template<typename T>
using lim = std::numeric_limits<T>;

#ifndef DEBUG
struct __X
{
    __X& operator<<(const auto& str) {return *this;}
    void sp([[maybe_unused]] const std::string& str = "") {}
} dout;
#define debug(x)
#endif

void solve()
{
    auto mat_mul = []<typename T>(const std::vector<std::vector<T>> &a, const std::vector<std::vector<T>> &b)
    {
        int n = a.size(), t = a[0].size(), m = b[0].size();
        std::vector<std::vector<T>> ans(n, std::vector<T>(m, lim<T>::max()));

        for (int i = 0; i < n; ++i)
        {
            for (int k = 0; k < t; ++k)
            {
                T aik =  a[i][k];
                if (aik == lim<T>::max())
                {
                    continue;
                }

                for (int j = 0; j < m; ++j)
                {
                    if (b[k][j] == lim<T>::max())
                    {
                        continue;
                    }

                    ans[i][j] = std::min(ans[i][j], aik + b[k][j]);
                }
            }
        }
    
        return ans;
    };

    auto mat_power = [&]<typename T>(std::vector<std::vector<T>> mat, int n)
    {
        int size = mat.size();
        std::vector<std::vector<T>> ans(size, std::vector<T>(size, lim<T>::max()));
        for (int i = 0; i < size; ++i)
        {
            ans[i][i] = T(0);
        }
    
        while (n > 0)
        {
            if (n & 1)
            {
                ans = mat_mul(ans, mat);
            }
    
            mat = mat_mul(mat, mat);
            n >>= 1;
        }
    
        return ans;
    };

    int n, k;
    std::cin >> n >> k;

    std::vector<std::vector<i64>> mat(n, std::vector<i64>(n));
    for (auto &line: mat)
    {
        for (auto &x: line)
        {
            std::cin >> x;
        }
    }

    auto ans = mat_power(mat, k);
    for (int i = 0; i < n; i++)
    {
        std::cout << ans[i][i] << "\n";
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
