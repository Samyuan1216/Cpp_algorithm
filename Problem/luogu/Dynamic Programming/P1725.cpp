#include <bits/stdc++.h>

const int MAXN = 200010, NA = INT32_MIN;
int arr[MAXN], dp[MAXN], q[MAXN];
int n, l, r, ql, qr, ans = NA;

void add(int i)
{
    if (i >= 0 && dp[i] != NA)
    {
        while (ql < qr && dp[q[qr - 1]] <= dp[i])
        {
            qr--;
        }

        q[qr++] = i;
    }
}

void del(int i)
{
    if (i >= 0 && q[ql] == i)
    {
        ql++;
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::cin >> n >> l >> r;
    for (int i = 0; i <= n; i++)
    {
        std::cin >> arr[i];
    }

    dp[0] = arr[0];
    for (int i = 1; i <= n; i++)
    {
        add(i - l);
        del(i - r - 1);

        dp[i] = (ql < qr? dp[q[ql]] + arr[i]: NA);
    }

    for (int i = n - r + 1; i <= n; i++)
    {
        ans = std::max(ans, dp[i]);
    }

    std::cout << ans << "\n";
}