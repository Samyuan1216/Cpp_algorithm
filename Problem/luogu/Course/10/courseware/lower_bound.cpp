#include <algorithm>
#include <iostream>
#include <chrono>
#include <format>
#include <random>
using namespace std;

mt19937 rnd(time(0));

void benchmark(const string &name, const auto &func) {
  auto start = std::chrono::high_resolution_clock::now();
  func();
  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  cout << format("{} execution time: {} ms\n", name, duration.count());
}

/**
 * lower_bound(Iterator begin, Iterator end, Type v, Function comp)
 * [在有序数组中]找到第一个大于等于 v 的迭代器
 * upper_bound(Iterator begin, Iterator end, Type v, Function comp)
 * [在有序数组中]找到第一个大于 v 的迭代器
 * 
 * 1 1 3 3 3 3 4 4   -> 2
 *     [l, u]
 * 二分搜索
 * 复杂度 O(logn)
 */
int main() {
  int n = 10000000;
  vector<int> a(n);
  for (int i = 0; i < n; i ++) a[i] = rnd();
  ranges::sort(a);
  vector<int> b = a;
  vector<int> targets(1000);
  for (auto &x : targets) x = rnd();

  vector<int> ans1, ans2;
  benchmark("[for]", [&](){
    for (auto &x : targets) {
      for (int i = 0; i < n; i ++) {
        if (a[i] >= x) {
          ans1.push_back(i);
          break;
        }
      }
    }
  });

  benchmark("[lower_bound]", [&]() {
    for (auto &x : targets) {
      ans2.push_back(ranges::lower_bound(a, x) - a.begin());
    }
  });

  for (size_t i = 0; i < ans1.size(); i ++) {
    if (ans1[i] != ans2[i]) {
      cout << "error" << endl;
    }
  }
}