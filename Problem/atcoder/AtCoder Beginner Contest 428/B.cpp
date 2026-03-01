#include <bits/stdc++.h>
using namespace std;

map<string, int> mp;
set<string> ans;
string s;
int n, k, cnt;

int main()
{
    cin >> n >> k >> s;

    for (int l = 0; l < n - k + 1; l++)
    {
        mp[s.substr(l, k)]++;
    }

    for (auto &x: mp)
    {
        cnt = max(cnt, x.second);
    }

    for (auto &x: mp)
    {
        if (x.second == cnt)
        {
            ans.insert(x.first);
        }
    }

    cout << cnt << endl;
    for (auto &x: ans)
    {
        cout << x << " ";
    }
    cout << endl;
}