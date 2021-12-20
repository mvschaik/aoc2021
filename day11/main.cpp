#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

void inc(std::vector<std::vector<int>>& grid, int row, int col) {
  if (++grid[row][col] == 10) {
    if (row > 0 && col > 0) inc(grid, row-1, col-1);
    if (col > 0) inc(grid, row, col-1);
    if (row < grid.size()-1 && col > 0) inc(grid, row+1, col-1);
    if (row > 0) inc(grid, row-1, col);
    if (row < grid.size()-1) inc(grid, row+1, col);
    if (row > 0 && col < grid[0].size()-1) inc(grid, row-1, col+1);
    if (col < grid[0].size()-1) inc(grid, row, col+1);
    if (row < grid.size()-1 && col < grid[0].size()-1) inc(grid, row+1, col+1);
  }
}


int main(int argc, char* argv[]) {
  std::ifstream file{argv[1]};

  std::vector<std::vector<int>> grid;
  std::string line;
  while (std::getline(file, line)) {
    std::vector<int> iline;
    std::transform(line.begin(), line.end(), 
                   std::back_inserter(iline), 
                   [](char c){return c - '0';});
    grid.push_back(iline);
  }

  int flashes = 0;
  int iteration = 0;
  while (++iteration) {
    for (int row = 0; row < grid.size(); row++) {
      for (int col = 0; col < grid[0].size(); col++) {
        inc(grid, row, col);
      }
    }
    int new_flashes = 0;
    for (int row = 0; row < grid.size(); row++) {
      for (int col = 0; col < grid[0].size(); col++) {
        if (grid[row][col] > 9) {
          new_flashes++;
          grid[row][col] = 0;
        }
      }
    }
    if (iteration < 100) flashes += new_flashes;
    if (new_flashes == grid.size() * grid[0].size()) break;
  }

  std::cout << "Number of flashes: " << flashes << '\n';
  std::cout << "First sync flash at iteration: " << iteration << '\n';
}
