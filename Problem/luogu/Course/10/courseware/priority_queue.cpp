#include <algorithm>
#include <iostream>
#include <chrono>
#include <format>
#include <random>
#include <queue>
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
 * push/emplace
 * pop
 * 
 * top
 * empty
 * size
 * 
 * pop <-- [3 2 100 0] <-- push
 * 100 3 2 0
 * 
 * 堆 大顶堆，小顶堆
 * 复杂度(logn)
 */
int main() {
  priority_queue<int> que;
  int n = 10000000;
  vector<int> vec(n);
  for (auto &x : vec) x = rnd();
  vector<int> sorted(n);
  benchmark("push & pop", [&]() {
    for (int i = 0; i < n; i ++) que.push(vec[i]);
    for (int i = 0; i < n; i ++) {
      sorted[i] = que.top();
      que.pop();
    }
  });
  benchmark("sort", [&]() {
    ranges::sort(vec, greater<int>());
  });
  for (int i = 0; i < n; i ++) {
    if (sorted[i] != vec[i]) {
      cout << "error" << endl;
    }
  }
}