#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;

    unordered_set<string> s;
    vector<string> mp(n);
    for (int i = 0; i < n; i++)
    {
        cin >> mp[i];
    }

    for (int low = 0, high = m - 1; high < n; low++, high++)
    {
        for (int l = 0, r = m - 1; r < n; l++, r++)
        {
            string str;
            for (int k = low; k <= high; k++)
            {
                str += mp[k].substr(l, m);
            }
            s.insert(str);
        }
    }

    cout << s.size() << endl;
}