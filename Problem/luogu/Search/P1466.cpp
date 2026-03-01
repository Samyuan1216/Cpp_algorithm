#include <bits/stdc++.h>
using namespace std;

const int MAXN = 40, MAXM = 400;
vector<vector<long long>> dp(MAXN, vector<long long>(MAXM));
int n = 0, m = 0;

int main()
{
    cin >> n;
    m = (1 + n) * n / 2;

    if (m & 1 == 1)
    {
        cout << 0 << endl;
        return 0;
    }

    m /= 2;

    dp[0][0] = 1;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j <= m; j++)
        {
            dp[i][j] = dp[i - 1][j];
            if (j - i >= 0)
            {
                dp[i][j] += dp[i - 1][j - i];
            }
        }
    }

    long long ans = 0;
    for (int i = 1; i <= n; i++)
    {
        ans = max(ans, dp[i][m]);
    }

    cout << ans / 2 << endl;
}

// const int MAXN = 40, MAXM = (1 << 20);
// vector<int> arr(MAXN), lsum(MAXM), rsum(MAXM);
// int N = 0;
// long long sumn = 0, ans = 0;

// int f(int i, int e, int s, vector<int> &sum, int j)
// {
//     if (i == e)
//     {
//         sum[j++] = s;
//     }
//     else
//     {
//         j = f(i + 1, e, s, sum, j);
//         j = f(i + 1, e, s + arr[i], sum, j);
//     }

//     return j;
// }

// int main()
// {
//     cin >> N;

//     for (int i = 0; i < N; i++)
//     {
//         arr[i] = i + 1;
//     }

//     sumn = (1 + N) * N / 2;

//     if (sumn & 1 == 1)
//     {
//         cout << 0 << endl;
//         return 0;
//     }

//     int lsize = f(0, N >> 1, 0, lsum, 0);
//     int rsize = f(N >> 1, N, 0, rsum, 0);

//     sort(lsum.begin(), lsum.begin() + lsize);
//     sort(rsum.begin(), rsum.begin() + rsize);

//     for (int l = 0, r = rsize - 1; l < lsize && r >= 0;)
//     {
//         int lr = l, rl = r;
//         for (; (lr < lsize || rl >= 0) && (lsum[lr] == lsum[l] || rsum[rl] == rsum[r]);)
//         {
//             if (lr < lsize && lsum[lr] == lsum[l])
//             {
//                 lr++;
//             }

//             if (rl >= 0 && rsum[rl] == rsum[r])
//             {
//                 rl--;
//             }
//         }

//         if (lsum[l] + rsum[r] == (sumn >> 1))
//         {
//             ans += (lr - l) * (r - rl);
//             l = lr;
//             r = rl;
//         }
//         else if (lsum[l] + rsum[r] > (sumn >> 1))
//         {
//             r = rl;
//         }
//         else if (lsum[l] + rsum[r] < (sumn >> 1))
//         {
//             l = lr;
//         }
//     }

//     cout << ans / 2 << endl;
// }