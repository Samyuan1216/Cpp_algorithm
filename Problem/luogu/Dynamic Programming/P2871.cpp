#include <bits/stdc++.h>

using vi = std::vector<int>;

const int MAXM = 13000;
vi dp(MAXM);
int n, m;

int main()
{
    std::cin >> n >> m;

    for (int i = 0, x, y; i < n; i++)
    {
        std::cin >> x >> y;
        for (int j = m; j >= x; j--)
        {
            dp[j] = std::max(dp[j], dp[j - x] + y);
        }
    }

    std::cout << dp[m] << std::endl;
}