#include <bits/stdc++.h>
using namespace std;

class Trie
{
public:
    static const int MAXN = 150001;
    static int tree[MAXN][26];
    static int pass[MAXN];
    static int end[MAXN];
    static int cnt;
    
    static void build()
    {
        cnt = 1;
    }

    static void insert(string word)
    {
        int cur = 1;
        pass[cur]++;

        for (int i = 0, path = 0; i < word.length(); i++)
        {
            path = word[i] - 'a';

            if (tree[cur][path] == 0)
            {
                cnt++;
                tree[cur][path] = cnt;
            }

            cur = tree[cur][path];
            pass[cur]++;
        }

        end[cur]++;
    }

    static int search(string word)
    {
        int cur = 1;

        for (int i = 0, path = 0; i < word.length(); i++)
        {
            path = word[i] - 'a';

            if (tree[cur][path] == 0)
            {
                return 0;
            }

            cur = tree[cur][path];
        }

        return end[cur];
    }

    static int prefix_number(string prefix)
    {
        int cur = 1;

        for (int i = 0, path = 0; i < prefix.length(); i++)
        {
            path = prefix[i] - 'a';

            if (tree[cur][path] == 0)
            {
                return 0;
            }

            cur = tree[cur][path];
        }

        return pass[cur];
    }

    static void delete_n(string word)
    {
        if (search(word) > 0)
        {
            int cur = 1;
            pass[cur]--;

            for (int i = 0, path = 0; i < word.length(); i++)
            {
                path = word[i] - 'a';
                pass[tree[cur][path]]--;

                if (pass[tree[cur][path]] == 0)
                {
                    tree[cur][path] = 0;
                    return;
                }

                cur = tree[cur][path];
            }

            end[cur]--;
        }
    }

    static void clear()
    {
        for (int i = 1; i <= cnt; i++)
        {
            fill(tree[i], tree[i] + 26, 0);
            pass[i] = 0;
            end[i] = 0;
        }
    }
};

int Trie::cnt = 0;
int Trie::tree[MAXN][26] = {};
int Trie::pass[MAXN] = {};
int Trie::end[MAXN] = {};

int main()
{
    Trie::build();
    Trie::insert("abc");
    Trie::insert("abs");
    Trie::insert("css");
    Trie::insert("abcd");

    cout << Trie::search("abc") << endl;
    cout << Trie::prefix_number("abc") << endl;
    cout << Trie::search("abb") << endl;
    
    Trie::delete_n("abs");
    Trie::clear();
}