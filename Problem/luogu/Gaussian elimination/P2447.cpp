#include <bits/stdc++.h>

const int MAXN = 2010;
std::bitset<MAXN> mat[MAXN];
int n, m, s, need;

void gauss(int n)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = i; j <= n; j++)
        {
            if (mat[j][i] == 1)
            {
                std::swap(mat[i], mat[j]);
                
                need = std::max(need, j);
                break;
            }
        }

        if (mat[i][i] == 0)
        {
            return;
        }

        for (int j = 1; j <= n; j++)
        {
            if (j != i && mat[j][i] == 1)
            {
                for (int k = i; k <= n + 1; k++)
                {
                    if (mat[i][k] == 1)
                    {
                        mat[j][k].flip();
                    }
                }
            }
        }
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::cin >> n >> m;
    s = std::max(n, m);

    for (int i = 1, status; i <= m; i++)
    {
        std::string str;
        std::cin >> str;
        for (int j = 1; j <= n; j++)
        {
            mat[i][j] = str[j - 1] - '0';
        }

        std::cin >> status;
        mat[i][s + 1] = status;
    }

    gauss(s);

    int sign = 1;
    for (int i = 1; i <= n; i++)
    {
        if (mat[i][i] == 0)
        {
            sign = 0;
            break;
        }
    }

    if (sign == 0)
    {
        std::cout << "Cannot Determine\n";
    }
    else
    {
        std::cout << need << "\n";
        for (int i = 1; i <= n; i++)
        {
            if (mat[i][s + 1] == 1)
            {
                std::cout << "?y7M#\n";
            }
            else
            {
                std::cout << "Earth\n";
            }
        }
    }
}