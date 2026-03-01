#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);

    int N = 0, k = 0;
    cin >> N >> k;

    map<int, int> m;
    m.emplace(0, -1);

    int ans = 0, sum = 0;
    for (int i = 0; i < N; i++)
    {
        int x = 0;
        cin >> x;

        sum += x;

        if (m.find(sum - k) != m.end())
        {
            ans = max(ans, i - (*m.find(sum - k)).second);
        }

        if (m.find(sum) == m.end())
        {
            m.emplace(sum, i);
        }
    }

    cout << ans << endl;
}