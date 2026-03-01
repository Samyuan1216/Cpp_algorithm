/*
 * @lc app=leetcode.cn id=691 lang=cpp
 *
 * [691] 贴纸拼词
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int minStickers(vector<string>& stickers, string target)
    {
        int n = stickers.size();
        
        vector<int> head(26), next((n + 1) * 26 * 26);
        vector<string> to((n + 1) * 26 * 26);
        int cnt = 1;
        for (auto &str: stickers)
        {
            sort(str.begin(), str.end());

            for (int i = 0; i < str.length(); i++)
            {
                if (i == 0 || str[i] != str[i - 1])
                {
                    next[cnt] = head[str[i] - 'a'];
                    to[cnt] = str;
                    head[str[i] - 'a'] = cnt++;
                }
            }
        }

        sort(target.begin(), target.end());

        set<string> visited;
        visited.insert(target);
        
        vector<string> q((n + 1) * 26 * 26);
        int l = 0, r = 0;
        q[r++] = target;

        int level = 1;
        while (l < r)
        {
            int size = r - l;
            for (int i = 0; i < size; i++)
            {
                string cur = q[l++];
                for (int j = head[cur[0] - 'a']; j > 0; j = next[j])
                {
                    string nexts = nextf(cur, to[j]);
                    if (nexts == "")
                    {
                        return level;
                    }
                    else if (visited.find(nexts) == visited.end())
                    {
                        visited.insert(nexts);
                        q[r++] = nexts;
                    }
                }
            }

            level++;
        }

        return -1;
    }

    string nextf(string &cur, string &s)
    {
        string temp;
        for (int i = 0, j = 0; i < cur.length();)
        {
            if (j == s.length())
            {
                temp += cur[i++];
            }
            else
            {
                if (cur[i] < s[j])
                {
                    temp += cur[i++];
                }
                else if (cur[i] > s[j])
                {
                    j++;
                }
                else
                {
                    i++;
                    j++;
                }
            }
        }

        return temp;
    }
};
// @lc code=end

