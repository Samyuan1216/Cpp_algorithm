#include <bits/stdc++.h>
using namespace std;

class Trie
{
    class Trie_Node
    {
    public:
        int pass;
        int end;
        vector<Trie_Node*> next;

        Trie_Node()
        {
            pass = 0;
            end = 0;
            next = vector<Trie_Node*>(26);
        }
    };

    Trie_Node *root;

public:
    Trie()
    {
        root = new Trie_Node();
    }

    void insert(string word)
    {
        Trie_Node *node = root;
        node->pass++;

        for (int i = 0, path = 0; i < word.length(); i++)
        {
            path = word[i] - 'a';

            if (node->next[path] == nullptr)
            {
                node->next[path] = new Trie_Node();
            }

            node = node->next[path];
            node->pass++;
        }

        node->end++;
    }

    int search(string word)
    {
        Trie_Node *node = root;

        for (int i = 0, path = 0; i < word.length(); i++)
        {
            path = word[i] - 'a';
            
            if (node->next[path] == nullptr)
            {
                return 0;
            }

            node = node->next[path];
        }

        return node->end;
    }

    int prefix_number(string prefix)
    {
        Trie_Node *node = root;

        for (int i = 0, path = 0; i < prefix.length(); i++)
        {
            path = prefix[i] - 'a';

            if (node->next[path] == nullptr)
            {
                return 0;
            }

            node = node->next[path];
        }

        return node->pass;
    }

    void delete_word(string word)
    {
        if (search(word) > 0)
        {
            Trie_Node *node = root;
            node->pass--;

            for (int i = 0, path = 0; i < word.length(); i++)
            {
                path = word[i] - 'a';
                node->next[path]->pass--;

                if (node->next[path]->pass == 0)
                {
                    auto delete_node = [](auto &self, Trie_Node *node) -> void
                    {
                        node->pass = 0;
                        node->end = 0;

                        for (auto &n: node->next)
                        {
                            if (n != nullptr)
                            {
                                self(self, n);
                                n = nullptr;
                            }
                        }

                        delete node;
                    };

                    delete_node(delete_node, node->next[path]);
                    node->next[path] = nullptr;
                    return;
                }

                node = node->next[path];
            }

            node->end--;
        }
    }

    ~Trie()
    {
        auto delete_node = [](auto &self, Trie_Node *node) -> void
        {
            node->pass = 0;
            node->end = 0;

            for (auto &n: node->next)
            {
                if (n != nullptr)
                {
                    self(self, n);
                    n = nullptr;
                }
            }

            delete node;
        };

        delete_node(delete_node, root);
        root = nullptr;
    }
};

int main()
{
    Trie T;
    T.insert("abc");
    T.insert("abs");
    T.insert("css");
    T.insert("abcd");

    cout << T.search("abc") << endl;
    cout << T.prefix_number("abc") << endl;
    cout << T.search("abb") << endl;
    
    T.delete_word("abs");
}