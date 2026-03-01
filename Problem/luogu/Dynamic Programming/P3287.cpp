#include <bits/stdc++.h>

const int MAXN = 10010, MAXK = 510, MAXH = 5500;
int arr[MAXN], tree[MAXH + 1][MAXK];
int n, k;

int lowbit(int i)
{
    return i & -i;
}

void update(int x, int y, int v)
{
    for (int i = x; i <= MAXH; i += lowbit(i))
    {
        for (int j = y; j <= k + 1; j += lowbit(j))
        {
            tree[i][j] = std::max(tree[i][j], v);
        }
    }
}

int max(int x, int y)
{
    int ans = 0;
    for (int i = x; i > 0; i -= lowbit(i))
    {
        for (int j = y; j > 0; j -= lowbit(j))
        {
            ans = std::max(ans, tree[i][j]);
        }
    }

    return ans;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::cin >> n >> k;
    for (int i = 1; i <= n; i++)
    {
        std::cin >> arr[i];
    }

    for (int i = 1, v, dp; i <= n; i++)
    {
        for (int j = k; j >= 0; j--)
        {
            v = arr[i] + j;
            dp = max(v, j + 1) + 1;

            update(v, j + 1, dp);
        }
    }

    std::cout << max(MAXH, k + 1) << "\n";
}