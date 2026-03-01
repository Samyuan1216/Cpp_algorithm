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
 * front
 * empty
 * size
 * 
 * pop <-- [0 1 2 3] <-- push
 * 
 * cannot []
 */
int main() {
  queue<int> que;
  for (int i = 0; i < 10; i ++) {
    que.push(i);
  }
  while (!que.empty()) {
    int front = que.front();
    que.pop();
    cout << front << endl;
  }
  int n = 100000000;
  benchmark("push", [&]() {
    for (int i = 0; i < n; i ++) que.push(rnd());
  });
  benchmark("pop", [&]() {
    for (int i = 0; i < n; i ++) que.pop();
  });
}