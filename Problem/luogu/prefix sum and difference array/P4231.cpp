#include <bits/stdc++.h>
using namespace std;

void set_c(vector<int64_t> &cnt, int l, int r, int s, int e, int d)
{
    cnt[l] += s;
    cnt[l + 1] += d - s;
    cnt[r + 1] -= d + e;
    cnt[r + 2] += e;
}

void build(vector<int64_t> &cnt, int N)
{
    for (int i = 1; i <= N; i++)
    {
        cnt[i] += cnt[i - 1];
    }

    for (int i = 1; i <= N; i++)
    {
        cnt[i] += cnt[i - 1];
    }
}

int main()
{
    ios::sync_with_stdio(false);

    int N = 0, M = 0;
    cin >> N >> M;

    vector<int64_t> cnt(N + 10);
    while (M--)
    {
        int l = 0, r = 0, s = 0, e = 0;
        cin >> l >> r >> s >> e;

        set_c(cnt, l, r, s, e, (e - s) / (r - l));
    }

    build(cnt, N);

    int64_t maxn = 0, Xor = 0;
    for (int i = 1; i <= N; i++)
    {
        maxn = max(maxn, cnt[i]);
        Xor ^= cnt[i];
    }

    cout << Xor << " " << maxn << endl;
}