#include <algorithm>
#include <iostream>
#include <chrono>
#include <format>
#include <random>
using namespace std;

mt19937 rnd(time(0));

/**
 * unique(Iterator begin, Iterator end, Function matcher)
 * [移除]相邻的相同元素，并返回新序列的尾部
 * 不会直接删除，需要自行删除
 * 还可以自定义[相同]
 * 
 * 复杂度 O(n)
 */
int main() {
  // 1 1 1 10000000
  // 1 10000000
  // 1 2
  // 离散化
  vector<int> vec = {1, 1, 10, 20, 30, 200, 2, 1, 10, -5, -8};
  // ranges::sort(vec);
  // ranges::unique(vec);
  vec.erase(unique(vec.begin(), vec.end(), [](int a, int b) {
    return abs(a - b) <= 10;
  }), vec.end());
  for (auto &x : vec) cout << x << ' ';
  cout << endl;
}