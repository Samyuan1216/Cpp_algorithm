// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int fieldOfGreatestBlessing(vector<vector<int>>& forceField)
    {
        int n = forceField.size();

        vector<long long> xs(n << 1), ys(n << 1);
        for (int i = 0, k = 0, p = 0; i < n; i++)
        {
            long long x = forceField[i][0];
            long long y = forceField[i][1];
            long long r = forceField[i][2];

            xs[k++] = (x << 1) + r;
            xs[k++] = (x << 1) - r;
            ys[p++] = (y << 1) + r;
            ys[p++] = (y << 1) - r;
        }

        int sizex = sort_a(xs);
        int sizey = sort_a(ys);

        vector<vector<int>> diff(sizex + 2, vector<int>(sizey + 2));
        for (int i = 0, a = 0, b = 0, c = 0, d = 0; i < n; i++)
        {
            long long x = forceField[i][0];
            long long y = forceField[i][1];
            long long r = forceField[i][2];

            a = rank(xs, (x << 1) - r, sizex);
            b = rank(ys, (y << 1) - r, sizey);
            c = rank(xs, (x << 1) + r, sizex);
            d = rank(ys, (y << 1) + r, sizey);

            add(diff, a, b, c, d);
        }

        int ans = 0;
        for (int i = 1; i < diff.size(); i++)
        {
            for (int j = 1; j < diff[0].size(); j++)
            {
                diff[i][j] += diff[i - 1][j] + diff[i][j - 1] - diff[i - 1][j - 1];
                ans = max(ans, diff[i][j]);
            }
        }

        return ans;
    }

    int sort_a(vector<long long> &num)
    {
        sort(num.begin(), num.end());

        int size = 1;
        for (int i = 1; i < num.size(); i++)
        {
            if (num[i] != num[size - 1])
            {
                num[size++] = num[i];
            }
        }

        return size;
    }

    int rank(vector<long long> &num, long long v, int size)
    {
        int l = 0, r = size - 1;
        int m = 0, ans = 0;
        while (l <= r)
        {
            m = (l + r) / 2;
            
            if (num[m] >= v)
            {
                ans = m;
                r = m - 1;
            }
            else
            {
                l = m + 1;
            }
        }

        return ans + 1;
    }

    void add(vector<vector<int>> &diff, int a, int b, int c, int d)
    {
        diff[a][b] += 1;
        diff[c + 1][d + 1] += 1;
        diff[c + 1][b] -= 1;
        diff[a][d + 1] -= 1;
    }
};
// @lc code=end