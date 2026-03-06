#include <bits/stdc++.h>
#include <bits/extc++.h>
namespace ranges = std::ranges;
namespace views = std::views;

using i64 = int64_t;
using i128 = __int128;
using u64 = uint64_t;
using u128 = unsigned __int128;
using f64 = double;
using f128 = long double;

template<typename T>
using lim = std::numeric_limits<T>;

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
   int n;
   std::cin >> n;

   std::vector<int> arr(n);
   int mini, maxi;
   for (int i = 0; i < n; ++i)
   {
       std::cin >> arr[i];
       if (arr[i] == 1)
       {
           mini = i;
       }
       else if (arr[i] == n)
       {
           maxi = i;
       }
   }

   std::string x;
   std::cin >> x;

   bool status = true;
   for (int i = 0; i < n; i++)
   {
       if (x[i] == '1' && (i == 0 || i == mini || i == maxi || i == n - 1))
       {
           status = false;
           break;
       }
   }

   if (!status)
   {
       std::cout << -1 << "\n";
       return;
   }

   std::cout << 5 << "\n";
   std::cout << std::format("1 {}\n", mini + 1);
   std::cout << std::format("1 {}\n", maxi + 1);
   std::cout << std::format("{} {}\n", std::min(mini, maxi) + 1, std::max(mini, maxi) + 1);
   std::cout << std::format("{} {}\n", mini + 1, n);
   std::cout << std::format("{} {}\n", maxi + 1, n);
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int t = 1;
    std::cin >> t;
    while (t--)
    {
        solve();
    }
}
