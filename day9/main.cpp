#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <queue>

template<class T1, class T2>
struct pair_hash {
    inline std::size_t operator()(const std::pair<T1,T2> & v) const {
        return std::hash<T1>()(v.first)^std::hash<T2>()(v.second);
    }
};

int main(int argc, char* argv[]) {
  std::ifstream file{argv[1]};
  std::vector<std::string> field;
  std::string line;
  while (std::getline(file, line)) {
    field.push_back("9" + line + "9");
  }
  size_t len = field[0].size();
  line = std::string(len, '9');
  field.push_back(line);
  field.insert(field.begin(), line);

  std::unordered_set<std::pair<int,int>, pair_hash<int,int>> seen;

  int risk = 0;
  std::priority_queue<int> bassins;
  for (int i = 1; i < field.size() - 1; i++) {
    for (int j = 1; j < field[0].size() - 1; j++) {
      // Part 1
      if (field[i][j] < field[i-1][j] &&
          field[i][j] < field[i+1][j] &&
          field[i][j] < field[i][j-1] &&
          field[i][j] < field[i][j+1]) {
        risk += (field[i][j] - '0') + 1;
      }

      // Part 2: BFS
      std::queue<std::pair<int,int>> todo;
      todo.push({i,j});
      int size = 0;
      while (!todo.empty()) {
        auto pos = todo.front();
        todo.pop();

        if (field[pos.first][pos.second] == '9' ||
            seen.find({pos.first,pos.second}) != seen.end()) continue;
        seen.insert({pos.first,pos.second});

        size++;

        todo.push({pos.first+1, pos.second});
        todo.push({pos.first-1, pos.second});
        todo.push({pos.first, pos.second+1});
        todo.push({pos.first, pos.second-1});
      }
      if (size > 0) bassins.push(size);
    }
  }

  std::cout << "Par 1: total risk: " << risk << "\n";

  std::cout << "Part 2: number of bassins: " << bassins.size() << ". ";
  std::cout << "Top 3 sizes: ";
  int prod = 1;
  for (int i = 0; i < 3; i++) {
    std::cout << bassins.top() << ", ";
    prod *= bassins.top();
    bassins.pop();
  }
  std::cout << "multiplied: " << prod << '\n';

}
