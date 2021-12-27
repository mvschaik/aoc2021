#include <iostream>
#include <regex>
#include <fstream>
#include <array>
#include <set>
#include <unordered_map>
#include <unordered_set>

struct Coord {
    int x, y, z;

    bool operator==(const Coord& other) const {
        return x == other.x && y == other.y && z == other.z;
    }

    struct Hasher {
        std::size_t operator()(const Coord& c) const {
            return std::hash<size_t>()(
                std::hash<int>()(c.x)
                ^ std::hash<int>()(c.y)
                ^ std::hash<int>()(c.z));
        }
    };
};

struct Command {
  bool on;
  int minx, maxx, miny, maxy, minz, maxz;

  friend std::ostream& operator<<(std::ostream& os, const Command& c) {
    os << (c.on ? "on " : "off ");
    os << "x=" << c.minx << ".." << c.maxx-1;
    os << ",y=" << c.miny << ".." << c.maxy-1;
    return os << ",z=" << c.minz << ".." << c.maxz-1;
  }

};

constexpr int worldmin = -50;
constexpr int worldmax = 50;

std::regex pat{R"((on|off) x=(-?\d+)\.\.(-?\d+),y=(-?\d+)\.\.(-?\d+),z=(-?\d+)\.\.(-?\d+))"};

int main(int argc, char* argv[]) {
  std::ifstream file{argv[1]};

  std::array<std::array<std::array<bool,100>,100>,100> world = {{{false}}};
  int count = 0;

  std::set<int> xboundaries;
  std::set<int> yboundaries;
  std::set<int> zboundaries;

  std::vector<Command> commands;

  std::string line;
  while(std::getline(file, line)) {
    std::smatch sm;
    if (!std::regex_match(line, sm, pat)) { std::cerr << "Invalid line " << line << '\n'; continue; }
    bool on = sm[1] == "on";
    int minx = std::stoi(sm[2]), maxx = std::stoi(sm[3]);
    int miny = std::stoi(sm[4]), maxy = std::stoi(sm[5]);
    int minz = std::stoi(sm[6]), maxz = std::stoi(sm[7]);

    xboundaries.insert(minx); xboundaries.insert(maxx+1);
    yboundaries.insert(miny); yboundaries.insert(maxy+1);
    zboundaries.insert(minz); zboundaries.insert(maxz+1);
    commands.push_back({on, minx, maxx+1, miny, maxy+1, minz, maxz+1});

    if (maxx < worldmin || minx > worldmax
       || maxy < worldmin || miny > worldmax
       || maxz < worldmin || miny > worldmax) continue;

    std::cout << line << '\n';

    for (int x = std::max(worldmin, minx); x <= std::min(worldmax, maxx); x++) {
      for (int y = std::max(worldmin, miny); y <= std::min(worldmax, maxy); y++) {
        for (int z = std::max(worldmin, minz); z <= std::min(worldmax, maxz); z++) {
          bool& cube = world[x+50][y+50][z+50];
          if (on && !cube) count++;
          if (!on && cube) count--;
          cube = on;
        }
      }
    }
  }
  std::cout << "There are " << count << " cubes on in part 1\n";

  std::unordered_map<Coord,bool,Coord::Hasher> states;

  long long count2 = 0;

  int num_cubes = xboundaries.size() * yboundaries.size() * zboundaries.size();
  std::cout << "Using " << xboundaries.size() << " * "
            << yboundaries.size() << " * "
            << zboundaries.size() << " = " << num_cubes
            << " cube buckets\n";

  std::unordered_set<Coord,Coord::Hasher> processed;
  processed.reserve(num_cubes);
  Coord c;
  int n = 0;
  for (auto it = commands.rbegin(); it != commands.rend(); it++) {
    std::cout << '[' << ++n << '/' << commands.size() << "] " << *it << '\n';
    for (auto xit = xboundaries.begin(); *xit < it->maxx; xit++) {
      if (*xit < it->minx) continue;
      for (auto yit = yboundaries.begin(); *yit < it->maxy; yit++) {
        if (*yit < it->miny) continue;
        for (auto zit = zboundaries.begin(); *zit < it->maxz; zit++) {
          if (*zit < it->minz) continue;
          c = {*xit, *yit, *zit};
          auto r = processed.insert(c);
          if (!r.second) continue;

          if (it->on) {
            long long cube_size = (long long)(*next(xit) - *xit)
                                * (long long)(*next(yit) - *yit)
                                * (long long)(*next(zit) - *zit);
            count2 += cube_size;
          }
        }
      }
    }
  }
  std::cout << "There are " << count2 << " cubes on in part 2\n";
}
