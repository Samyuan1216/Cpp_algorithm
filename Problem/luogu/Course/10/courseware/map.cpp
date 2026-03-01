#include <algorithm>
#include <iostream>
#include <chrono>
#include <format>
#include <random>
#include <map>
#include <unordered_map>
#include <set>
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
 * insert/emplace
 * erase
 * find
 * []
 */
int main() {
  map<string, int> mp;
  using value = map<int, set<int>>;
  multimap<string, value> mmp;
  unordered_map<string, int> ump;
  mp.insert(make_pair("zhugeliang", 99));
  mp.insert({"yuanfang", 95});
  mp.emplace("guojia", 92);
  // auto iter = mp.find("guojia");
  // cout << iter->first << ' ' << iter->second << endl;
  for (auto &[key, value] : mp) {
    cout << key << ' ' << value << endl;
  }
  cout << mp["guojia"] << endl;
  auto get = [&](const string key) {
    auto iter = mp.find(key);
    if (iter == mp.end()) {
      bool _;
      tie(iter, _) = mp.emplace(key, 0);
    }
    return iter->second;
  };
  cout << mp["unknown"] << endl;
  cout << get("unknown2") << endl;
  cout << mp.size() << endl;
}