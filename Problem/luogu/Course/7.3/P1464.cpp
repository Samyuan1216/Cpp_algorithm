#include <iostream>
#include <vector>
using namespace std;

vector<vector<vector<long long>>> m(21, vector<vector<long long>>(21, vector<long long>(21)));

long long w(long long a, long long b, long long c)
{
    if (a <= 0 || b <= 0 || c <= 0)
    {
        return 1;
    }
    else if (a > 20 || b > 20 || c > 20)
    {
        return w(20, 20, 20);
    }
    else if (m[a][b][c] > 0)
    {
        return m[a][b][c];
    }
    else if (a < b && b < c)
    {
        m[a][b][c] = w(a, b, c - 1) + w(a, b - 1, c - 1) - w(a, b - 1, c);
        
        return m[a][b][c];
    }
    else
    {
        m[a][b][c] = w(a - 1, b, c) + w(a - 1, b - 1, c) + w(a - 1, b, c - 1) - w(a - 1, b - 1, c - 1);

        return m[a][b][c];
    }
}

int main()
{
    while (true)
    {
        long long a = 0, b = 0, c = 0;
        cin >> a >> b >> c;

        if (a == -1 && b == -1 && c == -1)
        {
            break;
        }

        cout << "w(" << a << ", " << b << ", " << c << ") = " << w(a, b, c) << endl;
    }
}