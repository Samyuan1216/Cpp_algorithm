#include <bits/stdc++.h>
using namespace std;

vector<int> diff(3010);
bool appear[3000];
int n, q, m, cnt;

int main()
{
    cin >> n >> q;
    for (int i = 1; i <= n; i++)
    {
        cin >> diff[i];
    }

    while (q--)
    {
        cnt = 0;
        fill(appear, appear + 3000, false);

        cin >> m;

        for (int i = 1; i <= n; i++)
        {
            if (appear[diff[i] % m] == false)
            {
                appear[diff[i] % m] = true;
                cnt++;
            }
        }

        cout << cnt << endl;
    }
}