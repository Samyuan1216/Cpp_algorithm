#include <bits/stdc++.h>

using vi = std::vector<int>;

const int MAXV = 20010;
vi dp(MAXV);
int v, n;

int main()
{
    std::cin >> v >> n;
    for (int i = 1, x; i <= n; i++)
    {
        std::cin >> x;
        for (int j = v; j >= x; j--)
        {
            dp[j] = std::max(dp[j], dp[j - x] + x);
        }
    }

    std::cout << v - dp[v] << std::endl;
}