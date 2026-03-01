#include <iostream>
#include <format>
using namespace std;

int main()
{
    int n = 5, m = 5;
    int A[n][m] = {};

    for (auto& line: A)
    {
        for (auto& x: line)
        {
            cin >> x;
        }
    }

    bool found = false;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            bool IsMax = true, IsMin = true;

            for (int k = 0; k < n; k++)
            {
                if (A[i][j] < A[i][k])
                {
                    IsMax = false;
                    break;
                }
            }

            for (int k = 0; k < m; k++)
            {
                if (A[i][j] > A[k][j])
                {
                    IsMin = false;
                    break;
                }
            }

            if (IsMax == true && IsMin == true)
            {
                cout << format("{} {} {}", i + 1, j + 1, A[i][j]) << endl;

                found = true;
            }
        }
    }

    if (found == false)
    {
        cout << "not found" << endl;
    }
}