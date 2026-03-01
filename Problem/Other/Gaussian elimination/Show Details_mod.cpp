#include <bits/stdc++.h>

using ll = long long;

const int MOD = 7;
const int MAXN = 101;
int mat[MAXN][MAXN], inv[MOD];

void build_inv()
{
    inv[1] = 1;
    for (int i = 2; i < MOD; i++)
    {
        inv[i] = (int)(MOD - (ll)inv[MOD % i] * (MOD / i) % MOD);
    }
}

int gcd(int a, int b)
{
    return (b == 0 ? a : gcd(b, a % b));
}

void gauss(int n)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (j < i && mat[j][j] != 0)
            {
                continue;
            }

            if (mat[j][i] != 0)
            {
                std::swap(mat[i], mat[j]);
                break;
            }
        }

        if (mat[i][i] != 0)
        {
            for (int j = 1; j <= n; j++)
            {
                if (i != j && mat[j][i] != 0)
                {
                    int g = gcd(mat[j][i], mat[i][i]);
                    int a = mat[i][i] / g, b = mat[j][i] / g;
                    if (j < i && mat[j][j] != 0)
                    {
                        for (int k = j; k < i; k++)
                        {
                            mat[j][k] = (mat[j][k] * a) % MOD;
                        }
                    }

                    for (int k = i; k <= n + 1; k++)
                    {
                        mat[j][k] = ((mat[j][k] * a - mat[i][k] * b) % MOD + MOD) % MOD;
                    }
                }
            }
        }
    }

    for (int i = 1; i <= n; i++)
    {
        if (mat[i][i] != 0)
        {
            bool flag = false;
            for (int j = i + 1; j <= n; j++)
            {
                if (mat[i][j] != 0)
                {
                    flag = true;
                    break;
                }
            }

            if (!flag)
            {
                mat[i][n + 1] = (mat[i][n + 1] * inv[mat[i][i]]) % MOD;
                mat[i][i] = 1;
            }
        }
    }
}

void print(int n)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n + 1; j++)
        {
            std::cout << mat[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "========================" << "\n";
}

int main()
{
    build_inv();
    
    std::cout << "课上图解的例子，唯一解" << "\n";
    // 4*x1 + 2*x2 + 4*x3 同余 3
    // 2*x1 + 5*x2 + 2*x3 同余 2
    // 6*x1 + 3*x2 + 4*x3 同余 5
    mat[1][1] = 4; mat[1][2] = 2; mat[1][3] = 4; mat[1][4] = 3;
    mat[2][1] = 2; mat[2][2] = 5; mat[2][3] = 2; mat[2][4] = 2;
    mat[3][1] = 6; mat[3][2] = 3; mat[3][3] = 4; mat[3][4] = 5;
    gauss(3);
    print(3);

    std::cout << "表达式存在矛盾的例子" << "\n";
    // 1*x1 + 2*x2 + 3*x3 同余 2
    // 2*x1 + 4*x2 + 6*x3 同余 5
    // 0*x1 + 3*x2 + 4*x3 同余 2
    mat[1][1] = 1; mat[1][2] = 2; mat[1][3] = 3; mat[1][4] = 2;
    mat[2][1] = 2; mat[2][2] = 4; mat[2][3] = 6; mat[2][4] = 5;
    mat[3][1] = 0; mat[3][2] = 3; mat[3][3] = 4; mat[3][4] = 2;
    gauss(3);
    print(3);

    std::cout << "课上图解的例子，多解" << "\n";
    std::cout << "只有确定了自由元，才能确定主元的值" << "\n";
    std::cout << "如果是多解的情况，那么在消元结束后" << "\n";
    std::cout << "二维矩阵中主元和自由元的关系是正确的" << "\n";
    std::cout << "课上也进行了验证" << "\n";
    // 1*x1 + 2*x2 + 3*x3 同余 2
    // 2*x1 + 4*x2 + 6*x3 同余 4
    // 0*x1 + 3*x2 + 4*x3 同余 2
    mat[1][1] = 1; mat[1][2] = 2; mat[1][3] = 3; mat[1][4] = 2;
    mat[2][1] = 2; mat[2][2] = 4; mat[2][3] = 6; mat[2][4] = 4;
    mat[3][1] = 0; mat[3][2] = 3; mat[3][3] = 4; mat[3][4] = 2;
    gauss(3);
    print(3);

    std::cout << "注意下面这个多解的例子" << "\n";
    // 1*x1 + 1*x2 + 1*x3 同余 3
    // 2*x1 + 1*x2 + 1*x3 同余 5
    // 0*x1 + 3*x2 + 3*x3 同余 3
    mat[1][1] = 1; mat[1][2] = 1; mat[1][3] = 1; mat[1][4] = 3;
    mat[2][1] = 2; mat[2][2] = 1; mat[2][3] = 1; mat[2][4] = 5;
    mat[3][1] = 0; mat[3][2] = 3; mat[3][3] = 3; mat[3][4] = 3;
    gauss(3);
    print(3);
    
    std::cout << "最后一个例子里" << "\n";
    std::cout << "主元x1，不受其他自由元影响，值可以直接确定" << "\n";
    std::cout << "但是主元x2，受到自由元x3的影响，6*x2 + 6*x3 同余 6" << "\n";
    std::cout << "只有自由元x3确定了值，主元x2的值才能确定" << "\n";
    std::cout << "本节课提供的模版，对于能求出的主元可以得到正确结果" << "\n";
    std::cout << "对于不能求出的主元，该模版也能给出，主元和自由元的正确关系" << "\n";
    std::cout << "有些题目需要这种多解情况下，主元和自由元之间的正确关系" << "\n";
    std::cout << "绝大多数模版和讲解都没有考虑这个，但值得引起重视" << "\n";
    std::cout << "如果有些题目不需要这种正确关系" << "\n";
    std::cout << "那么逻辑可以化简，让常数时间更快，比如本节课的题目1" << "\n";
    
    return 0;
}