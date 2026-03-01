/*
 * @lc app=leetcode.cn id=145 lang=cpp
 *
 * [145] 二叉树的后序遍历
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
    vector<int> postorderTraversal(TreeNode* root)
    {
        stack<TreeNode*> sta;
        vector<int> ans;

        if (root != nullptr)
        {
            sta.push(root);
            while (!sta.empty())
            {
                TreeNode *cur = sta.top();
                if (cur->left != nullptr && root != cur->left && root != cur->right)
                {
                    sta.push(cur->left);
                }
                else if (cur->right != nullptr && root != cur->right)
                {
                    sta.push(cur->right);
                }
                else
                {
                    ans.push_back(cur->val);
                    
                    root = sta.top();
                    sta.pop();
                }
            }
        }

        return ans;
    }
};
// @lc code=end

