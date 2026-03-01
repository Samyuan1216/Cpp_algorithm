/*
 * @lc app=leetcode.cn id=30 lang=cpp
 *
 * [30] 串联所有单词的子串
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;
using vi = vector<int>;
using vull = vector<ull>;

const int base = 499;

class Solution
{
private:
    vull ha, power;  // 改为成员变量
    
public:
    vector<int> findSubstring(string s, vector<string>& words)
    {
        vi ans;
        if (s.empty() || words.empty())
        {
            return ans;
        }

        unordered_map<ull, int> mp;
        for (auto &word: words)
        {
            ull v = h(word);
            mp[v]++;
        }

        build(s);

        int n = s.length(), word_len = words[0].length(), word_num = words.size(), all_len = word_len * word_num;
        unordered_map<ull, int> window;
        for (int init = 0; init < word_len && init + all_len <= n; init++)
        {
            int debt = word_num;
            for (int l = init, r = init + word_len, part = 0; part < word_num; l += word_len, r += word_len, part++)
            {
                ull cur = h(l, r);
                window[cur]++;
                
                if (window[cur] <= mp[cur])
                {
                    debt--;
                }
            }

            if (debt == 0)
            {
                ans.push_back(init);
            }

            for (int l1 = init, r1 = init + word_len, l2 = init + all_len, r2 = init + all_len + word_len; r2 <= n; l1 += word_len, r1 += word_len, l2 += word_len, r2 += word_len)
            {
                ull out = h(l1, r1), in = h(l2, r2);

                window[out]--;
                if (window[out] < mp[out])
                {
                    debt++;
                }

                window[in]++;
                if (window[in] <= mp[in])
                {
                    debt--;
                }

                if (debt == 0)
                {
                    ans.push_back(r1);
                }
            }

            window.clear();
        }

        return ans;
    }

    void build(string &str)
    {
        int n = str.length();
        ha.resize(n);
        power.resize(n);
        
        power[0] = 1;
        for (int i = 1; i < n; i++)
        {
            power[i] = power[i - 1] * base;
        }

        ha[0] = str[0] - 'a' + 1;
        for (int i = 1; i < n; i++)
        {
            ha[i] = ha[i - 1] * base + str[i] - 'a' + 1;
        }
    }

    ull h(int l, int r)
    {
        ull ans = ha[r - 1];
        if (l > 0)
        {
            ans -= ha[l - 1] * power[r - l];
        }

        return ans;
    }

    ull h(string &str)
    {
        if (str.empty())
        {
            return 0;
        }

        ull ans = str[0] - 'a' + 1;
        for (int i = 1; i < str.length(); i++)
        {
            ans = ans * base + str[i] - 'a' + 1;
        }

        return ans;
    }
};
// @lc code=end