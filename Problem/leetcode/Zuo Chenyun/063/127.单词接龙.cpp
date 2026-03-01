/*
 * @lc app=leetcode.cn id=127 lang=cpp
 *
 * [127] 单词接龙
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList)
    {
        set<string> dict;
        for (auto &word: wordList)
        {
            dict.insert(word);
        }

        if (dict.find(endWord) == dict.end())
        {
            return 0;
        }

        set<string> small_level, big_level, next_level;
        small_level.insert(beginWord);
        big_level.insert(endWord);

        for (int len = 2; small_level.empty() == false; len++)
        {
            for (auto &word: small_level)
            {
                string str = word;
                for (int i = 0; i < str.length(); i++)
                {
                    char old = str[i];
                    for (char c = 'a'; c <= 'z'; c++)
                    {
                        if (c != old)
                        {
                            str[i] = c;
                            if (big_level.find(str) != big_level.end())
                            {
                                return len;
                            }

                            if (dict.find(str) != dict.end())
                            {
                                dict.erase(str);
                                next_level.insert(str);
                            }
                        }
                    }

                    str[i] = old;
                }
            }

            if (next_level.size() <= big_level.size())
            {
                small_level = next_level;
            }
            else
            {
                small_level = big_level;
                big_level = next_level;
            }

            next_level.clear();
        }

        return 0;
    }
};
// @lc code=end

