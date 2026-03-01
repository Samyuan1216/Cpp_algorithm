#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<int> findMissingElements(vector<int>& nums)
    {
        int minn = 100, maxn = 1;
        for (auto &num: nums)
        {
            minn = min(minn, num);
            maxn = max(maxn, num);
        }

        bool appear[maxn - minn + 1] = {};
        for (auto &num: nums)
        {
            appear[num - minn] = true;
        }

        vector<int> ans;
        for (int i = 0; i <= maxn - minn; i++)
        {
            if (!appear[i])
            {
                ans.push_back(i + minn);
            }
        }

        return ans;
    }
};