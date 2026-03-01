/*
 * @lc app=leetcode.cn id=126 lang=cpp
 *
 * [126] 单词接龙 II
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    set<string> dict, cur_level, next_level;
    map<string, vector<string>> graph;
    vector<string> path;
    vector<vector<string>> ans;

    void build(vector<string>& wordList)
    {
        for (auto &word: wordList)
        {
            dict.insert(word);
        }
    }
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList)
    {
        build(wordList);
        if (dict.find(endWord) == dict.end())
        {
            return ans;
        }
        
        if (bfs(beginWord, endWord) == true)
        {
            dfs(endWord, beginWord);
        }

        return ans;
    }

    bool bfs(string beginWord, string endWord)
    {
        bool find = false;
        cur_level.insert(beginWord);

        while (cur_level.empty() == false)
        {
            for (auto &word: cur_level)
            {
                dict.erase(word);
            }

            for (auto &word: cur_level)
            {
                string str = word;
                for (int i = 0; i < str.length(); i++)
                {
                    char old = str[i];
                    for (char ch = 'a'; ch <= 'z'; ch++)
                    {
                        str[i] = ch;
                        if (dict.find(str) != dict.end() && str != word)
                        {
                            if (str == endWord)
                            {
                                find = true;
                            }

                            if (graph.find(str) == graph.end())
                            {
                                graph[str] = vector<string>();
                            }
                            
                            graph[str].push_back(word);
                            next_level.insert(str);
                        }
                    }

                    str[i] = old;
                }
            }

            if (find == true)
            {
                return true;
            }
            else
            {
                cur_level = next_level;
                next_level.clear();
            }
        }

        return false;
    }

    void dfs(string word, string aim)
    {
        path.push_back(word);
        if (word == aim)
        {
            reverse(path.begin(), path.end());
            ans.push_back(path);
            reverse(path.begin(), path.end());
        }
        else if (graph.find(word) != graph.end())
        {
            for (auto &next: graph[word])
            {
                dfs(next, aim);
            }
        }

        path.pop_back();
    }
};
// @lc code=end

