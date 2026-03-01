#include <bits/stdc++.h>
using namespace std;

long long a, b;

long long count(long long n, int d)
{
    long long ans = 0;
    for (long long right = 1, tmp = n, left, cur; tmp != 0; right *= 10, tmp /= 10)
    {
        left = tmp / 10;
        cur = tmp % 10;

        if (d == 0)
        {
            left--;
        }

        ans += left * right;
        if (cur > d)
        {
            ans += right;
        }
        else if (cur == d)
        {
            ans += n % right + 1;
        }
    }

    return ans;
}

int main()
{
    cin >> a >> b;

    for (int d = 0; d <= 9; d++)
    {
        cout << count(b, d) - count(a - 1, d) << " \n"[d == 9];
    }
}