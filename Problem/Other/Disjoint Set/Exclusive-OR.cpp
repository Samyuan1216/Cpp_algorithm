// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3384

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

void solve(int n, int q)
{
    auto read = [&]() -> std::pair<int, std::vector<int>>
    {
        std::string line;
        std::getline(std::cin, line);

        std::stringstream ss(line);

        char c;
        ss >> c;

        std::vector<int> nums;
        int x;

        while (ss >> x)
        {
            nums.push_back(x);
        }

        int op;
        if (c == 'I')
        {
            op = 1;
            if (std::ssize(nums) == 2)
            {
                nums.push_back(nums[1]);
                nums[1] = n;
            }
        }
        else
        {
            op = 2;
        }

        return {op, nums};
    };

    std::vector<int> father(n + 1), dist(n + 1);
    ranges::iota(father, 0);

    auto find = [&](this auto &&find, int i) -> int
    {
        if (father[i] != i)
        {
            int old = father[i];
            father[i] = find(old);
            dist[i] ^= dist[old];
        }

        return father[i];
    };

    auto merge = [&](int l, int r, int v) -> void
    {
        if (int lf = find(l), rf = find(r); lf != rf)
        {
            if (lf == n)
            {
                std::swap(lf, rf);
            }

            father[lf] = rf;
            dist[lf] = dist[r] ^ dist[l] ^ v;
        }
    };

    auto query = [&](const auto &nums) -> std::optional<int>
    {
        int ans = 0;
        std::vector<int> fs;

        for (int i = 1, f; i <= nums[0]; ++i)
        {
            f = find(nums[i]);
            ans ^= dist[nums[i]];

            fs.push_back(f);
        }

        ranges::sort(fs);
        for (int l = 0, r = 0; l < nums[0]; l = ++r)
        {
            while (r + 1 < nums[0] && fs[r + 1] == fs[l])
            {
                ++r;
            }

            if ((r - l + 1) % 2 != 0 && fs[l] != n)
            {
                return std::nullopt;
            }
        }

        return ans;
    };

    bool status = false;
    int cnt = 0;

    while (q--)
    {
        if (auto [op, nums] = read(); op == 1)
        {
            if (status)
            {
                continue;
            }

            ++cnt;
            if (find(nums[0]) == find(nums[1]))
            {
                if ((dist[nums[0]] ^ dist[nums[1]]) != nums[2])
                {
                    status = true;
                    std::cout << std::format("The first {} facts are conflicting.\n", cnt);
                }
            }
            else
            {
                merge(nums[0], nums[1], nums[2]);
            }
        }
        else
        {
            if (status)
            {
                continue;
            }

            if (auto ans = query(nums); ans)
            {
                std::cout << *ans << "\n";
            }
            else
            {
                std::cout << "I don't know.\n";
            }
        }
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int t = 1, n, q;
    while (true)
    {
        if (std::cin >> n >> q; n != 0 || q != 0)
        {
            std::cin.ignore();

            std::cout << std::format("Case {}:\n", t++);
            solve(n, q);
            std::cout << "\n";
        }
        else
        {
            break;
        }
    }
}
