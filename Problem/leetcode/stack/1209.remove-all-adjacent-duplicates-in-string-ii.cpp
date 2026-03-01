// @leet start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    string removeDuplicates(string s, int k)
    {
        stack<int> sta;
        for (int i = 0; i < s.length(); i++)
        {
            if (sta.empty() || s[i] != s[i - 1])
            {
                sta.push(1);
            }
            else if (++sta.top() == k)
            {
                sta.pop();

                s.erase(i - k + 1, k);
                i = i - k;
            }
        }

        return s;
    }
};
// @leet end
