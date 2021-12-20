#include <iostream>
#include <fstream>
#include <stack>
#include <unordered_map>
#include <vector>
#include <algorithm>

const std::unordered_map<char, int> scores {
  {')', 3},
  {']', 57},
  {'}', 1197},
  {'>', 25137},
};

const std::unordered_map<char, int> complete_scores {
  {'(', 1},
  {'[', 2},
  {'{', 3},
  {'<', 4},
};

const std::unordered_map<char, char> matches {
  {'(',')'},
  {'[',']'},
  {'{','}'},
  {'<','>'},
};

typedef unsigned long long ull;

int main(int argc, char* argv[]) {
  std::ifstream file{argv[1]};
  std::string line;
  int score = 0;
  std::vector<ull> score2;
  while (std::getline(file, line)) {
    ull complete_score = 0ull;
    std::stack<char> s;
    for (char c : line) {
      switch (c) {
        case '(':
        case '{':
        case '<':
        case '[':
          s.push(c);
          break;
        case ')':
        case '}':
        case '>':
        case ']':
          if (c != matches.at(s.top())) {
            score += scores.at(c);
            goto invalid;
          }
          s.pop();
          break;
      }
    }

    while (!s.empty()) {
      complete_score *= 5;
      complete_score += complete_scores.at(s.top());
      s.pop();
    }
    score2.push_back(complete_score);

    invalid:;
  }

  std::cout << "Score: " << score << "\n";
  std::sort(score2.begin(), score2.end());
  std::cout << "Autocomplete score: " << score2[score2.size()/2] << "\n";
}
