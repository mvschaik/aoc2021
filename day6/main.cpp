#include <iostream>
#include <vector>
#include <fstream>
#include <array>
#include <numeric>

typedef unsigned long long ull;

int main(int argc, char* argv[]) {
  std::ifstream file{argv[1]};
  std::string n;
  std::array<ull, 9> fish{0};
  while (std::getline(file, n, ',')) fish[std::stol(n)]++;

  for (int i = 0; i < 256; i++) {
    ull spawns = fish[0];
    for (int j = 0; j < fish.size() - 1; j++) {
      fish[j] = fish[j+1];
    }
    fish[8] = spawns;
    fish[6] += spawns;

    std::cout << "Iteration " << (i+1) << ": " 
              << std::accumulate(fish.begin(), fish.end(), 0ull) << " fish.\n";
  }
}
