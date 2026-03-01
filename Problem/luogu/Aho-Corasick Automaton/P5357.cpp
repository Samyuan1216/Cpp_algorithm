#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;

const int MAXN = 200010, MAXS = 200010;
vi box(MAXS);

namespace AC
{
    vvi tree(MAXS, vi(26));
    vi fail(MAXS), end(MAXN), times(MAXS);
    int cnt;

    void insert(int i, string &s)
    {
        int u = 0;
        for (int j = 0, c; j < s.length(); j++)
        {
            c = s[j] - 'a';
            if (tree[u][c] == 0)
            {
                tree[u][c] = ++cnt;
            }

            u = tree[u][c];
        }

        end[i] = u;
    }

    void set_fail()
    {
        int l = 0, r = 0;
        for (int i = 0; i < 26; i++)
        {
            if (tree[0][i] > 0)
            {
                box[r++] = tree[0][i];
            }
        }

        while (l < r)
        {
            int u = box[l++];
            for (int i = 0; i < 26; i++)
            {
                if (tree[u][i])
                {
                    fail[tree[u][i]] = tree[fail[u]][i];
                    box[r++] = tree[u][i];
                }
                else
                {
                    tree[u][i] = tree[fail[u]][i];
                }
            }
        }
    }
} // namespace AC

namespace Graph
{
    vi head(MAXS), next(MAXS), to(MAXS);
    bool visited[MAXS];
    int cnt;

    void add_edge(int u, int v)
    {
        next[++cnt] = head[u];
        to[cnt] = v;
        head[u] = cnt;
    }

    void dfs(int u)
    {
        int r = 0;
        box[r++] = u;

        int cur;
        while (r > 0)
        {
            cur = box[r - 1];
            if (!visited[cur])
            {
                visited[cur] = true;
                for (int i = head[cur]; i > 0; i = next[i])
                {
                    box[r++] = to[i];
                }
            }
            else
            {
                r--;
                for (int i = head[cur]; i > 0; i = next[i])
                {
                    AC::times[cur] += AC::times[to[i]];
                }
            }
        }
    }
} // namespace Graph

string s;
int n;

int main()
{
    cin >> n;

    for (int i = 1; i <= n; i++)
    {
        cin >> s;
        AC::insert(i, s);
    }
    AC::set_fail();

    cin >> s;
    for (int u = 0, i = 0; i < s.length(); i++)
    {
        u = AC::tree[u][s[i] - 'a'];
        AC::times[u]++;
    }

    for (int i = 1; i <= AC::cnt; i++)
    {
        Graph::add_edge(AC::fail[i], i);
    }
    Graph::dfs(0);

    for (int i = 1; i <= n; i++)
    {
        cout << AC::times[AC::end[i]] << endl;
    }
}