#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <queue>
#include <unordered_set>
#include <algorithm>

// Make std::pair hashable. Not sure why it isn't...
namespace std {
  template<typename T1, typename T2>
  struct hash<std::pair<T1,T2>> {
    std::size_t operator()(const std::pair<T1,T2>& p) const {
      return hash<T1>()(p.first) ^ hash<T2>()(p.second);
    }
  };
}

std::vector<std::pair<int,int>> neighbors(const std::vector<std::vector<int>>& grid, int x, int y) {
  std::vector<std::pair<int,int>> result;
  if (x > 0) result.push_back({x-1, y});
  if (y > 0) result.push_back({x, y-1});
  if (y < grid[0].size() - 1) result.push_back({x, y+1});
  if (x < grid.size() - 1) result.push_back({x+1, y});
  return result;
}

int next(int n) {
  if (++n > 9) return 1;
  return n;
}

int main(int argc, char* argv[]) {
  std::ifstream file {argv[2]};
  std::vector<std::vector<int>> cave;
  std::vector<std::vector<int>> distances;

  int num_copies = argv[1][0] == '1' ? 0 : 4;

  std::string line;
  while (std::getline(file, line)) {
    std::vector<int> row;
    for (char c : line) row.push_back(c - '0');
    // Extend row num_copies times.
    int dim = row.size();
    for (int i = 0; i < num_copies; i++) {
      for (int j = 0; j < dim; j++) {
        row.push_back(next(row[i*dim + j]));
      }
    }
    cave.push_back(row);
    distances.push_back(std::vector(row.size(), INT_MAX));
  }
  // Extend columns num_copies times.
  int dim = cave.size();
  for (int i = 0; i < num_copies; i++) {
    for (int j = 0; j < dim; j++) {
      std::vector<int> next_row;
      std::transform(cave[i*dim + j].begin(), cave[i*dim + j].end(), 
                     std::back_inserter(next_row), &next);
      cave.push_back(next_row);
      distances.push_back(std::vector(next_row.size(), INT_MAX));
    }
  }

  // Calculate all distances.
  std::queue<std::pair<int,int>> q;
  distances[0][0] = 0;
  q.push({0,0});
  while (!q.empty()) {
    auto el = q.front();
    q.pop();

    int current = distances[el.first][el.second];
    for (const auto [x, y] : neighbors(distances, el.first, el.second)) {
      if (cave[x][y] + current < distances[x][y]) {
        distances[x][y] = cave[x][y] + current;
        q.push({x, y});
      }
    }
  }

  std::cout << "Distance: " << distances.back().back() << '\n';
}
