#include <iostream>
using namespace std;

int main()
{
    int n = 0, m = 0;
    cin >> n >> m;

    int A[n][m] = {};
    for (auto &line: A)
    {
        for (auto &x: line)
        {
            cin >> x;
        }
    }

    for (int j = 0; j < m; j++)
    {
        for (int i = 0; i < n; i++)
        {
            cout << A[i][j] << " ";
        }

        cout << endl;
    }
}