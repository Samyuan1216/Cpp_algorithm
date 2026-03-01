#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    long long maxProduct(vector<int>& nums)
    {
        long long maxn = -100010, sub_maxn = -100010, minn = 100010, sub_minn = 100010;
        for (auto &num: nums)
        {
            if (num > maxn)
            {
                sub_maxn = maxn;
                maxn = num;
            }
            else if (num > sub_maxn)
            {
                sub_maxn = num;
            }

            if (num < minn)
            {
                sub_minn = minn;
                minn = num;
            }
            else if (num < sub_minn)
            {
                sub_minn = num;
            }
        }

        long long ans = max(max(maxn * sub_maxn, minn * sub_minn) * 100000, maxn * minn * -100000);
        return ans;
    }
};