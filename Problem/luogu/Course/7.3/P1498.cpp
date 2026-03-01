#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include <cmath>

void draw(vector<string> &t, int x, int y, int size);

int main()
{
    int n = 0;
    cin >> n;

    int size = pow(2, n + 1);
    vector<string> t(size / 2, string(size, ' '));

    draw(t, 0, 0, size);

    for (auto &line: t)
    {
        cout << line << endl;
    }
}

void draw(vector<string> &t, int x, int y, int size)
{
    if (size == 4)
    {
        t[x][y + 1] = '/';
        t[x][y + 2] = '\\';
        t[x + 1][y] = '/';
        t[x + 1][y + 1] = '_';
        t[x + 1][y + 2] = '_';
        t[x + 1][y + 3] = '\\';
    }
    else
    {
        int m = size / 4;

        draw(t, x, y + m, size / 2);
        draw(t, x + m, y, size / 2);
        draw(t, x + m, y + 2 * m, size / 2);
    }
}