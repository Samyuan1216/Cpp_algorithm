/*
 * @lc app=leetcode.cn id=1367 lang=cpp
 *
 * [1367] 二叉树中的链表
 */

// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
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

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

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
    vector<int> str1, str2, ne;

    bool isSubPath(ListNode* head, TreeNode* root)
    {
        while (head != nullptr)
        {
            str2.push_back(head->val);
            head = head->next;
        }

        next_array(str2.size());
        return find(root, 0);
    }

    bool find(TreeNode *x, int i)
    {
        if (i == str2.size())
        {
            return true;
        }

        if (x == nullptr)
        {
            return false;
        }

        while (i >= 0 && str2[i] != x->val)
        {
            i = ne[i];
        }

        return find(x->left, i + 1) || find(x->right, i + 1);
    }

    void next_array(int m)
    {
        if (m == 1)
        {
            ne = vector<int>{-1};
            return;
        }

        ne = vector<int>(m);
        ne[0] = -1;
        ne[1] = 0;

        int i = 2, cn = 0;
        while (i < m)
        {
            if (str2[i - 1] == str2[cn])
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
    }
};
// @lc code=end

