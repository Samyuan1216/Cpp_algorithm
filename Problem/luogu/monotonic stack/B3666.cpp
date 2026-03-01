#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000010;
vector<uint64_t> st(MAXN), a(MAXN);
int n = 0, r = -1, nor = 0;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }

    for (int i = 1; i <= n; i++)
    {
        while (r >= 0 && a[i] >= a[st[r]])
        {
            nor ^= st[r];
            r--;
        }

        st[++r] = i;
        nor ^= st[r];

        cout << nor << endl;
    }
}