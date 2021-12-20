#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

int main(int argc, char* argv[]) {
  std::ifstream file{argv[1]};
  std::string num;
  std::vector<int> positions;
  while (std::getline(file, num, ',')) positions.push_back(std::stoi(num));
  int max = *std::max_element(positions.begin(), positions.end());

  std::vector<int> costs;
  int prev = 0;
  for (int i = 1; i <= max+1; i++) {
    costs.push_back(prev);
    prev += i;
  }

  int min_cost1 = INT32_MAX;
  int min_cost2 = INT32_MAX;
  for (int i = 0; i <= max; i++) {
    int cost1 = 0;
    int cost2 = 0;
    for (int p : positions) {
      cost1 += std::abs(p - i);
      cost2 += costs[std::abs(p - i)];
    }
    min_cost1 = std::min(cost1, min_cost1);
    min_cost2 = std::min(cost2, min_cost2);
  }

  std::cout << "Part 1: cheapest is " << min_cost1 << "\n";
  std::cout << "Part 2: cheapest is " << min_cost2 << "\n";
}
