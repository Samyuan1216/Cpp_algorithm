/*
 * @lc app=leetcode.cn id=1373 lang=cpp
 *
 * [1373] 二叉搜索子树的最大键值和
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
    int maxSumBST(TreeNode* root)
    {
        return f(root).max_bst_sum;
    }

    struct Info
    {
        int max;
        int min;
        int sum;
        bool is_bst;
        int max_bst_sum;

        Info(int a, int b, int c, bool d, int e): max(a), min(b), sum(c), is_bst(d), max_bst_sum(e) {}
    };
    
    Info f(TreeNode *x)
    {
        if (x == nullptr)
        {
            Info res(INT32_MIN, INT32_MAX, 0, true, 0);
            return res;
        }

        Info infol = f(x->left);
        Info infor = f(x->right);

        int maxn = max(x->val, max(infol.max, infor.max));
        int minn = min(x->val, min(infol.min, infor.min));
        int sum = infol.sum + infor.sum + x->val;
        bool is_bst = infol.is_bst && infor.is_bst && x->val > infol.max && x->val < infor.min;
        int max_bst_sum = max(infol.max_bst_sum, infor.max_bst_sum);

        if (is_bst)
        {
            max_bst_sum = max(max_bst_sum, sum);
        }

        Info res(maxn, minn, sum, is_bst, max_bst_sum);
        return res;
    }
};
// @lc code=end

