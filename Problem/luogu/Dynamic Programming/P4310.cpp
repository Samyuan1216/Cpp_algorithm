#include <bits/stdc++.h>

int pre[32];
int n, ans;

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n;
    for (int i = 1, x, cur; i <= n; i++)
    {
        std::cin >> x;

        cur = 1;
        for (int j = 0; j < 32; j++)
        {
            if (x & (1 << j))
            {
                cur = std::max(cur, pre[j] + 1);
            }
        }

        for (int j = 0; j < 32; j++)
        {
            if (x & (1 << j))
            {
                pre[j] = std::max(pre[j], cur);
            }
        }
    }

    for (int i = 0; i < 32; i++)
    {
        ans = std::max(ans, pre[i]);
    }

    std::cout << ans << std::endl;
}