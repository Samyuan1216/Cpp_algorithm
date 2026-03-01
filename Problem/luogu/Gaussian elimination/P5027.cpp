#include <bits/stdc++.h>

const int MAXN = 110;
const double SML = 1e-7;
int data[MAXN][MAXN];
double mat[MAXN][MAXN];
int n;

void swap(int row1, int row2)
{
    if (row1 == row2)
    {
        return;
    }

    for (int j = 1; j <= n + 1; j++)
    {
        double tmp = mat[row1][j];
        mat[row1][j] = mat[row2][j];
        mat[row2][j] = tmp;
    }
}

void gauss()
{
    for (int i = 1; i <= n; i++)
    {
        int max = i;
        for (int j = 1; j <= n; j++)
        {
            if (j < i && std::abs(mat[j][j]) >= SML)
            {
                continue;
            }

            if (std::abs(mat[j][i]) > std::abs(mat[max][i]))
            {
                max = j;
            }
        }

        swap(i, max);

        if (std::abs(mat[i][i]) >= SML)
        {
            double tmp = mat[i][i];
            for (int j = i; j <= n + 1; j++)
            {
                mat[i][j] /= tmp;
            }

            for (int j = 1; j <= n; j++)
            {
                if (j != i)
                {
                    double rate = mat[j][i] / mat[i][i];
                    for (int k = i; k <= n + 1; k++)
                    {
                        mat[j][k] -= mat[i][k] * rate;
                    }
                }
            }
        }
    }
}

int check()
{
    gauss();

    double maxv = DBL_MIN;
    int maxt = 0, ans = 0;
    for (int i = 1; i <= n; i++)
    {
        if (mat[i][i] == 0)
        {
            return 0;
        }

        if (mat[i][n + 1] <= 0 || mat[i][n + 1] != (int)mat[i][n + 1])
        {
            return 0;
        }

        if (maxv < mat[i][n + 1])
        {
            maxv = mat[i][n + 1];
            maxt = 1;
            ans = i;
        }
        else if (maxv == mat[i][n + 1])
        {
            maxt++;
        }
    }

    if (maxt > 1)
    {
        return 0;
    }

    return ans;
}

void swap_data(int row1, int row2)
{
    if (row1 == row2)
    {
        return;
    }

    for (int j = 1; j <= n + 1; j++)
    {
        double tmp = data[row1][j];
        data[row1][j] = data[row2][j];
        data[row2][j] = tmp;
    }
}

int main()
{
    scanf("%d", &n);
    for (int i = 1, m; i <= n + 1; i++)
    {
        scanf("%d", &m);
        for (int j = 1, cur; j <= m; j++)
        {
            scanf("%d", &cur);

            data[i][cur] = 1;
        }

        scanf("%d", &data[i][n + 1]);
    }

    int ans = 0, times = 0;
    for (int k = 1; k <= n + 1; k++)
    {
        swap_data(k, n + 1);
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n + 1; j++)
            {
                mat[i][j] = data[i][j];
            }
        }

        swap_data(k, n + 1);

        int cur = check();
        if (cur != 0)
        {
            times++;
            ans = cur;
        }
    }

    if (times != 1)
    {
        printf("illegal\n");
    }
    else
    {
        printf("%d\n", ans);
    }
}