#include <bits/stdc++.h>

using ll = long long;

int cnt[2] = {1, 0};
int n, x, cur;
ll ans1, ans2;

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n;
    for (int i = 1; i <= n; i++)
    {
        std::cin >> x;
        
        cur ^= (x > 0? 0: 1);
        ans1 += cnt[cur];
        ans2 += cnt[cur ^ 1];

        cnt[cur]++;
    }

    std::cout << ans2 << " " << ans1 << std::endl;
}