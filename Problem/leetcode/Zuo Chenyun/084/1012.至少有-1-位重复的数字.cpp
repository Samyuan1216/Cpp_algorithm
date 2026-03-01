/*
 * @lc app=leetcode.cn id=1012 lang=cpp
 *
 * [1012] 至少有 1 位重复的数字
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int numDupDigitsAtMostN(int n)
    {
        return n - countSpecialNumbers(n);
    }

    int countSpecialNumbers(int n)
    {
        int len = 1, offset = 1, tmp = n / 10;
        while (tmp > 0)
        {
            len++;
            offset *= 10;
            tmp /= 10;
        }

        vector<int> cnt(len);
        cnt[0] = 1;
        for (int i = 1, k = 10 - len + 1; i < len; k++, i++)
        {
            cnt[i] = cnt[i - 1] * k;
        }

        int ans = 0;
        if (len >= 2)
        {
            ans = 9;
            for (int i = 2, a = 9, b = 9; i < len; i++, b--)
            {
                a *= b;
                ans += a;
            }
        }

        int first = n / offset;
        ans += (first - 1) * cnt[len - 1];
        ans += f(cnt, n, len - 1, offset / 10, 1 << first);

        return ans;
    }

    int f(vector<int> & cnt, int num, int len, int offset, int status)
    {
        if (len == 0)
        {
            return 1;
        }

        int ans = 0;
        int first = (num / offset) % 10;
        for (int cur = 0; cur < first; cur++)
        {
            if ((status & (1 << cur)) == 0)
            {
                ans += cnt[len - 1];
            }
        }

        if ((status & (1 << first)) == 0)
        {
            ans += f(cnt, num, len - 1, offset / 10, status | (1 << first));
        }

        return ans;
    }
};
// @lc code=end

