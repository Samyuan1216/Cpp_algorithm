/*
 * @lc app=leetcode.cn id=212 lang=cpp
 *
 * [212] 单词搜索 II
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words)
    {
        build(words);

        vector<string> ans;
        for (int i = 0; i < board.size(); i++)
        {
            for (int j = 0; j < board[0].size(); j++)
            {
                dfs(board, i, j, 1, ans);
            }
        }

        clear();

        return ans;
    }

    static int dfs(vector<vector<char>> &board, int i, int j, int t, vector<string> &ans)
    {
        if (i < 0 || i == board.size() || j < 0 || j == board[0].size() || board[i][j] == 0)
        {
            return 0;
        }

        char tmp = board[i][j];
        int road = tmp - 'a';

        t = tree[t][road];
        if (pass[t] == 0)
        {
            return 0;
        }

        int fix = 0;
        if (end[t].length() > 0)
        {
            fix++;
            ans.push_back(end[t]);
            end[t].clear();
        }

        board[i][j] = 0;
        fix += dfs(board, i - 1, j, t, ans);
        fix += dfs(board, i + 1, j, t, ans);
        fix += dfs(board, i, j - 1, t, ans);
        fix += dfs(board, i, j + 1, t, ans);
        board[i][j] = tmp;

        return fix;
    }

    static const int MAXN = 10001;
    static int tree[MAXN][26];
    static int pass[MAXN];
    static string end[MAXN];
    static int cnt;

    static void build(vector<string>& words)
    {
        cnt = 1;
        for (auto &str: words)
        {
            int cur = 1;
            pass[cur]++;

            for (int i = 0, path = 0; i < str.length(); i++)
            {
                path = str[i] - 'a';
                if (tree[cur][path] == 0)
                {
                    cnt++;
                    tree[cur][path] = cnt;
                }

                cur = tree[cur][path];
                pass[cur]++;
            }

            end[cur] = str;
        }
    }

    static void clear()
    {
        for (int i = 1; i <= cnt; i++)
        {
            fill(tree[i], tree[i] + 26, 0);
            pass[i] = 0;
            end[i].clear();
        }
    }
};

int Solution::tree[MAXN][26] = {};
int Solution::pass[MAXN] = {};
string Solution::end[MAXN] = {};
int Solution::cnt = 0;
// @lc code=end

