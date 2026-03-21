#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

const int MAXN = 300010;
vi sum(MAXN);
int n, a, b;
string s;

int fin1(int left, int l)
{
    int ans = n + 1, r = n, mid;
    while (l <= r)
    {
        mid = l + ((r - l) >> 1);
        if (sum[mid] - sum[left - 1] >= a)
        {
            ans = mid;
            r = mid - 1;
        }
        else
        {
            l = mid + 1;
        }
    }

    return ans;
}

int fin2(int left, int l)
{
    int ans = left - 1, r = n, mid;
    while (l <= r)
    {
        mid = l + ((r - l) >> 1);
        if ((mid - left + 1) - (sum[mid] - sum[left - 1]) < b)
        {
            ans = mid;
            l = mid + 1;
        }
        else
        {
            r = mid - 1;
        }
    }

    return ans;
}

int main()
{
    cin >> n >> a >> b >> s;
    for (int i = 1; i <= n; i++)
    {
        sum[i] = sum[i - 1] + (s[i - 1] == 'a'? 1: 0);
    }

    long long ans = 0;
    for (int l = 1, ar, br; l <= n; l++)
    {
        ar = fin1(l, l), br = fin2(l, l);
        ans += max(0, br - ar + 1);
    }

    cout << ans << endl;
}