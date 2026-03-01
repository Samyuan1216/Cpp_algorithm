// @lc code=start
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
    int largestBSTSubtree(TreeNode *root)
    {
        return f(root).max_bst_size;
    }

    struct Info
    {
        long long max;
        long long min;
        bool is_bst;
        int max_bst_size;

        Info(long long a, long long b, bool c, int d)
        {
            max = a;
            min = b;
            is_bst = c;
            max_bst_size = d;
        }
    };

    Info f(TreeNode *x)
    {
        if (x == nullptr)
        {
            Info res(INT64_MIN, INT64_MAX, true, 0);
            return res;
        }

        Info infol = f(x->left);
        Info infor = f(x->right);

        long long maxn = max((long long)x->val, max(infol.max, infor.max));
        long long minn = min((long long)x->val, min(infol.min, infor.min));
        bool is_bst = infol.is_bst && infor.is_bst && x->val > infol.max && x->val < infor.min;
        int max_bst_size = 0;

        if (is_bst)
        {
            max_bst_size = infol.max_bst_size + infor.max_bst_size + 1;
        }
        else
        {
            max_bst_size = max(infol.max_bst_size, infor.max_bst_size);
        }

        Info res(maxn, minn, is_bst, max_bst_size);
        return res;
    }
};
// @lc code=end

