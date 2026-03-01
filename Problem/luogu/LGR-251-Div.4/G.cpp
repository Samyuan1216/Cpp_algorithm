#include <bits/stdc++.h>
using namespace std;

vector<int> a(100010), b(100010);
string s;
int n, cnt, cur, offset = 1;

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    
    for (int i = 1; i <= n; i++)
    {
        cin >> b[i];
    }

    cin >> s;

    int i = s.length() - 1;
    for (i; s[i] == ']'; i--)
    {
        cnt++;
    }

    while (s[i] >= '0' && s[i] <= '9')
    {
        cur += (s[i] - '0') * offset;

        offset *= 10;
        i--;
    }

    i++;

    while (cnt--)
    {
        i -= 2;
        if (s[i] == 'a')
        {
            cur = a[cur];
        }
        else
        {
            cur = b[cur];
        }
    }

    cout << cur << endl;
}