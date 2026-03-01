#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n = 0;
    cin >> n;

    vector<int> p(n);
    for (auto &x: p)
    {
        cin >> x;
    }

    int maxn = 0;
    for (int i = 0; i < n; i++)
    {
        vector<int> f(n, 0);
        for (int j = 0; j <= i; j++)
        {
            if (p[j] <= p[i])
            {
                f[0] = p[j];
                break;
            }
        }

        int len = 1, sum = 0;
        for (int j = 0; j <= i; j++)
        {
            int l = 0, r = len - 1, mid = 0;
            if (p[j] <= p[i] && p[j] > f[len - 1])
            {
                f[len] = p[j];
                len++;
            }
            else
            {
                while (l < r)
                {
                    mid = (l + r) / 2;

                    if (p[j] == f[mid])
                    {
                        break;
                    }

                    if (p[j] < f[mid])
                    {
                        r = mid;
                    }
                    else
                    {
                        l = mid + 1;
                    }
                }

                f[l] = min(f[l], p[j]);
            }
        }

        sum += len;

        reverse(p.begin(), p.end());

        vector<int> t(n, 0);
        for (int j = 0; j <= n - i - 1; j++)
        {
            if (p[j] <= p[n - i - 1])
            {
                t[0] = p[j];
                break;
            }
        }

        len = 1;
        for (int j = 0; j <= n - i - 1; j++)
        {
            int l = 0, r = len - 1, mid = 0;
            if (p[j] <= p[n - i - 1] && p[j] > t[len - 1])
            {
                t[len] = p[j];
                len++;
            }
            else
            {
                while (l < r)
                {
                    mid = (l + r) / 2;

                    if (p[j] == t[mid])
                    {
                        break;
                    }

                    if (p[j] < t[mid])
                    {
                        r = mid;
                    }
                    else
                    {
                        l = mid + 1;
                    }
                }

                t[l] = min(t[l], p[j]);
            }
        }

        sum += len - 1;
        maxn = max(maxn, sum);

        reverse(p.begin(), p.end());
    }

    cout << n - maxn << endl;
}