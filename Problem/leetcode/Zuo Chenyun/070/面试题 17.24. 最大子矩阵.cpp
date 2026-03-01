// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<int> getMaxMatrix(vector<vector<int>>& matrix)
    {
        int n = matrix.size(), m = matrix[0].size();
        vector<int> ans(4), cur(m);

        int maxn = INT32_MIN;
        for (int i = 0; i < n; i++)
        {
            fill(cur.begin(), cur.end(), 0);
            for (int j = i; j < n; j++)
            {
                for (int l = 0, r = 0, pre = INT32_MIN; r < m; r++)
                {
					cur[r] += matrix[j][r];
					if (pre >= 0)
                    {
						pre += cur[r];
					}
                    else
                    {
						pre = cur[r];
						l = r;
					}
					if (pre > maxn)
                    {
						maxn = pre;
						ans[0] = i;
						ans[1] = l;
						ans[2] = j;
						ans[3] = r;
					}
				}
            }
        }

        return ans;
    }
};
// @lc code=end