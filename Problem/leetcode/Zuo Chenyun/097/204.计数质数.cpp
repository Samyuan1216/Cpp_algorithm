/*
 * @lc app=leetcode.cn id=204 lang=cpp
 *
 * [204] 计数质数
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int countPrimes(int n)
    {
        return ehrlich2(n - 1);
    }

    int ehrlich(int n)
    {
        vector<int> visited(n + 1);
        for (int i = 2; i * i <= n; i++)
        {
            if (visited[i] == 0)
            {
                for (int j = i * i; j <= n; j += i)
                {
                    visited[j] = 1;
                }
            }
        }

        int cnt = 0;
        for (int i = 2; i <= n; i++)
        {
            if (visited[i] == 0)
            {
                cnt++;
            }
        }

        return cnt;
    }

    int euler(int n)
    {
        vector<int> visited(n + 1), prime(n / 2 + 1);
        int cnt = 0;

        for (int i = 2; i <= n; i++)
        {
            if (visited[i] == 0)
            {
                prime[cnt++] = i;
            }

            for (int j = 0; j < cnt; j++)
            {
                if (i * prime[j] > n)
                {
                    break;
                }

                visited[i * prime[j]] = 1;
                if (i % prime[j] == 0)
                {
                    break;
                }
            }
        }

        return cnt;
    }

    int ehrlich2(int n)
    {
        if (n <= 1)
        {
            return 0;
        }

        vector<int> visited(n + 1);
        int cnt = (n + 1) / 2;

        for (int i = 3; i * i <= n; i += 2)
        {
            if (visited[i] == 0)
            {
                for (int j = i * i; j <= n; j += 2 * i)
                {
                    if (visited[j] == 0)
                    {
                        visited[j] = 1;
                        cnt--;
                    }
                }
            }
        }

        return cnt;
    }
};
// @lc code=end

