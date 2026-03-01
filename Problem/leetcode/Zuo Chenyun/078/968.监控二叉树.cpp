/*
 * @lc app=leetcode.cn id=968 lang=cpp
 *
 * [968] 监控二叉树
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
    int ans = 0;

    int minCameraCover(TreeNode* root)
    {
        if (f(root) == 0)
        {
            ans++;
        }

        return ans;
    }

    int f(TreeNode *x)
    {
        if (x == nullptr)
        {
            return 1;
        }

        int left = f(x->left), right = f(x->right);
        if (left == 0 || right == 0)
        {
            ans++;
            return 2;
        }

        if (left == 1 && right == 1)
        {
            return 0;
        }

        return 1;
    }
};
// @lc code=end

