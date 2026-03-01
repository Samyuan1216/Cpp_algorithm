/*
 * @lc app=leetcode.cn id=2458 lang=cpp
 *
 * [2458] 移除子树后的二叉树高度
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

const int MAXN = 100010;
vector<int> dfn(MAXN), sizem(MAXN), deep(MAXN), maxr(MAXN), maxl(MAXN);
int dfn_cnt = 0;

class Solution
{
public:
    vector<int> treeQueries(TreeNode* root, vector<int>& queries)
    {
        dfn_cnt = 0;
        f(root, 0);

        for (int i = 1; i <= dfn_cnt; i++)
        {
            maxl[i] = max(maxl[i - 1], deep[i]);
        }

        maxr[dfn_cnt + 1] = 0;
        for (int i = dfn_cnt; i >= 1; i--)
        {
            maxr[i] = max(maxr[i + 1], deep[i]);
        }

        int m = queries.size();
        vector<int> ans(m);
        
        for (int i = 0; i < m; i++)
        {
            int left_max = maxl[dfn[queries[i]] - 1];
            int right_max = maxr[dfn[queries[i]] + sizem[dfn[queries[i]]]];
            ans[i] = max(left_max, right_max);
        }

        return ans;
    }

    void f(TreeNode *x, int k)
    {
        int i = ++dfn_cnt;
        dfn[x->val] = i;
        sizem[i] = 1;
        deep[i] = k;

        if (x->left != nullptr)
        {
            f(x->left, k + 1);
            sizem[i] += sizem[dfn[x->left->val]];
        }

        if (x->right != nullptr)
        {
            f(x->right, k + 1);
            sizem[i] += sizem[dfn[x->right->val]];
        }
    }
};
// @lc code=end

