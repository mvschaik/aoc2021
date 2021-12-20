#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <unordered_map>
#include <sstream>
#include <climits>
#include <algorithm>

int main(int argc, char* argv[]) {
  std::ifstream file {argv[1]};
  std::string initial_line;
  std::getline(file, initial_line);

  std::unordered_map<std::string,std::string> rules;

  std::regex rule {R"((..) -> (.))"};
  std::string rule_line;
  while (getline(file, rule_line)) {
    std::smatch match;
    if (std::regex_match(rule_line, match, rule)) {
      rules[match[1]] = match[2];
    }
  }

  std::unordered_map<std::string,long> pair_counts;
  for (int i = 0; i < initial_line.size() - 1; i++) {
    pair_counts[initial_line.substr(i, 2)]++;
  }

  for (int i = 0; i < 40; i++) {
    std::unordered_map<std::string,long> new_pair_counts;
    for (const auto& [p, c] : pair_counts) {
      new_pair_counts[p[0] + rules[p]] += c;
      new_pair_counts[rules[p] + p[1]] += c;
    }
    pair_counts = new_pair_counts;

    if (i == 9 || i == 39) {
      std::unordered_map<char, long> char_counts;
      for (const auto& [p, c] : pair_counts) {
        char_counts[p[0]] += c;
      }
      char_counts[initial_line.back()]++; // Last char stays the same.

      const auto [min, max] = std::minmax_element(
            char_counts.begin(), char_counts.end(),
            [](const auto& a, const auto& b) { return a.second < b.second; });

      std::cout << "Result after " << i+1 << " iterations: " << (max->second - min->second) << '\n';
    }
  }
}
