// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    long long power(long long x, int n, int mod)
    {
        long long ans = 1;
        while (n > 0)
        {
            if ((n & 1) == 1)
            {
                ans = (ans * x) % mod;
            }

            x = (x * x) % mod;
            n >>= 1;
        }

        return ans;
    }

    int cuttingBamboo(int bamboo_len)
    {
        if (bamboo_len == 2)
        {
            return 1;
        }
        else if (bamboo_len == 3)
        {
            return 2;
        }

        int mod = 1000000007;
        int tail = (bamboo_len % 3 == 0? 1: (bamboo_len % 3 == 1? 4: 2));
        int p = (tail == 1? bamboo_len: (bamboo_len - tail)) / 3;

        return (int)(power(3, p, mod) * tail % mod);
    }
};
// @lc code=end