#include <bits/stdc++.h>

const int MAXN = 110;
const double SML = 1e-7;
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

bool gauss()
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

        if (std::abs(mat[i][i]) < SML)
        {
            return false;
        }

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

    return true;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n + 1; j++)
        {
            scanf("%lf", &mat[i][j]);
        }
    }

    if (gauss())
    {
        for (int i = 1; i <= n; i++)
        {
            printf("%.2lf\n", mat[i][n + 1]);
        }
    }
    else
    {
        printf("No Solution\n");
    }
}