#include <bits/stdc++.h>

using ll = long long;
using arrll3 = std::array<ll, 3>;

const int MAXN = 300010;
arrll3 deer[MAXN];
int t, n, ans;
ll sumw, sump;

void solve()
{
    std::cin >> n;

    sump = 0, sumw = 0;
    for (int i = 1; i <= n; i++)
    {
        std::cin >> deer[i][0] >> deer[i][1];

        deer[i][2] = deer[i][0] + deer[i][1];
        sump += deer[i][1];
    }

    std::sort(deer + 1, deer + n + 1, [](arrll3 &a, arrll3 &b)
    {
        return a[2] < b[2];
    });

    ans = 0;
    for (int i = 1; i <= n; i++)
    {
        sumw += deer[i][0];
        sump -= deer[i][1];
        
        if (sumw <= sump)
        {
            ans++;
        }
        else
        {
            break;
        }
    }

    std::cout << ans << "\n";
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::cin >> t;
    while (t--)
    {
        solve();
    }
}