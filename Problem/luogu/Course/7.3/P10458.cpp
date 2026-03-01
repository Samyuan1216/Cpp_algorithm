#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

void draw(vector<string> &m, int x, int y, int size);

int main()
{
    while (true)
    {
        int n = 0;
        cin >> n;

        if (n == -1)
        {
            break;
        }

        int size = pow(3, n - 1);
        vector<string> m(size, string(size, ' '));

        draw(m, 0, 0, size);

        for (auto &line: m)
        {
            cout << line << endl;
        }
        
        cout << "-" << endl;
    }
}

void draw(vector<string> &m, int x, int y, int size)
{
    if (size == 1)
    {
        m[x][y] = 'X';

        return;
    }

    int m1 = size / 3;
    int m2 = m1 * 2;

    draw(m, x, y, m1);
    draw(m, x, y + m2, m1);
    draw(m, x + m1, y + m1, m1);
    draw(m, x + m2, y, m1);
    draw(m, x + m2, y + m2, m1);
}