#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;
vector<int> st(MAXN), h(MAXN), ans(MAXN);
int N = 0, r = -1;

int main()
{
    cin >> N;

    for (int i = 1; i <= N; i++)
    {
        cin >> h[i];
    }

    for (int i = 1; i <= N; i++)
    {
        while (r >= 0 && h[i] > h[st[r]])
        {
            ans[st[r--]] = i;
        }

        st[++r] = i;
    }

    for (int i = 1; i <= N; i++)
    {
        cout << ans[i] << endl;
    }
}