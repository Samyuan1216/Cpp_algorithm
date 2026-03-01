#include <bits/stdc++.h>

const int MAXN = 15;
const double SML = 1e-7;
double data[MAXN][MAXN], mat[MAXN][MAXN];
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

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n + 1; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            std::cin >> data[i][j];
        }
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            mat[i][j] = 2 * (data[i][j] - data[i + 1][j]);
            mat[i][n + 1] += std::pow(data[i][j], 2) - std::pow(data[i + 1][j], 2);
        }
    }

    gauss();
    for (int i = 1; i <= n; i++)
    {
        printf("%.3lf%c", mat[i][n + 1], " \n"[i == n]);
    }
}