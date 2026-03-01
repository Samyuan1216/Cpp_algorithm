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
 * bool next_permutation(Iterator begin, Iterator end)
 * 生成下一个排列，在原数组中直接修改
 * 如果已经是最后一个排列，则修改为最小的排列后，则返回 false
 * 
 * bool prev_permutation(Iterator begin, Iterator end)
 * 和 next_permutation 反过来
 * 复杂度 O(n)
 */
int main() {
  vector<int> a = {1, 1, 1, 100};
  do {
    for (auto x : a) cout << x << ' ';
    cout << endl;
  } while (next_permutation(a.begin(), a.end()));

  // cout << "=====" << endl;
  // vector<int> a = {4, 3, 2, 1};
  // do {
  //   for (auto x : a) cout << x << ' ';
  //   cout << endl;
  // } while (prev_permutation(a.begin(), a.end()));
}