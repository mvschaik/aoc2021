#include <iostream>
#include <fstream>
#include <unordered_set>
#include <regex>

struct Pos {
  int x, y;

  bool operator==(const Pos& other) const {
    return x == other.x && y == other.y;
  }

  struct Hasher {
    size_t operator()(const Pos& p) const {
      return std::hash<int>()(p.x) ^ std::hash<int>()(p.y);
    }
  };

  friend std::ostream& operator<<(std::ostream& os, const Pos& pos) {
    return os << pos.x << ',' << pos.y;
  }
};

typedef std::unordered_set<Pos, Pos::Hasher> Grid;

void print_grid(const Grid& grid) {
  int max_x = 0, max_y = 0;
  for (const auto& p : grid) {
    max_x = std::max(max_x, p.x);
    max_y = std::max(max_y, p.y);
  }
  for (int y = 0; y <= max_y; y++) {
    for (int x = 0; x <= max_x; x++) {
      if (grid.find(Pos{x, y}) != grid.end()) {
        std::cout << '#';
      } else {
        std::cout << ' ';
      }
    }
    std::cout << '\n';
  }
}

int main(int argc, char* argv[]) {
  std::ifstream file{argv[1]};
  std::string line;
  Grid grid;
  while (std::getline(file, line) && line != "") {
    auto sep = line.find(",");
    grid.insert(Pos{std::stoi(line.substr(0, sep)), 
                    std::stoi(line.substr(sep+1))});
  }

  std::cout << "Intial size: " << grid.size() << '\n';
  // print_grid(grid);

  std::regex fold_pat {R"(fold along (x|y)=(\d+))"};
  while (std::getline(file, line)) {
    std::smatch match;
    if (std::regex_match(line, match, fold_pat)) {
      std::string x_or_y = match[1];
      int fold_pos = std::stoi(match[2]);
      std::cout << "Folding along " << x_or_y << " at position " << fold_pos << '\n';
      std::vector<Pos> to_add;
      std::vector<Grid::iterator> to_remove;
      for (auto it = grid.begin(); it != grid.end(); it++) {
        if ((x_or_y == "x" ? it->x : it->y) > fold_pos) {
          to_add.push_back(x_or_y == "x" ? Pos{2*fold_pos - it->x, it->y} : 
                                           Pos{it->x, 2*fold_pos - it->y});
          to_remove.push_back(it);
        }
      }
      for (auto p : to_add) grid.insert(p);
      for (auto it : to_remove) grid.erase(it);
    }
    std::cout << "Size: " << grid.size() << '\n';
  }
  print_grid(grid);
}
