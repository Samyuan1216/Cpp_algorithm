#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int n = 0, m = 0, r = 0;
    cin >> n >> m >> r;

    vector<vector<int>> fs(2, vector<int>(n));
    for (auto &line: fs)
    {
        for (auto &x: line)
        {
            cin >> x;
        }
    }

    vector<vector<int>> xf(2, vector<int>(n));
    for (auto &line: xf)
    {
        for (auto &x: line)
        {
            cin >> x;
        }
    }

    while (n--)
    {
        int p = 0;
        cin >> p;
        p--;

        int index = -1;
        for (int i = 0; i < xf[0].size(); i++)
        {
            if (xf[0][i] == fs[0][p] && xf[1][i] > fs[1][p])
            {
                if (index == -1 || xf[1][i] < xf[1][index])
                {
                    index = i;
                }
            }
        }

        if (index != -1)
        {
            xf[0].erase(xf[0].begin() + index);
            xf[1].erase(xf[1].begin() + index);
        }
    }

    cout << xf[0].size() << endl;
}