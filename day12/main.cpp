#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <vector>
#include <unordered_set>
#include <queue>
#include <cctype>

template<class T>
bool contains(std::vector<T> v, T el) {
  for (auto e : v) {
    if (el == e) return true;
  }
  return false;
}

int main(int argc, char* argv[]) {
  std::ifstream file{argv[2]};
  std::unordered_map<std::string, std::vector<std::string>> graph;
  std::string line;
  while (std::getline(file, line)) {
    auto sep = line.find('-');
    std::string first = line.substr(0, sep);
    std::string second = line.substr(sep+1);
    graph[first].push_back(second);
    graph[second].push_back(first);
  }

  std::string special = argv[1][0] == '1' ? "none" : "";
  std::queue<std::tuple<std::string,std::vector<std::string>, std::string>> q;
  q.push({special, {}, "start"});

  int paths = 0;
  while(!q.empty()) {
    auto [special, visited, curr] = q.front();
    q.pop();
    visited.push_back(curr);

    for (auto next : graph[curr]) {
      if (next == "end") paths++;
      else if (std::isupper(next[0])) {
        q.push({special, visited, next});
      } else if (!contains(visited, next)) {
        q.push({special, visited, next});
      } else if (next != "start" && next != "end" && special == "") {
        q.push({next, visited, next});
      }
    }
  }

  std::cout << "Found " << paths << " paths\n";
}
