#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);

    int n = 0, m = 0;
    cin >> n >> m;

    int set = n;
    vector<int> enemy(n + 1);

    vector<int> father(n + 1);
    for (int i = 1; i <= n; i++)
    {
        father[i] = i;
    }

    function<int (int)> find = [&](int i) -> int
    {
        if (i != father[i])
        {
            father[i] = find(father[i]);
        }

        return father[i];
    };

    function<void (int, int)> un = [&](int a, int b) -> void
    {
        int ua = find(a), ub = find(b);
        if (ua != ub)
        {
            father[ua] = ub;
            set--;
        }
    };

    while (m--)
    {
        char c = '\0';
        int p = 0, q = 0;
        cin >> c >> p >> q;

        if (c == 'F')
        {
            un(p, q);
        }
        else
        {
            if (enemy[p] == 0)
            {
                enemy[p] = q;
            }
            else
            {
                un(enemy[p], q);
            }

            if (enemy[q] == 0)
            {
                enemy[q] = p;
            }
            else
            {
                un(enemy[q], p);
            }
        }
    }

    cout << set << endl;
}