/*
 * @lc app=leetcode.cn id=979 lang=cpp
 *
 * [979] 在二叉树中分配硬币
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
    int distributeCoins(TreeNode* root)
    {
        return f(root).move;
    }

    struct Info
    {
        int cnt;
        int sum;
        int move;

        Info(int a, int b, int c): cnt(a), sum(b), move(c) {}
    };
    
    Info f(TreeNode *x)
    {
        if (x == nullptr)
        {
            Info res(0, 0, 0);
            return res;
        }

        Info infol = f(x->left);
        Info infor = f(x->right);

        int cnt = infol.cnt + infor.cnt + 1;
        int sum = infol.sum + infor.sum + x->val;
        int move = infol.move + infor.move + abs(infol.cnt - infol.sum) + abs(infor.cnt - infor.sum);

        Info res(cnt, sum, move);
        return res;
    }
};
// @lc code=end

