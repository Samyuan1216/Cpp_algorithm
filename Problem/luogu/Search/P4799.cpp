#include <bits/stdc++.h>
using namespace std;

const int MAXN = 40, MAXM = (1 << 20);
vector<long long> diff(MAXN), lsum(MAXM), rsum(MAXM);
int N = 0;
long long M = 0;

int f(int i, int e, long long s, long long w, vector<long long> &ans, int j)
{
    if (s > w)
    {
        return j;
    }

    if (i == e)
    {
        ans[j++] = s;
    }
    else
    {
        j = f(i + 1, e, s, w, ans, j);
        j = f(i + 1, e, s + diff[i], w, ans, j);
    }

    return j;
}

int main()
{
    ios::sync_with_stdio(false);

    cin >> N >> M;
    for (int i = 0; i < N; i++)
    {
        cin >> diff[i];
    }

    int lsize = f(0, N >> 1, 0, M, lsum, 0);
    int rsize = f(N >> 1, N, 0, M, rsum, 0);

    sort(lsum.begin(), lsum.begin() + lsize);
    sort(rsum.begin(), rsum.begin() + rsize);

    long long sum = 0;
    for (int i = lsize - 1, j = 0; i >= 0; i--)
    {
        while (j < rsize && lsum[i] + rsum[j] <= M)
        {
            j++;
        }

        sum += j;
    }

    cout << sum << endl;
}