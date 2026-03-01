// @leet start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int countMonobit(int n)
    {
        return bit_width((unsigned int)n + 1);
    }
};
// @leet end
