/*
 * @lc app=leetcode.cn id=1483 lang=cpp
 *
 * [1483] 树节点的第 K 个祖先
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;

const int MAXN = 50010, LIMIT = 16;
vvi st(MAXN, vi(LIMIT));
vi deep(MAXN), lg2(MAXN), he(MAXN), ne(MAXN), to(MAXN);
int cnt, power;

class TreeAncestor
{
public:
    TreeAncestor(int n, vector<int> &parent)
    {
        power = log2(n);
        cnt = 1;
        fill(he.begin(), he.begin() + n, 0);

        for (int i = 1; i < n; i++)
        {
            add_edge(parent[i], i);
        }

        dfs(0, 0);
    }

    void add_edge(int u, int v)
    {
        ne[cnt] = he[u];
        to[cnt] = v;
        he[u] = cnt++;
    }

    int log2(int n)
    {
        int power = 1;
        while ((1 << power) <= (n >> 1))
        {
            power++;
        }

        return power;
    }

    void dfs(int u, int f)
    {
        if (u == 0)
        {
            deep[u] = 1;
        }
        else
        {
            deep[u] = deep[f] + 1;
        }

        st[u][0] = f;
        for (int p = 1; (1 << p) <= deep[u]; p++)
        {
            st[u][p] = st[st[u][p - 1]][p - 1];
        }

        for (int ei = he[u]; ei > 0; ei = ne[ei])
        {
            dfs(to[ei], u);
        }
    }
    
    int getKthAncestor(int node, int k)
    {
        if (deep[node] <= k)
        {
            return -1;
        }

        int s = deep[node] - k;
        for (int p = power; p >= 0; p--)
        {
            if (deep[st[node][p]] >= s)
            {
                node = st[node][p];
            }
        }

        return node;
    }
};

/**
 * Your TreeAncestor object will be instantiated and called as such:
 * TreeAncestor* obj = new TreeAncestor(n, parent);
 * int param_1 = obj->getKthAncestor(node,k);
 */
// @lc code=end

