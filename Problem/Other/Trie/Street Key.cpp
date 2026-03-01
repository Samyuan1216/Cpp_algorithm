#include <bits/stdc++.h>
using namespace std;

class Trie
{
public:
    static const int MAXN = 150001;
    static int tree[MAXN][12];
    static int pass[MAXN];
    static int end[MAXN];
    static int cnt;

    static void build()
    {
        cnt = 1;
    }

    static int path(char cha)
    {
        if (cha == '#')
        {
            return 10;
        }
        else if (cha == '-')
        {
            return 11;
        }
        else
        {
            return cha - '0';
        }
    }

    static void insert(string word)
    {
        int cur = 1;
        pass[cur]++;

        for (int i = 0; i < word.length(); i++)
        {
            if (tree[cur][path(word[i])] == 0)
            {
                cnt++;
                tree[cur][path(word[i])] = cnt;
            }

            cur = tree[cur][path(word[i])];
            pass[cur]++;
        }

        end[cur]++;
    }

    static int search(string word)
    {
        int cur = 1;

        for (int i = 0; i < word.length(); i++)
        {
            if (tree[cur][path(word[i])] == 0)
            {
                return 0;
            }

            cur = tree[cur][path(word[i])];
        }

        return end[cur];
    }

    static int prefix_number(string prefix)
    {
        int cur = 1;

        for (int i = 0; i < prefix.length(); i++)
        {
            if (tree[cur][path(prefix[i])] == 0)
            {
                return 0;
            }

            cur = tree[cur][path(prefix[i])];
        }

        return pass[cur];
    }

    static void delete_n(string word)
    {
        if (search(word) > 0)
        {
            int cur = 1;
            pass[cur]--;

            for (int i = 0; i < word.length(); i++)
            {
                pass[tree[cur][path(word[i])]]--;
                if (pass[tree[cur][path(word[i])]] == 0)
                {
                    tree[cur][path(word[i])] = 0;
                    return;
                }

                cur = tree[cur][path(word[i])];
            }

            end[cur]--;
        }
    }

    static void clear()
    {
        for (int i = 1; i <= cnt; i++)
        {
            fill(tree[i], tree[i] + 12, 0);
            pass[i] = 0;
            end[i] = 0;
        }
    }
};

int Trie::cnt = 0;
int Trie::tree[MAXN][12] = {};
int Trie::pass[MAXN] = {};
int Trie::end[MAXN] = {};

int main()
{
    vector<vector<int>> a = {{3, 6, 12, 20}, {1, 9}, {4, 7, 2}, {1, 4, -1}};
    vector<vector<int>> b = {{2, 5}, {7, 10, 5}};

    Trie::build();
    for (auto &line: a)
    {
        string s;
        for (int i = 1; i < line.size(); i++)
        {
            s += to_string(line[i] - line[i - 1]) + "#";
        }

        Trie::insert(s);
    }

    vector<int> ans(b.size());
    for (int i = 0; i < b.size(); i++)
    {
        string s;
        for (int j = 1; j < b[i].size(); j++)
        {
            s += to_string(b[i][j] - b[i][j - 1]) + "#";
        }

        ans[i] = Trie::prefix_number(s);
    }

    Trie::clear();

    for (auto &x: ans)
    {
        cout << x << " ";
    }

    cout << endl;
}