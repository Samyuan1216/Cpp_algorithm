#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;

int f(int i, int n, int m, vvi games, vi cnts)
{
    if (i == n)
    {
        int ans = 0;
        for (int j = 0, k, b, x; j < m; j++)
        {
            k = games[j][0];
            b = games[j][1];
            x = cnts[j];
            ans += max((b - k * x) * x, 0);
        }
        return ans;
    }
    else
    {
        int ans = f(i + 1, n, m, games, cnts);
        for (int j = 0; j < m; j++)
        {
            cnts[j]++;
            ans = max(ans, f(i + 1, n, m, games, cnts));
            cnts[j]--;
        }
        return ans;
    }
}

int enough1(int n, vvi games)
{
    int m = games.size();
    vi cnts(m);
    return f(0, n, m, games, cnts);
}

struct Game
{
    int ki;
    int bi;
    int people;

    Game() {}
    Game(int a, int b): ki(a), bi(b), people(0) {}

    int earn() const
    {
        return bi - (people + 1) * ki - people * ki;
    }

    bool operator<(const Game &other) const
    {
        return this->earn() < other.earn();
    }
};

using pqg = priority_queue<Game>;

int enough2(int n, vvi nums)
{
    pqg heap;
    for (auto &p: nums)
    {
        heap.push(Game(p[0], p[1]));
    }

    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        if (heap.top().earn() <= 0)
        {
            break;
        }

        Game cur = heap.top();
        heap.pop();

        ans += cur.earn();
        cur.people++;

        heap.push(cur);
    }

    return ans;
}

random_device rd;
mt19937 gen(rd());
uniform_real_distribution dis(0.0, 1.0);

vvi random_array(int m, int v)
{
    vvi ans(m, vi(2));
    for (int i = 0; i < m; i++)
    {
        ans[i][0] = dis(gen) * v + 1;
        ans[i][1] = dis(gen) * v + 1;
    }

    return ans;
}

int main()
{
    int N = 4;
    int M = 4;
    int V = 10;
    int testTimes = 2000;
    cout << "测试开始" << endl;
    for (int i = 1; i <= testTimes; i++)
    {
        int n = (int) (dis(gen) * N) + 1;
        int m = (int) (dis(gen) * M) + 1;
        vvi games = random_array(m, V);
        int ans1 = enough1(n, games);
        int ans2 = enough2(n, games);
        if (ans1 != ans2)
        {
            cout << "出错了！" << endl;
            break;
        }
    }
    cout << "测试结束" << endl;
}