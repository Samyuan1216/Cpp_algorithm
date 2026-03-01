#include <bits/stdc++.h>
using namespace std;

const int MAXN = 27, MAXM = 610, MAXQ = 27 * 610;
vector<int> head(MAXN), ne(MAXM), to(MAXM), indegree(MAXN), q(MAXN);
bool path[MAXN][MAXN] = {};
set<int> exist;
int cnt = 1, l = 0, r = 0, n = 0, m = 0;

int main()
{
    ios::sync_with_stdio(false);

    cin >> n >> m;

    for (int i = 0; i < 26; i++)
    {
        path[i][i] = true;
    }

    bool ok = false;
    for (int x = 1; x <= m; x++)
    {
        fill(q.begin(), q.end(), 0);
        l = r = 0;

        string str;
        cin >> str;

        exist.insert(str[0] - 'A');
        exist.insert(str[2] - 'A');

        ne[cnt] = head[str[0] - 'A'];
        to[cnt] = str[2] - 'A';
        head[str[0] - 'A'] = cnt++;

        indegree[str[2] - 'A']++;

        vector<int> temp_idg(indegree);
        for (int i = 0; i < 26; i++)
        {
            if (exist.find(i) != exist.end() && temp_idg[i] == 0)
            {
                q[r++] = i;
            }
        }

        int ans = 0;
        while (l < r)
        {
            int cur = q[l++];
            if (l == r)
            {
                bool status = true;
                for (int i = 0; i < r; i++)
                {
                    if (path[cur][q[i]] == false)
                    {
                        status = false;
                        break;
                    }
                }

                if (status == true)
                {
                    ans++;
                }
            }

            for (int i = head[cur]; i > 0; i = ne[i])
            {
                for (int j = 0; j < r; j++)
                {
                    path[to[i]][q[j]] |= path[cur][q[j]];
                }

                temp_idg[to[i]]--;
                if (temp_idg[to[i]] == 0)
                {
                    q[r++] = to[i];
                }
            }
        }

        if (ans == n)
        {
            ok = true;

            string ans_s;
            for (int i = 0; i < r; i++)
            {
                ans_s += q[i] + 'A';
            }

            cout << "Sorted sequence determined after " << x << " relations: " << ans_s << "." << endl;
            break;
        }
        else if (r != exist.size())
        {
            ok = true;

            cout << "Inconsistency found after "<< x <<" relations." << endl;
            break;
        }
    }

    if (ok == false)
    {
        cout << "Sorted sequence cannot be determined." << endl;
    }
}