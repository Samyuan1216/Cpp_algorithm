#include <bits/stdc++.h>

using vi = std::vector<int>;
using v2i = std::vector<vi>;

const int MAXN = 50010, BIT = 30;
v2i tree_basis(MAXN << 2, vi(BIT + 1));
vi basis(BIT + 1);
int n, m;

bool insert(vi &basis, int num)
{
    for (int i = BIT; i >= 0; i--)
    {
        if (num >> i == 1)
        {
            if (basis[i] == 0)
            {
                basis[i] = num;
                return true;
            }

            num ^= basis[i];
        }
    }

    return false;
}

void add(int jobi, int jobv, int l, int r, int i)
{
    insert(tree_basis[i], jobv);

    if (l < r)
    {
        int mid = l + ((r - l) >> 1);
        if (jobi <= mid)
        {
            add(jobi, jobv, l, mid, i << 1);
        }
        else
        {
            add(jobi, jobv, mid + 1, r, i << 1 | 1);
        }
    }
}

void merge(int jobl, int jobr, int l, int r, int i)
{
    if (l >= jobl && r <= jobr)
    {
        for (int j = BIT; j >= 0; j--)
        {
            if (tree_basis[i][j] != 0)
            {
                insert(basis, tree_basis[i][j]);
            }
        }
    }
    else
    {
        int mid = l + ((r - l) >> 1);
        if (jobl <= mid)
        {
            merge(jobl, jobr, l, mid, i << 1);
        }

        if (jobr >= mid + 1)
        {
            merge(jobl, jobr, mid + 1, r, i << 1 | 1);
        }
    }
}

int query(int jobl, int jobr)
{
    std::fill(basis.begin(), basis.end(), 0);
    merge(jobl, jobr, 1, m, 1);

    int ans = 0;
    for (int j = BIT; j >= 0; j--)
    {
        ans = std::max(ans, ans ^ basis[j]);
    }

    return ans;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::cin >> n >> m;
    for (int i = 1, op; i <= n; i++)
    {
        std::cin >> op;
        if (op == 1)
        {
            int k, x;
            std::cin >> k >> x;

            add(k, x, 1, m, 1);
        }
        else
        {
            int l, r;
            std::cin >> l >> r;

            std::cout << query(l, r) << "\n";
        }
    }
}