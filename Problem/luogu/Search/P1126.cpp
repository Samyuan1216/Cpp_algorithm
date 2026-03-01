#include <bits/stdc++.h>
using namespace std;

const int MAXN = 55, MAXM = 55;
vector<vector<int>> mp(MAXN, vector<int>(MAXM));
vector<int> moved{-1, 0, 1, 0, -1};
queue<tuple<int, int, char>> q;
bool visited[MAXN][MAXM][4];
int N = 0, M = 0, sa = 0, sb = 0, ea = 0, eb = 0, l = 0, r = 0, s = 0, level = 0;
char d = '\0';

bool check(int i, int j)
{
    if (i > 0 && i < N && j > 0 && j < M && mp[i][j] == 0 && mp[i - 1][j] == 0 && mp[i][j - 1] == 0 && mp[i - 1][j - 1] == 0)
    {
        return true;
    }

    return false;
}

int duration(char c)
{
    int index = 0;
    if (c == 'E')
    {
        index = 1;
    }
    else if (c == 'S')
    {
        index = 2;
    }
    else if (c == 'W')
    {
        index = 3;
    }
    else
    {
        index = 0;
    }

    return index;
}

char left_rotate(char c)
{
    if (c == 'E')
    {
        c = 'N';
    }
    else if (c == 'S')
    {
        c = 'E';
    }
    else if (c == 'W')
    {
        c = 'S';
    }
    else
    {
        c = 'W';
    }

    return c;
}

char right_rotate(char c)
{
    if (c == 'E')
    {
        c = 'S';
    }
    else if (c == 'S')
    {
        c = 'W';
    }
    else if (c == 'W')
    {
        c = 'N';
    }
    else
    {
        c = 'E';
    }

    return c;
}

int main()
{
    ios::sync_with_stdio(false);

    cin >> N >> M;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cin >> mp[i][j];
        }
    }

    cin >> sa >> sb >> ea >> eb >> d;

    q.push(make_tuple(sa, sb, d));
    visited[sa][sb][d] = true;

    while (q.empty() == false)
    {
        s = q.size();
        for (int i = 0; i < s; i++)
        {
            int a = get<0>(q.front()), b = get<1>(q.front());
            char c = get<2>(q.front());
            q.pop();

            if (a == ea && b == eb)
            {
                cout << level << endl;
                return 0;
            }

            for (int j = 1; j <= 3; j++)
            {
                int na = a + j * moved[duration(c)], nb = b + j * moved[duration(c) + 1];
                if (check(na, nb) == false)
                {
                    break;
                }

                if (visited[na][nb][duration(c)] == false)
                {
                    visited[na][nb][duration(c)] = true;
                    q.push(make_tuple(na, nb, c));
                }
            }

            if (visited[a][b][duration(left_rotate(c))] == false)
            {
                visited[a][b][duration(left_rotate(c))] = true;
                q.push(make_tuple(a, b, left_rotate(c)));
            }

            if (visited[a][b][duration(right_rotate(c))] == false)
            {
                visited[a][b][duration(right_rotate(c))] = true;
                q.push(make_tuple(a, b, right_rotate(c)));
            }
        }

        level++;
    }

    cout << -1 << endl;
}