/*
 * @lc app=leetcode.cn id=144 lang=cpp
 *
 * [144] 二叉树的前序遍历
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
    vector<int> preorderTraversal(TreeNode* root)
    {
        stack<TreeNode*> sta;
        vector<int> ans;

        if (root != nullptr)
        {
            sta.push(root);

            while (!sta.empty())
            {
                root = sta.top();
                sta.pop();

                ans.push_back(root->val);
                if (root->right != nullptr)
                {
                    sta.push(root->right);
                }

                if (root->left != nullptr)
                {
                    sta.push(root->left);
                }
            }
        }

        return ans;
    }
};
// @lc code=end

