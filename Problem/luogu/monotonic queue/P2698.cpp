#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;
vector<vector<int>> diff(MAXN, vector<int>(2));
vector<int> max_dq(MAXN), min_dq(MAXN);
int N = 0, D = 0, maxh = 0, maxt = 0, minh = 0, mint = 0, ans = INT32_MAX;

bool ok()
{
    int max = (maxh < maxt ? diff[max_dq[maxh]][1] : 0);
    int min = (minh < mint ? diff[min_dq[minh]][1] : 0);

    return max - min >= D;
}

void push(int r)
{
    while (maxh < maxt && diff[max_dq[maxt - 1]][1] <= diff[r][1])
    {
        maxt--;
    }

    max_dq[maxt++] = r;

    while (minh < mint && diff[min_dq[mint - 1]][1] >= diff[r][1])
    {
        mint--;
    }

    min_dq[mint++] = r;
}

void pop(int l)
{
    if (maxh < maxt && max_dq[maxh] == l)
    {
        maxh++;
    }

    if (minh < mint && min_dq[minh] == l)
    {
        minh++;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> D;
    
    for (int i = 0; i < N; i++)
    {
        cin >> diff[i][0] >> diff[i][1];
    }

    sort(diff.begin(), diff.begin() + N, [](vector<int> &a, vector<int> &b)
    {
        return a[0] < b[0];
    });

    for (int l = 0, r = 0; l < N; l++)
    {
        while (ok() == false && r < N)
        {
            push(r++);
        }

        if (ok() == true)
        {
            ans = min(ans, diff[r - 1][0] - diff[l][0]);
        }

        pop(l);
    }

    if (ans == INT32_MAX)
    {
        ans = -1;
    }

    cout << ans << endl;
}