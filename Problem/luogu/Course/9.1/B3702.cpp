#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int m = 0, n = 0, Sx = 0, Sy = 0;
    cin >> m >> n >> Sx >> Sy;

    vector<vector<pair<int, int>>> graph(n, vector<pair<int, int>>(m));
    for (auto &line: graph)
    {
        for (auto &[x, y]: line)
        {
            cin >> x >> y;
        }
    }

    while (Sx != 0 || Sy != 0)
    {
        cout << Sx << ' ' << Sy << endl;

        auto [x, y] = graph[Sx - 1][Sy - 1];
        Sx = x;
        Sy = y;
    }
}