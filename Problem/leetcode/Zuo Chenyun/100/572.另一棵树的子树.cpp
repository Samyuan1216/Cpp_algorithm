/*
 * @lc app=leetcode.cn id=572 lang=cpp
 *
 * [572] 另一棵树的子树
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
    bool isSubtree(TreeNode* root, TreeNode* subRoot)
    {
        vector<int> s1, s2;
        build(s1, root);
        build(s2, subRoot);

        return kmp(s1, s2) != -1;
    }

    void build(vector<int> &s, TreeNode *x)
    {
        if (x != nullptr)
        {
            s.push_back(x->val);
            build(s, x->left);
            build(s, x->right);
        }
        else
        {
            s.push_back(INT32_MAX);
        }
    }

    int kmp(vector<int> &s1, vector<int> &s2)
    {
        int n = s1.size(), m = s2.size(), x = 0, y = 0;
        vector<int> ne = next_array(s2, m);

        while (x < n && y < m)
        {
            if (s1[x] == s2[y])
            {
                x++;
                y++;
            }
            else if (y == 0)
            {
                x++;
            }
            else
            {
                y = ne[y];
            }
        }

        return (y == m? x - y: -1);
    }

    vector<int> next_array(vector<int> &s, int m)
    {
        if (m == 1)
        {
            return vector<int>{-1};
        }

        vector<int> ne(m);
        ne[0] = -1;
        ne[1] = 0;

        int i = 2, cn = 0;
        while (i < m)
        {
            if (s[i - 1] == s[cn])
            {
                ne[i++] = ++cn;
            }
            else if (cn > 0)
            {
                cn = ne[cn];
            }
            else
            {
                ne[i++] = 0;
            }
        }

        return ne;
    }
};
// @lc code=end

