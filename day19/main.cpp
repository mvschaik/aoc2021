#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <algorithm>
#include <cassert>
#include <regex>
#include <set>

typedef std::array<int,3> Pos;
typedef std::set<Pos> Scanner;
typedef std::array<std::array<int,3>,3> Matrix;

Pos operator+(const Pos& p1, const Pos& p2) {
  return {p1[0] + p2[0], p1[1] + p2[1], p1[2] + p2[2]};
}

Pos operator-(const Pos& p1, const Pos& p2) {
  return {p1[0] - p2[0], p1[1] - p2[1], p1[2] - p2[2]};
}

std::ostream& operator<<(std::ostream& os, const Pos& p) {
  return os << p[0] << ',' << p[1] << ',' << p[2];
}

Matrix operator*(const Matrix& m1, const Matrix& m2) {
  std::function<int(int,int)> value = [&](int row, int col){
    int sum = 0;
    for (int t = 0; t < 3; t++) sum += m1[row][t]*m2[t][col];
    return sum;
  };
  return {{
    {value(0,0), value(0,1), value(0,2)},
    {value(1,0), value(1,1), value(1,2)},
    {value(2,0), value(2,1), value(2,2)}
  }};
}

std::set<Matrix> rotation_matrices;
void calculate_rotation_matrices() {
  Matrix xrot = {{
    {1, 0,  0},
    {0, 0, -1},
    {0, 1,  0}
  }};
  Matrix yrot = {{
    { 0, 0, 1},
    { 0, 1, 0},
    {-1, 0, 0}
  }};
  Matrix zrot = {{
    {0, -1, 0},
    {1,  0, 0},
    {0,  0, 1}
  }};

  Matrix m = {{
    {1, 0, 0},
    {0, 1, 0},
    {0, 0, 1}
  }};
  rotation_matrices.insert(m);
  for (int x = 0; x < 3; x++) {
    for (int y = 0; y < 5; y++) {
      for (int z = 0; z < 4; z++) {
        m = m * zrot;
        rotation_matrices.insert(m);
      }
      m = m * yrot;
      rotation_matrices.insert(m);
    }
    m = m * xrot;
    rotation_matrices.insert(m);
  }
  assert(rotation_matrices.size() == 24);
}

Pos operator*(const Matrix& m, const Pos& p) {
    return {m[0][0]*p[0] + m[1][0]*p[1] + m[2][0]*p[2],
            m[0][1]*p[0] + m[1][1]*p[1] + m[2][1]*p[2],
            m[0][2]*p[0] + m[1][2]*p[1] + m[2][2]*p[2]};
}

const std::regex line_fmt{R"((-?\d+),(-?\d+),(-?\d+))"};
const std::regex header_fmt{R"(--- scanner \d+ ---)"};

struct Match {
  Pos offset;
  Matrix rotation;
};

std::vector<Scanner> read_scanners(std::string filename) {
  std::ifstream file{filename};

  std::vector<Scanner> scanners;
  Scanner s;
  std::string line;
  while (std::getline(file, line)) {
    if (std::regex_match(line, header_fmt)) continue;
    if (line == "") {
      scanners.push_back(s);
      s = Scanner();
      continue;
    }

    std::smatch match;
    if (!std::regex_match(line, match, line_fmt)) {
      std::cout << "Unable to parse line " << line << '\n';
    }

    Pos p{std::stoi(match[1]),
          std::stoi(match[2]),
          std::stoi(match[3])};
    s.insert(p);
  }
  scanners.push_back(s);
  return scanners;
}

std::optional<Match> matches(const Scanner& s1, const Scanner& s2) {
  for (const auto& m : rotation_matrices) {
    for (const auto& r1 : s1) {
      for (const auto& r2 : s2) {
        const Pos offset = r1 - m*r2;

        int matches = std::count_if(s2.cbegin(), s2.cend(), [&](auto p2){
          return s1.find(m*p2 + offset) != s1.end();
        });
        // Must match at least element for which the offset was calculated
        assert(matches > 0);
        if (matches >= 12) return {{offset, m}};
      }
    }
  }
  return {};
}

int distance(const Pos& p1, const Pos& p2) {
  return std::abs(p1[0]-p2[0]) + std::abs(p1[1]-p2[1]) + std::abs(p1[2]-p2[2]);
}

int main(int argc, char* argv[]) {
  std::vector<Scanner> scanners = read_scanners(argv[1]);
  Scanner world = scanners[0];

  calculate_rotation_matrices();

  std::set<Pos> scanner_positions = {{0,0,0}};
  std::set<int> matched = {0};
  while (matched.size() < scanners.size()) {
    for (int i = 1; i < scanners.size(); i++) {
      if (matched.find(i) != matched.end()) continue;

      std::cout << "Checking scanner " << i;
      auto match = matches(world, scanners[i]);
      if (match.has_value()) {
        std::cout << " matched! (" << scanners.size() - matched.size() << " left)\n";
        std::transform(scanners[i].begin(), scanners[i].end(), 
                       std::inserter(world, world.begin()),
                       [&](auto p){ return match->rotation*p + match->offset; });
        matched.insert(i);
        scanner_positions.insert(match->offset);
      } else {
        std::cout << " no match...\n";
      }
    }
  }

  std::cout << "Number of beacons: " << world.size() << '\n';

  int max_dist = 0;
  for (const auto& b1 : scanner_positions) {
    for (const auto& b2 : scanner_positions) {
      max_dist = std::max(max_dist, distance(b1, b2));
    }
  }
  std::cout << "Maximum distance between scanners: " << max_dist << '\n';
}
