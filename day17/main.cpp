#include <iostream>
#include <fstream>
#include <regex>
#include <unordered_set>

struct pairhash {
  template <typename T, typename U>
  std::size_t operator()(const std::pair<T, U> &x) const
  {
    return std::hash<T>()(x.first) ^ std::hash<U>()(x.second);
  }
};

int main(int argc, char* argv[]) {
  std::ifstream file{argv[1]};
  std::string line;
  if (!std::getline(file, line)) return 1;

  std::regex regex{R"(target area: x=(-?\d+)..(-?\d+), y=(-?\d+)..(-?\d+))"};
  std::smatch match;
  if (!std::regex_match(line, match, regex)) return 2;
  int x_min = std::stoi(match[1]);
  int x_max = std::stoi(match[2]);
  int y_min = std::stoi(match[3]);
  int y_max = std::stoi(match[4]);

  std::unordered_set<std::pair<int,int>, pairhash> hits;

  // First go over # steps.
  for (int initial_yv = -y_min, steps = 2;
       steps > 1;
       initial_yv--) {
    int top = 0;
    steps = 0;
    // Walk y trajectory.
    for (int yv = initial_yv, ypos = 0;
         ypos >= y_min;
         ypos += yv--) {

      top = std::max(top, ypos);

      if (ypos <= y_max) {
        // Now find xv.
        for (int initial_xv = x_max; initial_xv > 0; initial_xv--) {
          int xv = initial_xv;
          int xpos = 0;
          // Walk x trajectory.
          for (int i = 0; i < steps; i++) {
            xpos += xv;
            if (xv > 0) xv--;
          }

          if (x_min <= xpos && xpos <= x_max) {
            if (hits.empty()) {
              std::cout << "Hit using " << initial_xv << ',' <<  initial_yv 
                        << " in " << steps << " steps. Max height is " << top << '\n';
            }
            hits.insert({initial_xv, initial_yv});
          }
        }
      }

      steps++;
    }
  }

  std::cout << "Number of ways to hit: " << hits.size() << '\n';
}
