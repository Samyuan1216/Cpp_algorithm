#include <bits/stdc++.h>
using namespace std;

bool f(vector<int> &cuts, vector<int> &poisons, long long hp, int limit)
{
    int n = min((int)cuts.size(), limit);
    for (int i = 0, j = 1; i < n; i++, j++)
    {
        hp -= max((long long)cuts[i], (long long)(limit - j) * poisons[j]);
        if (hp <= 0)
        {
            return true;
        }
    }

    return false;
}

int fast(vector<int> &cuts, vector<int> &poisons, int hp)
{
    int ans = INT32_MIN;
    for (int l = 1, r = hp + 1, m = 0; l <= r;)
    {
        m = l + ((r - l) >> 1);
        if (f(cuts, poisons, hp, m) == true)
        {
            ans = m;
            r = m - 1;
        }
        else
        {
            l = m + 1;
        }
    }

    return ans;
}

int main()
{
    vector<int> cuts{100, 500, 10}, poisons{20, 40, 10};
    int hp = 1000;

    cout << fast(cuts, poisons, hp) << endl;
}