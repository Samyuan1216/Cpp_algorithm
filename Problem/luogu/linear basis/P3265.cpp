#include <bits/stdc++.h>

using vi = std::vector<int>;
using vd = std::vector<double>;
using v2d = std::vector<vd>;

const int MAXN = 510;
const double SML = 1e-5;
v2d mat(MAXN, vd(MAXN));
vi basis(MAXN);
int n, m, cnt, cost;

bool insert(int i)
{
    for (int j = 1; j <= m; j++)
    {
        if (std::abs(mat[i][j]) >= SML)
        {
            if (basis[j] == 0)
            {
                basis[j] = i;
                return true;
            }
        }

        double rate = mat[i][j] / mat[basis[j]][j];
        for (int k = j; k <= m; k++)
        {
            mat[i][k] -= mat[basis[j]][k] * rate;
        }
    }

    return false;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            std::cin >> mat[i][j];
        }
    }

    for (int i = 1; i <= n; i++)
    {
        std::cin >> mat[i][m + 1];
    }

    std::sort(mat.begin() + 1, mat.begin() + n + 1, [](vd &a, vd &b)
    {
        return a[m + 1] < b[m + 1];
    });

    for (int i = 1; i <= n; i++)
    {
        if (insert(i))
        {
            cnt++;
            cost += (int)mat[i][m + 1];
        }
    }

    std::cout << cnt << " " << cost << "\n";
}