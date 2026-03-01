#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;
using vull = vector<ull>;

const int MAXN = 10010;
vull nums(MAXN);
int n, base = 433;
string s;

ull v(char c)
{
    if (c >= '0' && c <= '9')
    {
        return c - '0' + 1;
    }
    else if (c >= 'a' && c <= 'z')
    {
        return c - 'a' + 11;
    }
    else
    {
        return c - 'A' + 37;
    }
}

ull value()
{
    ull ans = v(s[0]);
    for (int i = 1; i < (int)s.length(); i++)
    {
        ans = ans * base + v(s[i]);
    }

    return ans;
}

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> s;
        nums[i] = value();
    }

    sort(nums.begin(), nums.begin() + n);
    
    int ans = 0;
    for (int i = 0, j = 1; i < n; i = j, j++)
    {
        while (j < n && nums[i] == nums[j])
        {
            j++;
        }

        ans++;
    }

    cout << ans << endl;
}