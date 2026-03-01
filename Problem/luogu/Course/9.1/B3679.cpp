#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int n = 0, k = 0, T = 0;
    cin >> n >> k >> T;

    vector<tuple<int, int ,bool>> point(n);
    for (auto &[x, y, _]: point)
    {
        cin >> x >> y;
    }

    while (k--)
    {
        int sx = 0, sy = 0;
        cin >> sx >> sy;

        for (auto &[x, y, withS]: point)
        {
            if (sx == x && sy == y)
            {
                withS = true;
            }
        }
    }

    int cnt = 0;
    while (T--)
    {
        int fx = 0, fy = 0;
        cin >> fx >> fy;

        cnt += get<2>(*max_element(point.begin(), point.end(), [&](tuple<int, int, bool> &a, tuple<int, int, bool> &b)
        {
            auto &[ax, ay, _] = a;
            auto &[bx, by, __] = b;

            int dista = (fx - ax) * (fx - ax) + (fy - ay) * (fy - ay);
            int distb = (fx - bx) * (fx - bx) + (fy - by) * (fy - by);

            return dista < distb;
        }));

        // int maxDist = 0;
        // bool withSurvive = false;
        // for (auto &[x, y, withS]: point)
        // {
        //     int dist = (fx - x) * (fx - x) + (fy - y) * (fy - y);
        //     if (dist > maxDist)
        //     {
        //         maxDist = dist;
        //         withSurvive = withS;
        //     }
        // }

        // cnt += withSurvive;
    }

    cout << cnt << endl;
}