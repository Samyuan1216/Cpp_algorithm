// @leet start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int lengthOfLongestSubstring(string s)
    {
        std::unordered_map<char, int> cnt;
        int ans = 0;
        bool illigal = false;
        for (int l = 0, r = 0; r < int(s.length()); r++)
        {
            cnt[s[r]]++;
            if (cnt[s[r]] > 1)
            {
                illigal = true;
            }

            while (illigal)
            {
                char c = s[l++];
                cnt[c]--;
                if (cnt[c] == 1)
                {
                    illigal = false;
                    break;
                }
            }

            ans = std::max(ans, r - l + 1);
        }

        return ans;
    }
};
// @leet end
