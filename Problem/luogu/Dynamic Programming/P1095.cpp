#include <bits/stdc++.h>
using namespace std;

int main()
{
    int M = 0, S = 0, T = 0;
    cin >> M >> S >> T;
    
    vector<int> dp(M + 1);
    vector<int> dp1(M + 1);

    bool flag = false;
    dp[M] = 17;
    flag = (dp[M] >= S? true: false);
    if (M - 10 >= 0)
    {
        dp[M - 10] = 60;
        flag = (dp[M - 10] >= S? true: false);
    }

    int time = 1, maxs = max(dp[M], dp[M - 10]);
    for (int i = 2; i <= T && flag == false; i++)
    {
        for (int j = M; j >= 0; j--)
        {
            int p1 = (dp[j] > 0? dp[j] + 17: 0);
            int p2 = 0, p3 = 0;
            if (j + 10 <= M)
            {
                p2 = (dp[j + 10] > 0? dp[j + 10] + 60: 0);
            }

            if (j - 4 >= 0 && j < M)
            {
                p3 = dp[j - 4];
            }
            else if (j == M)
            {
                for (int k = j - 4; k <= j; k++)
                {
                    p3 = max(p3, dp[max(0, k)]);
                }
            }

            dp1[j] = max(p1, max(p2, p3));

            if (dp1[j] >= S)
            {
                flag = true;
                time = i;
                break;
            }
            else
            {
                maxs = max(maxs, dp1[j]);
            }
        }

        dp = dp1;
        dp1.clear();
        dp1.resize(M + 1);
    }

    if (flag == true)
    {
        cout << "Yes" << endl;
        cout << time << endl;
    }
    else
    {
        cout << "No" << endl;
        cout << maxs << endl;
    }
}