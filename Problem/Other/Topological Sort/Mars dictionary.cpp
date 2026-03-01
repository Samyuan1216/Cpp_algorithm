#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n = 0;
    cin >> n;

    vector<string> words(n);
    for (auto &word: words)
    {
        cin >> word;
    }

    vector<int> indegree(26, -1);
    for (auto &word: words)
    {
        for (int i = 0; i < word.length(); i++)
        {
            indegree[word[i] - 'a'] = 0;
        }
    }

    vector<int> head(26), next(100), to(100);
    int cnt = 1;
    for (int i = 0, j = 0, len = 0; i < n - 1; i++)
    {
        string cur = words[i], nxt = words[i + 1];
        j = 0;
        len = min(cur.length(), nxt.length());
        
        for (; j < len; j++)
        {
            if (cur[j] != nxt[j])
            {
                next[cnt] = head[cur[j] - 'a'];
                to[cnt] = nxt[j] - 'a';
                head[cur[j] - 'a'] = cnt++;

                indegree[nxt[j] - 'a']++;

                break;
            }
        }

        if (j < cur.length() && j == nxt.length())
        {
            cout << endl;
            return 0;
        }
    }

    vector<int> q(26);
    int kinds = 0, l = 0, r = 0;
    for (int i = 0; i < 26; i++)
    {
        if (indegree[i] != -1)
        {
            kinds++;
        }

        if (indegree[i] == 0)
        {
            q[r++] = i;
        }
    }

    string ans;
    while (l < r)
    {
        int cur = q[l++];
        ans += cur + 'a';

        for (int i = head[cur]; i > 0; i--)
        {
            indegree[to[i]]--;
            if (indegree[to[i]] == 0)
            {
                q[r++] = to[i];
            }
        }
    }

    if (ans.length() == kinds)
    {
        cout << ans;
    }
    else
    {
        cout << endl;
    }
}

/*
5
wrt
wrf
er
ett
rftt
*/

/*
2
z
x
*/

/*
3
z
x
z
*/