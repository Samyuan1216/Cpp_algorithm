#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    long long minimumTime(vector<int>& d, vector<int>& r)
    {
        long long ans;
        for (long long left = 1, right = 10000000000, mid; left <= right;)
        {
            mid = left + ((right - left) >> 1);
            if (check(d, r, mid))
            {
                ans = mid;
                right = mid - 1;
            }
            else
            {
                left = mid + 1;
            }
        }

        return ans;
    }

    int gcd(int a, int b)
    {
        return b == 0? a: gcd(b, a %b);
    }

    int lcm(int a, int b)
    {
        return a / gcd(a, b) * b;
    }

    bool check(vector<int> &d, vector<int> &r, long long k)
    {
        long long num = k, first = d[0], second = d[1];
        num = num - k / r[0] - k / r[1] + k / lcm(r[0], r[1]);
        first = max(first - k / r[1] + k / lcm(r[0], r[1]), 0LL);
        second = max(second - k / r[0] + k / lcm(r[0], r[1]), 0LL);

        return first + second <= num;
    }
};