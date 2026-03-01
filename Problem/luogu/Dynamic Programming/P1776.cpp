#include <bits/stdc++.h>
using namespace std;

// 单调队列优化
const int MAXN = 110, MAXW = 40010;
vector<int> v(MAXN), w(MAXN), c(MAXN), dp(MAXW), dq(MAXW);
int n = 0, t = 0, l = 0, r = 0;

int value(int i, int j)
{
    return dp[j] - j / w[i] * v[i];
}

int main()
{
    cin >> n >> t;
    for (int i = 1; i <= n; i++)
    {
        cin >> v[i] >> w[i] >> c[i];
    }

    for (int i = 1; i <= n; i++)
    {
        for (int mod = 0; mod <= min(t, w[i] - 1); mod++)
        {
            l = r = 0;
            for (int j = t - mod, cnt = 1; j >= 0 && cnt <= c[i]; j -= w[i], cnt++)
            {
                while (l < r && value(i, dq[r - 1]) <= value(i, j))
                {
                    r--;
                }

                dq[r++] = j;
            }

            for (int j = t - mod, enter = j - w[i] * c[i]; j >= 0; j -= w[i], enter -= w[i])
            {
                if (enter >= 0)
                {
                    while (l < r && value(i, dq[r - 1]) <= value(i, enter))
                    {
                        r--;
                    }

                    dq[r++] = enter;
                }

                dp[j] = value(i, dq[l]) + j / w[i] * v[i];

                if (dq[l] == j)
                {
                    l++;
                }
            }
        }
    }

    cout << dp[t] << endl;
}

// 二进制分组优化
// const int MAXN = 1010, MAXW = 40010;
// vector<int> v(MAXN), w(MAXN), dp(MAXW);
// int n = 0, t = 0, m = 0;

// int main()
// {
//     cin >> n >> t;
//     for (int i = 1, value = 0, weight = 0, cnt = 0; i <= n; i++)
//     {
//         cin >> value >> weight >> cnt;
//         for (int k = 1; k <= cnt; k <<= 1)
//         {
//             v[++m] = k * value;
//             w[m] = k * weight;
//             cnt -= k;
//         }

//         if (cnt > 0)
//         {
//             v[++m] = cnt * value;
//             w[m] = cnt * weight;
//         }
//     }

//     for (int i = 1; i <= m; i++)
//     {
//         for (int j = t; j >= w[i]; j--)
//         {
//             dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
//         }
//     }

//     cout << dp[t] << endl;
// }