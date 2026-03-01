// https://www.nowcoder.com/share/jump/1961392931766414170614

#include <bits/stdc++.h>

using vi = std::vector<int>;

const int MAXN = 200010;
vi arr(MAXN), costs(MAXN);
int n, cute, ans = 1;

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::cin >> n;
    for (int i = 1; i <= n; i++)
    {
        std::cin >> arr[i];
        costs[i] = i;
    }

    std::cin >> cute;

    for (int i = n, j = 0; i >= 1; i--)
    {
        if (arr[i] > cute)
        {
            costs[i] = j++;
        }
    }

    for (int i = 1; i <= n && ans <= costs[i]; i++, ans++);

    std::cout << ans << "\n";
}