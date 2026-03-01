/*
 * @lc app=leetcode.cn id=699 lang=cpp
 *
 * [699] 掉落的方块
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;

const int MAXN = 2010;
vvi nums(MAXN, vi(3));
vi diff(MAXN);
int idx, info, num;

namespace ST
{
    vi maxa(MAXN << 2), change(MAXN << 2);
    bool upd[MAXN << 2];

    void lazy(int i, int v)
    {
        maxa[i] = v;
        change[i] = v;
        upd[i] = true;
    }

    void up(int i)
    {
        maxa[i] = max(maxa[i << 1], maxa[i << 1 | 1]);
    }

    void down(int i)
    {
        if (upd[i])
        {
            lazy(i << 1, change[i]);
            lazy(i << 1 | 1, change[i]);

            upd[i] = false;
        }
    }

    void build(int l, int r, int i)
    {
        if (l == r)
        {
            maxa[i] = 0;
        }
        else
        {
            int mid = l + ((r - l) >> 1);
            build(l, mid, i << 1);
            build(mid + 1, r, i << 1 | 1);

            up(i);
        }

        change[i] = 0;
        upd[i] = false;
    }

    int query(int &jobl, int &jobr, int l, int r, int i)
    {
        if (l >= jobl && r <= jobr)
        {
            return maxa[i];
        }

        int mid = l + ((r - l) >> 1);
        down(i);

        int ans = 0;
        if (jobl <= mid)
        {
            ans = max(ans, query(jobl, jobr, l, mid, i << 1));
        }

        if (jobr >= mid + 1)
        {
            ans = max(ans, query(jobl, jobr, mid + 1, r, i << 1 | 1));
        }

        return ans;
    }

    void update(int &jobl, int &jobr, int &jobv, int l, int r, int i)
    {
        if (l >= jobl && r <= jobr)
        {
            lazy(i, jobv);
        }
        else
        {
            int mid = l + ((r - l) >> 1);
            down(i);

            if (jobl <= mid)
            {
                update(jobl, jobr, jobv, l, mid, i << 1);
            }
            
            if (jobr >= mid + 1)
            {
                update(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
            }

            up(i);
        }
    }
}

class Solution
{
public:
    vector<int> fallingSquares(vector<vector<int>>& positions)
    {
        build(positions);
        ST::build(1, idx, 1);

        vi ans(positions.size());
        for (int i = 0, v; i < positions.size(); i++)
        {
            v = nums[i][2] + ST::query(nums[i][0], nums[i][1], 1, idx, 1);
            ST::update(nums[i][0], nums[i][1], v, 1, idx, 1);

            num = max(num, v);
            ans[info++] = num;
        }

        return ans;
    }

    void build(vector<vector<int>>& positions)
    {
        idx = 1, info = 0, num = 0;
        for (auto &position: positions)
        {
            diff[idx++] = position[0];
            diff[idx++] = position[0] + position[1];
        }

        sort(diff.begin() + 1, diff.begin() + idx);
        idx = unique(diff.begin() + 1, diff.begin() + idx) - diff.begin() - 1;

        for (int i = 0; i < positions.size(); i++)
        {
            nums[i][0] = fin(positions[i][0]);
            nums[i][1] = fin(positions[i][0] + positions[i][1]) - 1;
            nums[i][2] = positions[i][1];
        }
    }

    int fin(int v)
    {
        int ans = 0;
        for (int l = 1, r = idx, mid; l <= r;)
        {
            mid = l + ((r - l) >> 1);
            if (diff[mid] <= v)
            {
                ans = mid;
                l = mid + 1;
            }
            else
            {
                r = mid - 1;
            }
        }

        return ans;
    }
};
// @lc code=end

