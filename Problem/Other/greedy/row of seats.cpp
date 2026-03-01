// https://www.nowcoder.com/share/jump/1961392931766318372549

#include <bits/stdc++.h>

using vi = std::vector<int>;
using vvi = std::vector<vi>;

const int MAXN = 1010;
vvi row(MAXN, vi(2)), col(MAXN, vi(2));
int n, m, k, l, d;

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::cin >> n >> m >> k >> l >> d;
    for (int i = 1; i <= n; i++)
    {
        row[i][1] = col[i][1] = i;
    }

    for (int i = 1, x, y, p, q; i <= d; i++)
    {
        std::cin >> x >> y >> p >> q;
        if (x == p)
        {
            col[std::min(y, q)][0]++;
        }
        else
        {
            row[std::min(x, p)][0]++;
        }
    }

    std::sort(row.begin() + 1, row.begin() + n + 1, [](vi &a, vi &b)
    {
        return a[0] > b[0];
    });

    std::sort(row.begin() + 1, row.begin() + k + 1, [](vi &a, vi &b)
    {
        return a[1] < b[1];
    });

    for (int i = 1; i <= k; i++)
    {
        std::cout << row[i][1] << " \n"[i == k];
    }

    std::sort(col.begin() + 1, col.begin() + m + 1, [](vi &a, vi &b)
    {
        return a[0] > b[0];
    });

    std::sort(col.begin() + 1, col.begin() + l + 1, [](vi &a, vi &b)
    {
        return a[1] < b[1];
    });

    for (int i = 1; i <= l; i++)
    {
        std::cout << col[i][1] << " \n"[i == l];
    }
}