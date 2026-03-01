#include <bits/stdc++.h>

const int MAXN = 110;
int mat[MAXN][MAXN];

void gauss(int n)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (j < i && mat[j][j] == 1)
            {
                continue;
            }

            if (mat[j][i] == 1)
            {
                std::swap(mat[i], mat[j]);
                break;
            }
        }

        if (mat[i][i] == 1)
        {
            for (int j = 1; j <= n; j++)
            {
                if (i != j && mat[j][i] == 1)
                {
                    for (int k = i; k <= n + 1; k++)
                    {
                        mat[j][k] ^= mat[i][k];
                    }
                }
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
    std::cout << "课上图解的例子，有唯一解" << "\n";
    // x1 ^ x2 ^ x3 = 0
    // x1 ^ x3 ^ x4 = 1
    // x2 ^ x3 ^ x4 = 1
    // x3 ^ x4 = 0
    mat[1][1] = 1; mat[1][2] = 1; mat[1][3] = 1; mat[1][4] = 0; mat[1][5] = 0;
    mat[2][1] = 1; mat[2][2] = 0; mat[2][3] = 1; mat[2][4] = 1; mat[2][5] = 1;
    mat[3][1] = 0; mat[3][2] = 1; mat[3][3] = 1; mat[3][4] = 1; mat[3][5] = 1;
    mat[4][1] = 0; mat[4][2] = 0; mat[4][3] = 1; mat[4][4] = 1; mat[4][5] = 0;
    gauss(4);
    print(4);

    std::cout << "表达式存在矛盾的例子" << "\n";
    // x1 ^ x2 = 1
    // x1 ^ x3 = 1
    // x2 ^ x3 = 1
    mat[1][1] = 1; mat[1][2] = 1; mat[1][3] = 0; mat[1][4] = 1;
    mat[2][1] = 1; mat[2][2] = 0; mat[2][3] = 1; mat[2][4] = 1;
    mat[3][1] = 0; mat[3][2] = 1; mat[3][3] = 1; mat[3][4] = 1;
    gauss(3);
    print(3);

    std::cout << "表达式存在多解的例子" << "\n";
    // x1 ^ x3 = 1
    // x2 ^ x3 = 1
    // x1 ^ x2 = 0
    mat[1][1] = 1; mat[1][2] = 0; mat[1][3] = 1; mat[1][4] = 1;
    mat[2][1] = 0; mat[2][2] = 1; mat[2][3] = 1; mat[2][4] = 1;
    mat[3][1] = 1; mat[3][2] = 1; mat[3][3] = 0; mat[3][4] = 0;
    mat[4][1] = 1; mat[4][2] = 1; mat[4][3] = 0; mat[4][4] = 0;
    gauss(3);
    print(3);

    std::cout << "注意下面这个多解的例子" << "\n";
    // x1 ^ x3 ^ x4 = 0
    // x2 ^ x3 ^ x4 = 0
    // x1 ^ x2 = 0
    // x3 ^ x4 = 1
    mat[1][1] = 1; mat[1][2] = 0; mat[1][3] = 1; mat[1][4] = 1; mat[1][5] = 0;
    mat[2][1] = 0; mat[2][2] = 1; mat[2][3] = 1; mat[2][4] = 1; mat[2][5] = 0;
    mat[3][1] = 1; mat[3][2] = 1; mat[3][3] = 0; mat[3][4] = 0; mat[3][5] = 0;
    mat[4][1] = 0; mat[4][2] = 0; mat[4][3] = 1; mat[4][4] = 1; mat[4][5] = 1;
    gauss(4);
    print(4);
    std::cout << "最后一个例子里" << "\n";
    std::cout << "主元x1和x2，不受其他自由元影响，值可以直接确定" << "\n";
    std::cout << "但是主元x3，受到自由元x4的影响，x3 ^ x4 = 1" << "\n";
    std::cout << "只有自由元x4确定了值，主元x3的值才能确定" << "\n";
    std::cout << "这里是想说，消元完成后，如果结论是多解，那么" << "\n";
    std::cout << "有些主元的值可以直接确定" << "\n";
    std::cout << "有些主元的值需要若干自由元确定之后才能确定" << "\n";
    std::cout << "这就是上节课，也就是讲解133讲的：" << "\n";
    std::cout << "主元和自由元之间的依赖关系" << "\n";
    std::cout << "请确保已经掌握" << "\n";

    return 0;
}