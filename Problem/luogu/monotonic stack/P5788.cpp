#include <bits/stdc++.h>
using namespace std;

const int MAXN = 3000010;
vector<int> st(MAXN), a(MAXN), ans(MAXN);
int n = 0, r = -1, cur = 0;

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }

    for (int i = 1; i <= n; i++)
    {
        while (r >= 0 && a[i] > a[st[r]])
        {
            ans[st[r--]] = i;
        }

        st[++r] = i;
    }

    for (int i = 1; i <= n; i++)
    {
        cout << ans[i] << " \n"[i == n];
    }
}