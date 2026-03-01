/*
 * @lc app=leetcode.cn id=437 lang=cpp
 *
 * [437] 路径总和 III
 */

// @lc code=start
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
#include <bits/stdc++.h>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution
{
public:
    int pathSum(TreeNode* root, int targetSum)
    {
        map<long long, int> presum;
        presum[0] = 1;

        return f(root, targetSum, 0, presum);
    }

    int f(TreeNode *x, int targetSum, long long sum, map<long long, int> presum)
    {
        if (x == nullptr)
        {
            return 0;
        }

        sum += x->val;
        int ans = (presum.find(sum - targetSum) != presum.end()? presum.at(sum - targetSum): 0);
        presum[sum]++;
        ans += f(x->left, targetSum, sum, presum);
        ans += f(x->right, targetSum, sum, presum);
        presum[sum]--;

        return ans;
    }
};
// @lc code=end

