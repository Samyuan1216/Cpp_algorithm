/*
 * @lc app=leetcode.cn id=543 lang=cpp
 *
 * [543] 二叉树的直径
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
    int diameterOfBinaryTree(TreeNode* root)
    {
        return f(root).diameter;
    }

    struct Info
    {
        int diameter;
        int height;

        Info(int a, int b): diameter(a), height(b) {}
    };

    Info f(TreeNode *x)
    {
        if (x == nullptr)
        {
            Info res(0, 0);
            return res;
        }

        Info infol = f(x->left);
        Info infor = f(x->right);

        int diameter = max(infol.diameter, infor.diameter);
        int height = max(infol.height, infor.height) + 1;
        diameter = max(diameter, infol.height + infor.height);

        Info res(diameter, height);
        return res;
    }
};
// @lc code=end

