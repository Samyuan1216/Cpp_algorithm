#include <bits/stdc++.h>
using namespace std;

vector<int> moved{-1, 0, 1, 0, -1};

// Dijkstra
int minDistance1(vector<vector<int>> &arr, int startX, int startY, int targetX, int targetY)
{
    if (arr[startX][startY] == 0 || arr[targetX][targetY] == 0)
    {
        return -1;
    }

    int n = arr.size();
    vector<vector<int>> dis(n, vector<int>(n, INT_MAX));
    dis[startX][startY] = 1;

    priority_queue< vector<int>,
                    vector<vector<int>>,
                    decltype([](vector<int> &a, vector<int> &b)
                    {
                        return a[2] > b[2];
                    })> heap;
    heap.push(vector<int>{startX, startY, 1});

    vector<vector<int>> visited(n, vector<int>(n));
    while (heap.empty() == false)
    {
        int x = heap.top()[0], y = heap.top()[1];
        heap.pop();

        if (visited[x][y] == 1)
        {
            continue;
        }

        if (x == targetX && y == targetY)
        {
            return dis[x][y];
        }

        visited[x][y] = 1;
        for (int i = 0; i < 4; i++)
        {
            int nx = x + moved[i], ny = y + moved[i + 1];
            if (nx >= 0 && nx < n && ny >= 0 && ny < n && arr[nx][ny] == 1 && visited[nx][ny] == 0 && dis[x][y] + 1 < dis[nx][ny])
            {
                dis[nx][ny] = dis[x][y] + 1;
                heap.push(vector<int>{nx, ny, dis[x][y] + 1});
            }
        }
    }

    return -1;
}

void benchmark(const string &name, const auto &func)
{
    auto start = chrono::high_resolution_clock::now();
    func();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

    cout << name << " execution time: " << duration.count() << " ms" << endl;
}

// 曼哈顿距离
int f1(int x, int y, int targetX, int targetY)
{
    return abs(x - targetX) + abs(y - targetY);
}

// 对角线距离
int f2(int x, int y, int targetX, int targetY)
{
    return max(abs(x - targetX), abs(y - targetY));
}

// 欧式距离
double f3(int x, int y, int targetX, int targetY)
{
    return sqrt(pow(x - targetX, 2) + pow(y - targetY, 2));
}

// A*
int minDistance2(vector<vector<int>> &arr, int startX, int startY, int targetX, int targetY)
{
    if (arr[startX][startY] == 0 || arr[targetX][targetY] == 0)
    {
        return -1;
    }

    int n = arr.size();
    vector<vector<int>> dis(n, vector<int>(n, INT_MAX));
    dis[startX][startY] = 1;

    priority_queue< vector<int>,
                    vector<vector<int>>,
                    decltype([](vector<int> &a, vector<int> &b)
                    {
                        return a[2] > b[2];
                    })> heap;
    heap.push(vector<int>{startX, startY, 1 + (int)f1(startX, startY, targetX, targetY)});

    vector<vector<int>> visited(n, vector<int>(n));
    while (heap.empty() == false)
    {
        int x = heap.top()[0], y = heap.top()[1];
        heap.pop();

        if (visited[x][y] == 1)
        {
            continue;
        }

        if (x == targetX && y == targetY)
        {
            return dis[x][y];
        }

        visited[x][y] = 1;
        for (int i = 0; i < 4; i++)
        {
            int nx = x + moved[i], ny = y + moved[i + 1];
            if (nx >= 0 && nx < n && ny >= 0 && ny < n && arr[nx][ny] == 1 && visited[nx][ny] == 0 && dis[x][y] + 1 < dis[nx][ny])
            {
                dis[nx][ny] = dis[x][y] + 1;
                heap.push(vector<int>{nx, ny, dis[x][y] + 1 + (int)f1(startX, startY, targetX, targetY)});
            }
        }
    }

    return -1;
}

// 对数器验证
random_device rd;
mt19937 gen(rd());
uniform_real_distribution<> dis(0, 1);

vector<vector<int>> generate_random_array(int n)
{
    vector<vector<int>> arr(n, vector<int>(n));
    for (auto &line: arr)
    {
        for (auto &x: line)
        {
            if (dis(gen) < 0.3)
            {
                x = 0;
            }
            else
            {
                x = 1;
            }
        }
    }

    return arr;
}

int main()
{
    int len = 100, test_time = 1000;
    cout << "功能测试开始" << endl;

    bool status = false;
    for (int i = 0; i < test_time; i++)
    {
        int n = (int)(dis(gen) * len) + 2;
        vector<vector<int>> arr = generate_random_array(n);

        int start_x = (int)(dis(gen) * n), start_y = (int)(dis(gen) * n), target_x = (int)(dis(gen) * n), target_y = (int)(dis(gen) * n);
        int ans1 = minDistance1(arr, start_x, start_y, target_x, target_y);
        int ans2 = minDistance2(arr, start_x, start_y, target_x, target_y);

        if (ans1 != ans2)
        {
            cout << "出错了！" << endl;
            status = true;

            cout << "错误数据：" << endl;
            for (auto &line: arr)
            {
                cout << "[ ";
                for (auto &x: line)
                {
                    cout << x << " ";
                }
                cout << "]" << endl;
            }

            break;
        }
    }

    if (status == false)
    {
        cout << "全部正确！" << endl;
    }

    cout << "功能测试结束" << endl;

    cout << "性能测试开始" << endl;

    vector<vector<int>> arr = generate_random_array(4000);
    int start_x = 0, start_y = 0, target_x = 3900, target_y = 3900;

    benchmark("Dijkstra", [&]()
    {
        int ans = minDistance1(arr, start_x, start_y, target_x, target_y);
        cout << "Dijkstra result: " << ans << ", ";
    });

    benchmark("A*", [&]()
    {
        int ans = minDistance2(arr, start_x, start_y, target_x, target_y);
        cout << "A* result: " << ans << ", ";
    });

    cout << "性能测试结束" << endl;
}