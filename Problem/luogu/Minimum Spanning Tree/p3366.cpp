#include <bits/stdc++.h>
using namespace std;

// Prim
const int MAXN = 5010, MAXM = 500010;
vector<int> headm(MAXN), nextm(MAXM), tom(MAXM), weightm(MAXM), setm(MAXN);
int cnt = 1, N = 0, M = 0, X = 0, Y = 0, Z = 0;
priority_queue <pair<int, int>,
                vector<pair<int, int>>,
                decltype([](pair<int, int> a, pair<int, int> b)
                {
                    return a.second > b.second;
                })> heapm;

int main()
{
    ios::sync_with_stdio(false);

    cin >> N >> M;

    for (int i = 0; i < M; i++)
    {
        cin >> X >> Y >> Z;

        nextm[cnt] = headm[X];
        tom[cnt] = Y;
        weightm[cnt] = Z;
        headm[X] = cnt++;

        nextm[cnt] = headm[Y];
        tom[cnt] = X;
        weightm[cnt] = Z;
        headm[Y] = cnt++;
    }

    for (int i = headm[1]; i > 0; i = nextm[i])
    {
        pair<int, int> temp{tom[i], weightm[i]};
        heapm.push(temp);
    }

    setm[1] = 1;
    int node_cnt = 1, ans = 0;
    while (heapm.empty() == false)
    {
        pair<int, int> temp = heapm.top();
        heapm.pop();

        int next = temp.first, cost = temp.second;
        if (setm[next] == 0)
        {
            node_cnt++;
            setm[next] = 1;
            ans += cost;

            for (int i = headm[next]; i > 0; i = nextm[i])
            {
                pair<int, int> temp2{tom[i], weightm[i]};
                heapm.push(temp2);
            }
        }
    }

    if (node_cnt == N)
    {
        cout << ans << endl;
    }
    else
    {
        cout << "orz" << endl;
    }
}

// Kruskal
// const int MAXN = 5010, MAXM = 200010;
// vector<int> father(MAXN);
// vector<vector<int>> edge(MAXM, vector<int>(3));
// int N = 0, M = 0;

// int find(int i)
// {
//     if (i != father[i])
//     {
//         father[i] = find(father[i]);
//     }

//     return father[i];
// }

// bool un(int a, int b)
// {
//     int ua = find(a), ub = find(b);
//     if (ua != ub)
//     {
//         father[ua] = ub;

//         return true;
//     }
//     else
//     {
//         return false;
//     }
// }

// int main()
// {
//     ios::sync_with_stdio(false);

//     cin >> N >> M;

//     for (int i = 1; i <= N; i++)
//     {
//         father[i] = i;
//     }

//     for (int i = 0; i < M; i++)
//     {
//         cin >> edge[i][0] >> edge[i][1] >> edge[i][2];
//     }

//     sort(edge.begin(), edge.begin() + M, [](vector<int> a, vector<int> b)
//     {
//         return a[2] < b[2];
//     });

//     int ans = 0, edge_cnt = 0;
//     for (int i = 0; i < M; i++)
//     {
//         if (un(edge[i][0], edge[i][1]) == true)
//         {
//             edge_cnt++;
//             ans += edge[i][2];
//         }
//     }

//     if (edge_cnt == N - 1)
//     {
//         cout << ans << endl;
//     }
//     else
//     {
//         cout << "orz" << endl;
//     }
// }