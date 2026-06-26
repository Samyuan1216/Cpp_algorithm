#include <bits/extc++.h>
namespace ranges = std::ranges;

using i64 = long long;

#ifndef YUAN_DEBUG
struct __X
{
    __X& operator<<(const auto& str) {return *this;}
    void sp([[maybe_unused]] const std::string& str = "") {}
} dout;
#define debug(x)
#endif

void solve()
{
    int n, k, x;
    std::cin >> n >> k >> x;

    std::vector<i64> arr(n);
    for (auto &x: arr)
    {
        std::cin >> x;
    }

    ranges::sort(arr, std::greater());

    struct Data
    {
        i64 sum = 0;
        std::vector<int> arr;

        Data(i64 s, const std::vector<int> &a): sum(s), arr(a) {}

        bool operator<(const Data &other) const
        {
            return sum < other.sum;
        }
    };

    Data first(k * arr[0], std::vector<int>(n));
    first.arr[0] = k;

    std::priority_queue<Data> heap;
    heap.push(first);

    std::set<std::vector<int>> s;
    s.insert(first.arr);

    while (x--)
    {
        auto cur = heap.top();
        heap.pop();

        std::cout << cur.sum << "\n";
        for (int i = n - 2; i >= 0; --i)
        {
            if (cur.arr[i] == 0)
            {
                continue;
            }

            cur.sum += -arr[i] + arr[i + 1];
            --cur.arr[i], ++cur.arr[i + 1];

            if (!s.contains(cur.arr))
            {
                heap.push(cur);
                s.insert(cur.arr);
            }

            cur.sum -= -arr[i] + arr[i + 1];
            ++cur.arr[i], --cur.arr[i + 1];
        }
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int t = 1;
    while (t--)
    {
        solve();
    }
}
