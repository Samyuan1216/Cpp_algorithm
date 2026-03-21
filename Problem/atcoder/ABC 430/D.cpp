#include <bits/stdc++.h>

int nearest(int nx, std::set<int> &line)
{
    auto iter = line.find(nx);
    int res = INT32_MAX;
    
    if (iter != line.begin())
    {
        auto jter = iter; jter--;
        res = std::min(res, nx - *jter);
    }

    iter++;
    if (iter != line.end())
    {
        res = std::min(res, *iter - nx);
    }

    return res;
}

int main()
{
    int n, x, sum;
    std::cin >> n;

    std::set<int> line;
    line.insert(0);

    std::cin >> x;
    
    sum = 2 * x;
    line.insert(x);

    std::cout << sum << std::endl;

    for (int i = 2; i <= n; i++)
    {
        std::cin >> x;

        std::vector<int> hit;
        auto iter = line.lower_bound(x);
        if (iter != line.end())
        {
            hit.push_back(*iter);
        }

        if (iter != line.begin())
        {
            iter--;
            hit.push_back(*iter);
        }

        for (auto &nx: hit)
        {
            sum -= nearest(nx, line);
        }

        line.insert(x);
        hit.push_back(x);
        
        for (auto &nx: hit)
        {
            sum += nearest(nx, line);
        }

        std::cout << sum << std::endl;
    }
}