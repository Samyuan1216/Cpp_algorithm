/*
 * @lc app=leetcode.cn id=3031 lang=cpp
 *
 * [3031] 将单词恢复初始状态所需的最短时间 II
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

class Solution
{
public:
    int minimumTimeToInitialState(string word, int k)
    {
        int n = word.length();
        vi z(n);

        int ans = (n + k - 1) / k;
        z[0] = n;
        for (int i = 1, r = 1, c = 1, len; i < n; i++)
        {
            len = (i < r? min(r - i, z[i - c]): 0);
            while (i + len < n && word[i + len] == word[len])
            {
                len++;
            }

            if (i + len > r)
            {
                r = i + len;
                c = i;
            }

            z[i] = len;

            if (i % k == 0 && z[i] == n - i)
            {
                ans = i / k;
                break;
            }
        }

        return ans;
    }
};
// @lc code=end

