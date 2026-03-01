#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using usi = unordered_set<int>;
using umii = unordered_map<int, int>;

bool finish(vi &l, usi &s)
{
    int len = l.size();
    for (int i = 0; i < len; i++)
    {
        for (int j = i + 1; j < len; j++)
        {
            int a = abs(l[i] - l[j]);
            if (s.find(a) == s.end())
            {
                l.push_back(a);
                s.insert(a);
            }
        }
    }

    return (len == l.size());
}

int len1(vi &arr)
{
    vi l = arr;
    usi s;
    for (auto &x: arr)
    {
        s.insert(x);
    }

    while (!finish(l, s));

    return l.size();
}

int gcd(int a, int b)
{
    return (b == 0? a: gcd(b, a % b));
}

int len2(vi &arr)
{
    int maxn = 0, g = 0;
    for (auto &x: arr)
    {
        maxn = max(maxn, x);
        if (x != 0)
        {
            g = x;
        }
    }

    if (g == 0)
    {
        return arr.size();
    }

    umii cnts;
    for (auto &x: arr)
    {
        if (x != 0)
        {
            g = gcd(g, x);
        }

        cnts[x]++;
    }

    int ans = maxn / g, max_cnt = 0;
    for (auto &p: cnts)
    {
        if (p.first != 0)
        {
            ans += p.second - 1;
        }

        max_cnt = max(max_cnt, p.second);
    }

    if (cnts.find(0) != cnts.end())
    {
        ans += cnts[0];
    }
    else if (max_cnt > 1)
    {
        ans++;
    }

    return ans;
}

random_device rd;
mt19937 gen(rd());
uniform_real_distribution dis(0.0, 1.0);

vi random_array(int n, int v)
{
    vi ans(n);
    for (auto &x: ans)
    {
        x = dis(gen) * v;
    }

    return ans;
}

int main()
{
    cout << "测试开始" << endl;

    int N = 50, V = 200, test_time = 2000;
    for (int i = 0; i < test_time; i++)
    {
        int n = dis(gen) * N + 1;
        vi nums = random_array(n, V);

        int ans1 = len1(nums);
        int ans2 = len2(nums);

        if (ans1 != ans2)
        {
            cout << "出错了" << endl;
            break;
        }
    }

    cout << "测试结束" << endl;
}