#include <bits/stdc++.h>
using namespace std;

int main()
{
    int N = 0, M = 0;
    cin >> N >> M;

    vector<int> father(N + 1);
    for (int i = 1; i <= N; i++)
    {
        father[i] = i;
    }

    vector<int> len(N + 1, 1);

    auto find = [&](int i) -> int
    {
        stack<int> st;

        while (i != father[i])
        {
            st.push(i);
            i = father[i];
        }

        while (st.empty() == false)
        {
            father[st.top()] = i;
            st.pop();
        }

        return i;
    };

    auto same_set = [&](int a, int b) -> bool
    {
        return (find(a) == find(b));
    };

    auto un = [&](int a, int b) -> void
    {
        int ua = find(a);
        int ub = find(b);

        if (ua != ub)
        {
            if (len[ua] >= len[ub])
            {
                father[ub] = ua;
                len[ua] += len[ub];
            }
            else
            {
                father[ua] = ub;
                len[ub] += len[ua];
            }
        }
    };

    while (M--)
    {
        int Z = 0, x = 0, y = 0;
        cin >> Z >> x >> y;

        if (Z == 1)
        {
            un(x, y);
        }
        else if (Z == 2)
        {
            if (same_set(x, y) == true)
            {
                cout << "Y" << endl;
            }
            else
            {
                cout << "N" << endl;
            }
        }
    }
}