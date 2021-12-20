#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <cassert>
#include <regex>
#include <string>

const std::regex number { R"(\d+)" };
const std::regex large_number { R"(\d\d+)" };

std::string reduce(std::string);

std::string split(std::string s) {
  std::smatch sm;
  if (std::regex_search(s, sm, large_number)) {
    std::ostringstream oss;
    oss << sm.prefix();
    int n = std::stoi(sm.str());
    int half = n / 2;
    oss << '[' << half << ','
        << ((2*half < n) ? half+1 : half)
        << ']'
        << sm.suffix();
    return reduce(oss.str());
  }
  return s;

}

std::pair<int,int> parse_pair(const std::string& s) {
  std::smatch match;
  std::regex_search(s, match, number);
  int first = std::stoi(match.str());
  std::string rest = match.suffix();
  std::regex_search(rest, match, number);
  return {first, std::stoi(match.str())};
}

std::string add_to_last_number(int i, std::string s) {
  std::ostringstream oss;
  std::smatch sm;
  std::string prev_num;
  while (std::regex_search(s, sm, number)) {
    oss << prev_num;
    oss << sm.prefix();
    prev_num = sm.str();
    s = sm.suffix();
  }
  if (prev_num.size()) oss << std::stoi(prev_num) + i;
  oss << s;
  return oss.str();
}

std::string add_to_first_number(int i, std::string s) {
  std::ostringstream oss;
  std::smatch sm;
  if (std::regex_search(s, sm, number)) {
    oss << sm.prefix() << std::stoi(sm.str()) + i << sm.suffix();
  } else {
    oss << s;
  }
  return oss.str();
}

std::string reduce(std::string s) {
  int depth = 0;

  for (int i = 0; i < s.size(); i++) {
    switch (s[i]) {
      case '[': depth++; break;
      case ']': depth--; break;
    }
    if (depth > 4) {

      std::ostringstream oss;

      std::smatch digits_before;
      std::string first_part = s.substr(0, i);
      int end_of_pair = s.find(']', i) + 1;
      auto [first, last] = parse_pair(s.substr(i, end_of_pair-i));
      std::string last_part = s.substr(end_of_pair);

      oss << add_to_last_number(first, first_part) << 0 << add_to_first_number(last, last_part);

      return reduce(oss.str());
    }
  }
  return split(s);
}

int magnitude(std::string::const_iterator& it) {
  if (std::isdigit(*it)) return (*(it++)) - '0';
  int first, second;
  while (true) {
    switch (*it) {
      case '[':
        it++;
        first = magnitude(it);
        break;
      case ',':
        it++;
        second = magnitude(it);
        break;
      case ']':
        it++;
        return 3*first + 2*second;
    }
  }
}

int magnitude(const std::string& s) {
  auto it = s.begin();
  return magnitude(it);
}

int main(int argc, char* argv[]) {
  assert(reduce("[[[[[9,8],1],2],3],4]") == "[[[[0,9],2],3],4]");
  assert(reduce("[7,[6,[5,[4,[3,2]]]]]") == "[7,[6,[5,[7,0]]]]");
  assert(reduce("[[6,[5,[4,[3,2]]]],1]") == "[[6,[5,[7,0]]],3]");
  assert(reduce("[[3,[2,[8,0]]],[9,[5,[4,[3,2]]]]]") == "[[3,[2,[8,0]]],[9,[5,[7,0]]]]");
  assert(reduce("[[[[[4,3],4],4],[7,[[8,4],9]]],[1,1]]") == "[[[[0,7],4],[[7,8],[6,0]]],[8,1]]");
  assert(magnitude("[[[[8,7],[7,7]],[[8,6],[7,7]]],[[[0,7],[6,6]],[8,7]]]") == 3488);

  std::ifstream file{argv[1]};
  std::string line;
  std::vector<std::string> lines;
  while (std::getline(file, line)) lines.push_back(line);

  std::string sum;
  for (const auto& line : lines) {
    if (sum.empty()) { sum = line; continue; }
    sum = reduce("[" + sum + "," + line + "]");
  }
  std::cout << "Total sum: " << magnitude(sum) << '\n';

  int max = 0;
  // 100*99 additions...
  for (int i = 0; i < lines.size(); i++) {
    for (int j = 0; j < lines.size(); j++) {
      if (i == j) continue;
      max = std::max(max, magnitude(reduce("[" + lines[i] + "," + lines[j] + "]")));
    }
    std::cout << 100*(i+1)/lines.size() << "% ... " << std::flush;
  }
  std::cout << "\nMax: " << max << '\n';
}
