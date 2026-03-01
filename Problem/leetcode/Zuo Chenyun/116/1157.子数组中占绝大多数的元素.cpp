/*
 * @lc app=leetcode.cn id=1157 lang=cpp
 *
 * [1157] 子数组中占绝大多数的元素
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;

const int MAXN = 20010;
vvi nums(MAXN, vi(2));
vi cand(MAXN << 2), hp(MAXN << 2);
int n;

class MajorityChecker
{
public:
    MajorityChecker(vector<int>& arr)
    {
        n = arr.size();
        build_cnt(arr);
        build_tree(arr, 1, n, 1);
    }
    
    int query(int left, int right, int threshold)
    {
        vi ch = find_cand(left + 1, right + 1, 1, n, 1);

        int can = ch[0];
        return (cnt(left, right, can) >= threshold? can: -1);
    }

    void build_cnt(vi &arr)
    {
        for (int i = 0; i < n; i++)
        {
            nums[i][0] = arr[i];
            nums[i][1] = i;
        }

        sort(nums.begin(), nums.begin() + n, [](vi &a, vi &b)
        {
            return (a[0] != b[0]? (a[0] < b[0]): (a[1] < b[1]));
        });
    }

    int cnt(int l, int r, int v)
    {
        return bs(v, r) - bs(v, l - 1);
    }

    int bs(int v, int i)
    {
        int find = -1, l = 0, r = n - 1, mid;
        while (l <= r)
        {
            mid = l + ((r - l) >> 1);
            if (nums[mid][0] < v || (nums[mid][0] == v && nums[mid][1] <= i))
            {
                find = mid;
                l = mid + 1;
            }
            else
            {
                r = mid - 1;
            }
        }

        return find + 1;
    }

    void up(int i)
    {
        int lc = cand[i << 1], lh = hp[i << 1];
        int rc = cand[i << 1 | 1], rh = hp[i << 1 | 1];

        cand[i] = (lc == rc || lh >= rh? lc: rc);
        hp[i] = (lc == rc? (lh + rh): (abs(lh - rh)));
    }

    void build_tree(vi &arr, int l, int r, int i)
    {
        if (l == r)
        {
            cand[i] = arr[l - 1];
            hp[i] = 1;
        }
        else
        {
            int mid = l + ((r - l) >> 1);
            build_tree(arr, l, mid, i << 1);
            build_tree(arr, mid + 1, r, i << 1 | 1);

            up(i);
        }
    }

    vi find_cand(int jobl, int jobr, int l, int r, int i)
    {
        if (l >= jobl && r <= jobr)
        {
            return vi{cand[i], hp[i]};
        }

        int mid = l + ((r - l) >> 1);

        if (jobr <= mid)
        {
            return find_cand(jobl, jobr, l, mid, i << 1);
        }

        if (jobl >= mid + 1)
        {
            return find_cand(jobl, jobr, mid + 1, r, i << 1 | 1);
        }

        vi lch = find_cand(jobl, jobr, l, mid, i << 1);
        vi rch = find_cand(jobl, jobr, mid + 1, r, i << 1 | 1);

        int lc = lch[0], lh = lch[1];
        int rc = rch[0], rh = rch[1];
        int c = (lc == rc || lh >= rh? lc: rc);
        int h = (lc == rc? (lh + rh): (abs(lh - rh)));

        return vi{c, h};
    }
};

/**
 * Your MajorityChecker object will be instantiated and called as such:
 * MajorityChecker* obj = new MajorityChecker(arr);
 * int param_1 = obj->query(left,right,threshold);
 */
// @lc code=end

