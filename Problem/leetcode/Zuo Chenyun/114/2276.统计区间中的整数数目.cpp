/*
 * @lc app=leetcode.cn id=2276 lang=cpp
 *
 * [2276] 统计区间中的整数数目
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

const int MAXN = 700010;
vi le(MAXN), ri(MAXN), sum(MAXN);
int cnt = 1, n = 1000000000;

class CountIntervals
{
public:
    CountIntervals()
    {
        fill(le.begin() + 1, le.begin() + cnt + 1, 0);
        fill(ri.begin() + 1, ri.begin() + cnt + 1, 0);
        fill(sum.begin() + 1, sum.begin() + cnt + 1, 0);

        cnt = 1;
    }

    void up(int i, int l, int r)
    {
        sum[i] = sum[l] + sum[r];
    }

    void set_one(int jobl, int jobr, int l, int r, int i)
    {
        if (sum[i] == r - l + 1)
        {
            return;
        }

        if (l >= jobl && r <= jobr)
        {
            sum[i] = r - l + 1;
        }
        else
        {
            int mid = l + ((r - l) >> 1);
            if (jobl <= mid)
            {
                if (le[i] == 0)
                {
                    le[i] = ++cnt;
                }

                set_one(jobl, jobr, l, mid, le[i]);
            }

            if (jobr >= mid + 1)
            {
                if (ri[i] == 0)
                {
                    ri[i] = ++cnt;
                }

                set_one(jobl, jobr, mid + 1, r, ri[i]);
            }

            up(i, le[i], ri[i]);
        }
    }
    
    void add(int left, int right)
    {
        set_one(left, right, 1, n, 1);
    }
    
    int count()
    {
        return sum[1];
    }
};

/**
 * Your CountIntervals object will be instantiated and called as such:
 * CountIntervals* obj = new CountIntervals();
 * obj->add(left,right);
 * int param_2 = obj->count();
 */
// @lc code=end

