// @leet start
#include <bits/extc++.h>
using namespace std;

template<typename T = int>
class AVL
{
private:
    struct Node
    {
        T key = T{};
        int value = 0;
        int height = 0;
        int left = 0;
        int right = 0;
        int count = 0;
        int size = 0;
    };

    std::vector<Node> tr;
    std::vector<int> free_list;
    int head = 0;
    int fi = 0;

    int new_node(const T &num, int index)
    {
        int i;
        if (!free_list.empty())
        {
            i = free_list.back();
            free_list.pop_back();
        }
        else
        {
            i = tr.size();
            tr.push_back({});
        }

        tr[i] = {num, index, 1, 0, 0, 1, 1};
        return i;
    }

    void up(int i)
    {
        tr[i].size = tr[tr[i].left].size + tr[tr[i].right].size + tr[i].count;
        tr[i].height = std::max(tr[tr[i].left].height, tr[tr[i].right].height) + 1;
    }

    int left_rotate(int i)
    {
        int r = tr[i].right;
        std::tie(tr[i].right, tr[r].left) = std::tuple(tr[r].left, i);

        up(i), up(r);
        return r;
    }

    int right_rotate(int i)
    {
        int l = tr[i].left;
        std::tie(tr[i].left, tr[l].right) = std::tuple(tr[l].right, i);

        up(i), up(l);
        return l;
    }

    int maintain(int i)
    {
        int lh = tr[tr[i].left].height, rh = tr[tr[i].right].height;
        if (lh - rh > 1)
        {
            if (tr[tr[tr[i].left].left].height < tr[tr[tr[i].left].right].height)
            {
                tr[i].left = left_rotate(tr[i].left); 
            }

            i = right_rotate(i);
        }
        else if (rh - lh > 1)
        {
            if (tr[tr[tr[i].right].right].height < tr[tr[tr[i].right].left].height)
            {
                tr[i].right = right_rotate(tr[i].right);
            }

            i = left_rotate(i);
        }

        return i;
    }

    int add(int i, int rank, const T &num, int index)
    {
        if (i == 0)
        {
            return new_node(num, index);
        }

        if (tr[tr[i].left].size >= rank)
        {
            tr[i].left = add(tr[i].left, rank, num, index);
        }
        else
        {
            tr[i].right = add(tr[i].right, rank - tr[tr[i].left].size - 1, num, index);
        }

        up(i);
        return maintain(i);
    }

    void in_order(auto &ans, int i)
    {
        if (i == 0)
        {
            return;
        }

        in_order(ans, tr[i].left);
        ans[fi][0] = tr[i].key;
        ans[fi++][1] = tr[i].value;
        in_order(ans, tr[i].right);
    }
public:
    AVL()
    {
        tr.push_back({});
    }

    void add(const T &num, int index)
    {
        head = add(head, index, num, index);
    }

    void fill(auto &ans)
    {
        in_order(ans, head);
    }
};

class Solution
{
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people)
    {
        sort(people.begin(), people.end(), [](auto &a, auto &b)
        {
            return (a[0] != b[0]? a[0] > b[0]: a[1] < b[1]);
        });

        AVL tree;
        for (auto &p: people)
        {
            tree.add(p[0], p[1]);
        }

        tree.fill(people);
        return people;
    }
};
// @leet end
