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
 * push_back/emplace_back O(1)
 * pop_back O(1)
 * insert O(n)
 * erase O(n)
 * 
 * 123456
 * 23456
 * 0123456
 */
int global[100000000];
int main() {
  int n = 100000000;
  benchmark("push_back", [&]() {
    vector<int> vec;
    for (int i = 0; i < n; i ++) vec.push_back(rnd());
  });
  benchmark("init", [&]() {
    vector<int> vec(n);
    for (auto &x : vec) x = rnd();
  });
  benchmark("reserve", [&]() {
    vector<int> vec;
    vec.reserve(n);
    for (int i = 0; i < n; i ++) vec.push_back(rnd());
  });
  benchmark("new", [&]() {
    int* arr = new int[n];
    for (int i = 0; i < n; i ++) arr[i] = rnd();
  });
  
  benchmark("global", [&]() {
    for (int i = 0; i < n; i ++) global[i] = rnd();
  });

  // benchmark("pop_back", [&]() {
  //   for (int i = 0; i < n; i ++) vec.pop_back();
  // });
  // vector<int> vec2;
  // benchmark("insert", [&]() {
  //   for (int i = 0; i < n; i ++) {
  //     vec2.insert(vec2.begin(), rnd());
  //   }
  // });
  // benchmark("erase", [&]() {
  //   for (int i = 0; i < n; i ++) {
  //     vec2.erase(vec2.begin());
  //   }
  // });
}