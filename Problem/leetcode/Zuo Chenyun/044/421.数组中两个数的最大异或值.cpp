/*
 * @lc app=leetcode.cn id=421 lang=cpp
 *
 * [421] 数组中两个数的最大异或值
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findMaximumXOR(vector<int>& nums)
    {
        int maxn = INT_MIN;
        for (auto x: nums)
        {
            maxn = max(maxn, x);
        }

        int ans = 0;
        set<int> s;

        for (int i = 31 - (maxn > 0? __builtin_clz(maxn): 0); i >= 0; i--)
        {
            int better = ans | (1 << i);
            s.clear();

            for (auto x: nums)
            {
                x = (x >> i) << i;
                s.insert(x);

                if (s.find(better ^ x) != s.end())
                {
                    ans = better;
                    break;
                }
            }
        }

        return ans;
    }

    int findMaximumXOR1(vector<int>& nums)
    {
        build(nums);
        
        int ans = 0;
        for (auto &x: nums)
        {
            ans = max(ans, max_xor(x));
        }

        clear();

        return ans;
    }

    static const int MAXN = 3000001;
    static int tree[MAXN][2];
    static int cnt;
    static int left;

    static void build(vector<int>& nums)
    {
        cnt = 1;

        int maxn = INT_MIN;
        for (auto &x: nums)
        {
            maxn = max(maxn, x);
        }

        left = 31 - (maxn > 0? __builtin_clz(maxn): 31);
        for (auto &x: nums)
        {
            insert(x);
        }
    }

    static void insert(int num)
    {
        int cur = 1;
        for (int i = left, path = 0; i >= 0; i--)
        {
            path = (num >> i) & 1;
            if (tree[cur][path] == 0)
            {
                cnt++;
                tree[cur][path] = cnt;
            }

            cur = tree[cur][path];
        }
    }

    static int max_xor(int num)
    {
        int ans = 0;
        int cur = 1;
        for (int i = left, status = 0, want = 0; i >= 0; i--)
        {
            status = (num >> i) & 1;
            want = status ^ 1;
            if (tree[cur][want] == 0)
            {
                want ^= 1;
            }

            ans |= (status ^ want) << i;
            cur = tree[cur][want];
        }

        return ans;
    }

    static void clear()
    {
        for (int i = 1; i <= cnt; i++)
        {
            tree[i][0] = tree[i][1] = 0;
        }
    }
};

int Solution::tree[MAXN][2] = {};
int Solution::cnt = 0;
int Solution::left = 0;
// @lc code=end