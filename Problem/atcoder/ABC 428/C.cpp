#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

const int MAXN = 800010;
vi sta(MAXN), stb(MAXN);
int q, x, topa = 0, topb = 0;
char c;

int main()
{
    cin >> q;
    while (q--)
    {
        cin >> x;
        if (x == 1)
        {
            cin >> c;

            sta[topa + 1] = sta[topa] + (c == '('? 1: -1);
            topa++;

            stb[topb + 1] = min(stb[topb], sta[topa]);
            topb++;
        }
        else
        {
            topa--;
            topb--;
        }

        if (sta[topa] == 0 && stb[topb] == 0)
        {
            cout << "Yes" << endl;
        }
        else
        {
            cout << "No" << endl;
        }
    }
}