#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

void f(vector<vector<int>> &m, int i, int j, int p, int q);

int main()
{
    int n = 0;
    cin >> n;
    
    n = pow(2, n);

    auto m = vector<vector<int>>(n, vector<int>(n, 1));
    f(m, 0, n - 1, 0, n - 1);

    for (auto &line: m)
    {
        for (auto &x: line)
        {
            cout << x << " ";
        }

        cout << endl;
    }
}

void f(vector<vector<int>> &m, int i, int j, int p, int q)
{
    if (j - i >= 1)
    {
        int x = (j + i) / 2, y = (p + q) / 2;
        for (int a = i; a <= x; a++)
        {
            for (int b = p; b <= y; b++)
            {
                m[a][b] = 0;
            }
        }

        f(m, x + 1, j, p, y);
        f(m, i, x, y + 1, q);
        f(m, x + 1, j, y + 1, q);
    }
}