#include <iostream>
using namespace std;

int main()
{
    int n = 0, m = 0, k = 0;

    cin >> n >> m >> k;

    int A[n][m] = {}, B[m][k] = {}, C[n][k] = {};

    for (auto& line: A)
    {
        for (auto& x: line)
        {
            cin >> x;
        }
    }

    for (auto& line: B)
    {
        for (auto& x: line)
        {
            cin >> x;
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < k; j++)
        {
            for (int t = 0; t < m; t++)
            {
                C[i][j] += A[i][t] * B[t][j];
            }
        }
    }

    for (auto& line: C)
    {
        for (auto& x: line)
        {
            cout << x << " ";
        }

        cout << endl;
    }
}