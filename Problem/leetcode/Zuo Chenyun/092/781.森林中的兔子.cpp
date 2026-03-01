/*
 * @lc app=leetcode.cn id=781 lang=cpp
 *
 * [781] 森林中的兔子
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int numRabbits(vector<int>& answers)
    {
        sort(answers.begin(), answers.end());

        int n = answers.size(), ans = 0;
        for (int i = 0, j = 1, x; i < n; j++)
        {
            x = answers[i];
            while (j < n && answers[j] == x)
            {
                j++;
            }

            ans += (j - i + x) / (x + 1) * (x + 1);
            i = j;
        }

        return ans;
    }
};
// @lc code=end

