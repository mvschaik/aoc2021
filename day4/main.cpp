#include <iostream>
#include <unordered_set>
#include <array>
#include <numeric>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <cassert>

typedef std::unordered_set<int> Row;
typedef std::array<Row, 10> Card; // 5 rows, 5 cols

bool draw_number(int i, Card& card) {
  bool bingo = false;
  for (auto& row : card) {
    row.erase(i);
    if (row.empty()) bingo = true;
  }
  return bingo;
}

int score(const Card& card) {
  int sum = 0;
  for (int i = 0; i < 5; i++) {
    sum += std::accumulate(card[i].begin(), card[i].end(), 0);
  }
  return sum;
}

std::istream& operator>>(std::istream& is, Card& card) {
  std::string line;
  if (!std::getline(is, line)) return is;
  assert(line == "");
  for (int i = 0; i < 5; i++) {
    if (!std::getline(is, line)) return is;
    if (line == "") {i--; continue;}
    std::istringstream iss{line};
    for (int j = 0; j < 5; j++) {
      int value;
      iss >> value;
      card[i].insert(value);
      card[5+j].insert(value);
    }
  }
  return is;
}

int main(int argc, char* argv[]) {
  std::ifstream file{argv[1]};
  std::string line;
  std::getline(file, line);
  std::istringstream iss{line};
  std::vector<int> draws;
  std::string draw;
  while (std::getline(iss, draw, ',')) draws.push_back(std::stoi(draw));

  std::vector<Card> cards;
  while (true) {
    Card c;
    if (!(file >> c)) break;
    cards.push_back(c);
  }

  std::cout << "Got " << draws.size() << " draws and " << cards.size() << " cards\n";

  std::unordered_set<int> completed;
  for (int draw : draws) {
    std::cout << "Draw: " << draw << '\n';
    for (int i = 0; i < cards.size(); i++) {
      if (completed.find(i) != completed.end()) continue;
      if (draw_number(draw, cards[i])) {
        int value = score(cards[i]);
        completed.insert(i);
        std::cout << "Bingo! Card value is " << value << " for a score of " << value * draw << '\n';
        if (completed.size() == cards.size()) return 0;
      }
    }
  }
}
