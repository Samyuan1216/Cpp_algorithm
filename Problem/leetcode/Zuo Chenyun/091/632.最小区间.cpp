/*
 * @lc app=leetcode.cn id=632 lang=cpp
 *
 * [632] 最小区间
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    struct Node
    {
        int v = 0;
        int i = 0;
        int j = 0;

        Node() {}
        Node(int a, int b, int c): v(a), i(b), j(c) {}

        bool operator<(const Node &other) const
        {
            return (this->v != other.v? (this->v < other.v): (this->i < other.i));
        }
    };
    
    vector<int> smallestRange(vector<vector<int>>& nums)
    {
        int k = nums.size();

        set<Node> s;
        for (int i = 0; i < k; i++)
        {
            s.insert(Node(nums[i][0], i, 0));
        }

        int a = 0, b = 0, r = INT32_MAX;
        Node maxn, minn;
        while (s.size() == k)
        {
            maxn = *s.rbegin();
            minn = *s.begin();
            s.erase(s.begin());

            if (maxn.v - minn.v < r)
            {
                r = maxn.v - minn.v;
                a = minn.v;
                b = maxn.v;
            }

            if (minn.j + 1 < nums[minn.i].size())
            {
                s.insert(Node(nums[minn.i][minn.j + 1], minn.i, minn.j + 1));
            }
        }

        return vector<int>{a, b};
    }
};
// @lc code=end

