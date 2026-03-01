#include <bits/stdc++.h>
using namespace std;

const int MAXN = 500010;
int tree[MAXN][26] = {};
vector<set<int>> ed(MAXN);
int cnt = 1;
int idx = 0;

void insert(string &word)
{
    int cur = 1;
    
    for (int i = 0, path = 0; i < word.length(); i++)
    {
        path = word[i] - 'a';

        if (tree[cur][path] == 0)
        {
            cnt++;
            tree[cur][path] = cnt;
        }

        cur = tree[cur][path];
    }

    ed[cur].insert(idx);
}

set<int> search(string &word)
{
    int cur = 1;

    for (int i = 0, path = 0; i < word.length(); i++)
    {
        path = word[i] - 'a';

        if (tree[cur][path] == 0)
        {
            return {};
        }

        cur = tree[cur][path];
    }

    return ed[cur];
}

int main()
{
    ios::sync_with_stdio(false);

    int N = 0;
    cin >> N;

    while (N--)
    {
        int L = 0;
        cin >> L;

        idx++;
        while (L--)
        {
            string word;
            cin >> word;

            insert(word);
        }
    }

    int M = 0;
    cin >> M;

    while (M--)
    {
        string word;
        cin >> word;

        set<int> ans = search(word);
        bool status = true;
        for (auto &x: ans)
        {
            if (status == true)
            {
                cout << x;
                status = false;
            }
            else
            {
                cout << " " << x;
            }
        }

        cout << endl;
    }
}