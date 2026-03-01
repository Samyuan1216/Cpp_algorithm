#include <iostream>
using namespace std;

int main()
{
    int n = 0, m = 0;

    cin >> m >> n;

    int A[m][n] = {};

    for (auto& line: A)
    {
        for (auto& x: line)
        {
            cin >> x;
        }
    }

    int sum = 0;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == 0 || j == 0 || i == m - 1 || j == n - 1)
            {
                sum += A[i][j];
            }
        }
    }

    cout << sum << endl;
}