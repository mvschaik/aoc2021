#include <iostream>
#include <fstream>
#include <array>
#include <queue>
#include <stack>
#include <map>
#include <vector>
#include <climits>

int room_size = 2;

struct State {
  std::array<char,11> hall{'.','.','.','.','.','.','.','.','.','.','.'};
  std::map<char,std::vector<char>> rooms;
  int cost {0};
};

std::ostream& operator<<(std::ostream& os, const State& s) {
  os << "#############\n";
  os << '#';
  for (char c : s.hall) os << c;
  os << "#\n";
  os << "###";
  for (char room : {'A', 'B', 'C', 'D'}) {
    os << (s.rooms.at(room).size() == room_size ? s.rooms.at(room)[room_size-1] : '.') << '#';
  }
  os << "##\n";
  os << "  #";
  for (int i = 0; i < room_size - 1; i++) {
    for (char room : {'A', 'B', 'C', 'D'}) {
      int idx = room_size -1 - i;
      os << (s.rooms.at(room).size() >= idx-1 ? s.rooms.at(room)[idx] : '.') << '#';
    }
  }
  return os << "\n  #########\nCost: " << s.cost;  
}

const std::map<char,int> costs = {
  {'A', 1},
  {'B', 10},
  {'C', 100},
  {'D', 1000},
};

const std::map<char,std::vector<std::vector<std::pair<int,int>>>> reachable_from_room = {
  {'A', {{{1, 2}, {0, 3}},
         {{3, 2}, {5, 4}, {7, 6}, {9, 8}, {10, 9}}}},
  {'B', {{{3, 2}, {1, 4}, {0, 5}},
         {{5, 2}, {7, 4}, {9, 6}, {10, 7}}}},
  {'C', {{{5, 2}, {3, 4}, {1, 6}, {0, 7}},
         {{7, 2}, {9, 4}, {10, 5}}}},
  {'D', {{{7, 2}, {5, 4}, {3, 6}, {1, 8}, {0, 9}},
         {{9, 2}, {10, 3}}}}
};

bool is_complete(const State& s) {
  for (auto [room, contents] : s.rooms) {
    if (contents.size() != room_size) return false;
    for (int i = 0; i < room_size; i++) {
      if (contents[i] != room) return false;
    }
  }
  return true;
}

State read_state(std::istream& is) {
  State s0;
  std::string line, line2;
  std::getline(is, line);  // #############
  std::getline(is, line);  // #01234567890#
  std::getline(is, line2); // ###B#C#B#D###
  std::getline(is, line);  //   #B#C#B#D#
  s0.rooms['A'].push_back(line[3]);
  if (room_size == 4) {
    s0.rooms['A'].push_back('D');
    s0.rooms['A'].push_back('D');
  }
  s0.rooms['A'].push_back(line2[3]);
  s0.rooms['B'].push_back(line[5]);
  if (room_size == 4) {
    s0.rooms['B'].push_back('B');
    s0.rooms['B'].push_back('C');
  }
  s0.rooms['B'].push_back(line2[5]);
  s0.rooms['C'].push_back(line[7]);
  if (room_size == 4) {
    s0.rooms['C'].push_back('A');
    s0.rooms['C'].push_back('B');
  }
  s0.rooms['C'].push_back(line2[7]);
  s0.rooms['D'].push_back(line[9]);
  if (room_size == 4) {
    s0.rooms['D'].push_back('C');
    s0.rooms['D'].push_back('A');
  }
  s0.rooms['D'].push_back(line2[9]);
  return s0;
}

int main(int argc, char* argv[]) {
  if (argv[1][0] == '2') room_size = 4;

  std::ifstream file{argv[2]};
  State s0 = read_state(file);;

  std::stack<State, std::vector<State>> q;
  q.push(s0);
  int min_cost = 50000;
  while (!q.empty()) {
    State s = q.top();
    q.pop();
    if (s.cost >= min_cost) continue;

    for (const auto& [room, contents] : s.rooms) {
      // Walk from room to hall.
      if (std::any_of(contents.cbegin(), contents.cend(), [&,r=room](auto c){return c != r;})) {
        for (const auto& path : reachable_from_room.at(room)) {
          for (const auto& [pos, cost] : path) {
            if (s.hall[pos] != '.') break;
            State ns = s;
            ns.cost += (room_size-contents.size() + cost)*costs.at(contents.back());
            if (ns.cost >= min_cost) break;
            ns.hall[pos] = contents.back();
            ns.rooms[room].pop_back();

            q.push(ns);
          }
        }
      }

      // Walk from hall to room.
      if (contents.size() < room_size &&
          std::all_of(contents.cbegin(), contents.cend(), [&,r=room](auto c){return c == r;})) {
        for (const auto& path : reachable_from_room.at(room)) {
          for (const auto& [pos, cost] : path) {
            if (s.hall[pos] == room) {
              State ns = s;
              ns.cost += (room_size-1-contents.size() + cost)*costs.at(room);
              if (ns.cost >= min_cost) break;
              ns.hall[pos] = '.';
              ns.rooms[room].push_back(room);
              if (is_complete(ns)) {
                std::cout << "Completed with cost " << ns.cost << '\n';
                min_cost = std::min(min_cost, ns.cost);
              } else {
                q.push(ns);
              }
              break;
            } else if (s.hall[pos] != '.') break;
          }
        }
      }
    }
  }
  std::cout << "Min cost: " << min_cost << '\n';
}
