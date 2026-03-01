// @leet start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int finalElement(vector<int>& nums)
    {
        return std::max(nums.front(), nums.back());
    }
};
// @leet end
