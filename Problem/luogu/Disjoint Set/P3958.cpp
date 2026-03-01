#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);

    int T = 0;
    cin >> T;

    while (T--)
    {
        int n = 0, h = 0, r = 0;
        cin >> n >> h >> r;

        vector<int> x(n), y(n), z(n);
        for (int i = 0; i < n; i++)
        {
            cin >> x[i] >> y[i] >> z[i];
        }

        vector<int> father(n);
        for (int i = 0; i < n; i++)
        {
            father[i] = i;
        }

        auto find = [&](auto &self, int i) -> int
        {
            if (i != father[i])
            {
                father[i] = self(self, father[i]);
            }

            return father[i];
        };

        auto un = [&](int a, int b) -> void
        {
            int ua = find(find, a), ub = find(find, b);
            if (ua != ub)
            {
                if (z[ua] >= z[ub])
                {
                    father[ub] = ua;
                }
                else
                {
                    father[ua] = ub;
                }
            }
        };

        auto dist = [&](int P1, int P2) -> int
        {
            return ceil(sqrt(pow(x[P1] - x[P2], 2) + pow(y[P1] - y[P2], 2) + pow(z[P1] - z[P2], 2)));
        };

        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (dist(i, j) <= 2 * r)
                {
                    un(i, j);
                }
            }
        }

        bool status = false;
        for (int i = 0; i < n; i++)
        {
            if (z[i] <= r && (h - z[find(find, i)] <= r))
            {
                status = true;
            }
        }

        if (status == true)
        {
            cout << "Yes" << endl;
        }
        else
        {
            cout << "No" << endl;
        }
    }
}