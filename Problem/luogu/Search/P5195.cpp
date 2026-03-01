#include <bits/stdc++.h>
using namespace std;

const int MAXW = 1010, MAXH = 1010;
vector<vector<int>> mp(MAXH, vector<int>(MAXW));
vector<int> moved{-1, 0, 1, 0, -1};
bool visited[MAXH][MAXW][2];
queue<vector<int>> q;
int W = 0, H = 0, s = 0, sx = 0, sy = 0, level = 0;

int main()
{
    ios::sync_with_stdio(false);

    cin >> W >> H;

    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            cin >> mp[i][j];

            if (mp[i][j] == 2)
            {
                sx = i;
                sy = j;
            }
        }
    }

    q.push(vector<int>{sx, sy, 0});
    visited[sx][sy][0] = true;

    while (q.empty() == false)
    {
        s = q.size();
        for (int i = 0; i < s; i++)
        {
            int x = q.front()[0], y = q.front()[1], z = q.front()[2];
            q.pop();

            if (mp[x][y] == 3 && z == 1)
            {
                cout << level << endl;
                return 0;
            }

            for (int j = 0, nx = 0, ny = 0, nz = 0; j < 4; j++)
            {
                nx = x + moved[j], ny = y + moved[j + 1], nz = 0;
                
                if (nx < 0 || ny < 0 || nx >= H || ny >= W || mp[nx][ny] == 1)
                {
                    continue;
                }

                if (mp[nx][ny] == 4)
                {
                    nz = 1;
                }

                if (visited[nx][ny][nz | z] == true)
                {
                    continue;
                }

                q.push(vector<int>{nx, ny, z | nz});
                visited[nx][ny][z | nz] = true;
            }
        }

        level++;
    }
}