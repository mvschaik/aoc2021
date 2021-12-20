#include <iostream>
#include <fstream>
#include <regex>
#include <unordered_map>

struct Pos {
  int x, y;

  Pos operator+(const Pos& other) const {
    return Pos{x + other.x, y + other.y};
  }

  Pos operator-(const Pos& other) const {
    return Pos{x - other.x, y - other.y};
  }

  Pos& operator+=(const Pos& other) {
    return *this = *this + other;
  }

  bool operator==(const Pos& other) const {
    return x == other.x && y == other.y;
  }

  bool operator!=(const Pos& other) const {
    return x != other.x || y != other.y;
  }

  friend std::ostream& operator<<(std::ostream& os, const Pos& pos) {
    return os << pos.x << ',' << pos.y;
  }

  struct HashFunction
  {
    size_t operator()(const Pos& p) const
    {
      return std::hash<int>()(p.x) ^ std::hash<int>()(p.y);
    }
  };
};

typedef std::unordered_map<Pos,int, Pos::HashFunction> Field;

std::ostream& operator<<(std::ostream& os, const Field& field) {
  int max_x = 0, max_y = 0;
  for (auto [p, c] : field) {
    if (p.x > max_x) max_x = p.x;
    if (p.y > max_y) max_y = p.y;
  }
  for (int y = 0; y <= max_y; y++) {
    for (int x = 0; x <= max_x; x++) {
      Pos p{x, y};
      if (field.find(p) == field.end()) os << '.';
      else os << field.at(p);
      os << ' ';
    }
    os << '\n';
  }
  return os;
}

int main(int argc, char* argv[]) {
  std::regex pat{R"((\d+),(\d+) -> (\d+),(\d+))"};

  Field field;

  int overlaps = 0;
  std::ifstream file{argv[2]};
  std::string line;
  std::smatch match;
  while (std::getline(file, line)) {
    if (!std::regex_match(line, match, pat)) std::cout << "Malformed line " << line << '\n';
    Pos p1{std::stoi(match[1].str()), std::stoi(match[2].str())};
    Pos p2{std::stoi(match[3].str()), std::stoi(match[4].str())};

    if (argv[1][0] == '1' && p1.x != p2.x && p1.y != p2.y) continue;

    Pos slope{0,0};
    if (p2.x > p1.x) slope.x = 1;
    else if (p1.x > p2.x) slope.x = -1;
    if (p2.y > p1.y) slope.y = 1;
    else if (p1.y > p2.y) slope.y = -1;

    Pos i = p1 - slope;
    do {
      i += slope;
      if (++field[i] == 2) overlaps++;
    } while (i != p2);
  }

  std::cout << "Number of overlapping points: " << overlaps << '\n';
}
