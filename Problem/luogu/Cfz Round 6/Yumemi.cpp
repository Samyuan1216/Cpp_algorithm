#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n = 0, k = 0;
    cin >> n >> k;
    getchar();

    while (n--)
    {
        string s;
        getline(cin, s);

        vector<int> cnt(10);
        int len = s.length();
        for (int i = 0; i < len; i++)
        {
            cnt[s[i] - '0']++;
        }

        if (cnt[0] > 0)
        {
            cout << "kawaii" << endl;
            continue;
        }

        long long sum = 1;
        for (int i = 9; i >= 2 && sum <= k; i--)
        {
            while (cnt[i] > 0)
            {
                sum *= i;
                cnt[i]--;

                if (sum > k)
                {
                    break;
                }
            }
        }

        if (sum <= k)
        {
            cout << "kawaii" << endl;
        }
        else
        {
            cout << "dame" << endl;
        }
    }
}