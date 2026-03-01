#include <bits/stdc++.h>

const int MAXN = 1000010, MAXM = 1010, NA = INT32_MAX;
int next[MAXN][26], right[26], dp[MAXM][MAXM];
std::string str1, str2;
int n, m;

int lcs1()
{
    int dp[n + 1][m + 1];
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= m; j++)
        {
            dp[i][j] = 0;
        }
    }
    
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (str1[i - 1] == str2[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else
            {
                dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    return dp[n][m];
}

void build()
{
    for (int i = 0; i < 26; i++)
    {
        right[i] = NA;
    }

    for (int i = n; i >= 0; i--)
    {
        for (int j = 0; j < 26; j++)
        {
            next[i][j] = right[j];
        }

        if (i > 0)
        {
            right[str1[i - 1] - 'a'] = i;
        }
    }

    for (int i = 0; i <= m; i++)
    {
        for (int j = 0; j <= m; j++)
        {
            dp[i][j] = -1;
        }
    }
}

int dfs(int i, int j)
{
    if (i < j)
    {
        return NA;
    }

    if (j == 0)
    {
        return 0;
    }

    if (dp[i][j] != -1)
    {
        return dp[i][j];
    }

    int cha = str2[i - 1] - 'a';
    int ans = dfs(i - 1, j);
    int pre = dfs(i - 1, j - 1);
    if (pre != NA)
    {
        ans = std::min(ans, next[pre][cha]);
    }

    dp[i][j] = ans;
    return ans;
}

int lcs2()
{
    build();

    int ans = 0;
    for (int i = m; i >= 1; i--)
    {
        if (dfs(m, i) != NA)
        {
            ans = i;
            break;
        }
    }

    return ans;
}

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution dis1(0, 25), dis2(1, 101);

std::string random_string(int n)
{
    std::string str;
    for (int i = 0; i < n; i++)
    {
        str += (char)(dis1(gen) + 'a');
    }

    return str;
}

int main()
{
    int test_time = 10000;
    
    std::cout << "测试开始" << std::endl;
    for (int i = 1; i <= test_time; i++)
    {
        n = dis2(gen), m = dis2(gen);
        str1 = random_string(n), str2 = random_string(m);

        int ans1 = lcs1(), ans2 = lcs2();
        if (ans1 != ans2)
        {
            std::cout << "出错了" << std::endl;
            std::cout << ans1 << " " << ans2 << std::endl;

            break;
        }
    }
    std::cout << "测试结束" << std::endl;
}