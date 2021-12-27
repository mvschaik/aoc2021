#include <iostream>
#include <array>
#include <regex>
#include <vector>
#include <string>
#include <fstream>

typedef long long ll;

ll proc(ll input, ll carry, bool p1, ll p2, ll p3) {
  ll result = carry;
  if (p1) result /= 26;
  if (input != (carry % 26) + p2) {
    result *= 26;
    result += input + p3;
  }
  return result;
}

// cx = carry for digit x, ix = input for digit x.
// 0   -> c0  =             i0 + 1
// 1   -> c1  = (c0 * 26) + i1 + 7
// 2   -> c2  = (c1 * 26) + i2 + 13
// 3   t> c3  = (c1 * 26) + i3 + 10    ||  i3 ==  i2 + 13 - 6 == i2 + 7
// 4   -> c4  = (c3 * 26) + i4 + 0
// 5   t> c5  = (c3 * 26) + i5 + 13    ||  i5 ==  i4 + 0  - 4 == i4 - 4
// 6   -> c6  = (c5 * 26) + i6 + 11
// 7   -> c7  = (c6 * 26) + i7 + 6
// 8   -> c8  = (c7 * 26) + i8 + 1
// 9   t> c9  = (c7 * 26) + i9 + 7     ||  i9 == i8 + 1 + 0  == i8 + 1
// 10  t> c10 = (c7 * 26) + i10 + 11   ||  i10 == i9 + 7 + 0 == i9 + 7
// 11  t> c11 = (c7 * 26) + i11 + 14   ||  i11 == i10 + 11 - 3 == i10 + 8
// 12  t> c12 = (c7 * 26) + i12 + 4    ||  i12 == i11 + 14 - 9 == i11 + 5
// 13  t> c13 = (c7 * 26) + i13 + 10   ||  i13 == i12 + 4 - 9 == i12 - 5

bool validate(std::array<ll,14> nums) {
  ll carry = 0;
  carry = proc(nums[0],  carry, false, 14,  1);
  carry = proc(nums[1],  carry, false, 15,  7);
  carry = proc(nums[2],  carry, false, 15, 13);
  carry = proc(nums[3],  carry, true,  -6, 10);
  carry = proc(nums[4],  carry, false, 14,  0);
  carry = proc(nums[5],  carry, true,  -4, 13);
  carry = proc(nums[6],  carry, false, 15, 11);
  carry = proc(nums[7],  carry, false, 15,  6);
  carry = proc(nums[8],  carry, false, 11,  1);
  carry = proc(nums[9],  carry, true,   0,  7);
  carry = proc(nums[10], carry, true,   0, 11);
  carry = proc(nums[11], carry, true,  -3, 14);
  carry = proc(nums[12], carry, true,  -9,  4);
  carry = proc(nums[13], carry, true,  -9, 10);
  return carry == 0;
}

std::regex instr{R"((inp|mul|add|mod|div|eql) (\S+)(?: (\S+))?)"};

int exec(std::vector<std::string> prog, std::array<ll,14> input) {
  std::array<ll, 4> mem = {0,0,0,0};
  int ip = 0;

  for (auto i : prog) {
    std::smatch sm;
    if (!std::regex_match(i, sm, instr)) std::cerr << "Invalid instruction " << i;
    int dest = sm[2].str()[0] - 'w';
    if (sm[1] == "inp") {
      mem[dest] = input[ip++];
    }
    else {
      int op;
      if (sm[3] == "w" || sm[3] == "x" || sm[3] == "y" || sm[3] == "z") {
        op = mem[sm[3].str()[0] - 'w'];
      } else {
        op = std::stoi(sm[3]);
      }
      if (sm[1] == "mul") {
        mem[dest] *= op;
      }
      else if (sm[1] == "add") {
        mem[dest] += op;
      }
      else if (sm[1] == "mod") {
        mem[dest] %= op;
      }
      else if (sm[1] == "div") {
        mem[dest] /= op;
      }
      else if (sm[1] == "eql") {
        mem[dest] = mem[dest] == op;
      }
    }
  }
  return mem[3];
}

std::vector<std::string> read_prog(std::string filename) {
  std::vector<std::string> prog;
  std::ifstream file{filename};
  std::string line;
  while (std::getline(file, line)) prog.push_back(line);
  return prog;
}

int main(int argc, char* argv[]) {
  std::array<ll,14> num = {9,9,2,9, 9,5, 9,9, 9,9, 9,9,9,9};
  for (ll i6 = 9; i6 > 0; i6--) {
    num[6] = i6;
    for (ll i7 = 9; i7 > 0; i7--) {
      num[7] = i7;
      for (ll i8 = 9; i8 > 0; i8--) {
        num[8] = i8;
        for (ll i9 = 9; i9 > 0; i9--) {
          num[9] = i9;
          for (ll i10 = 9; i10 > 0; i10--) {
            num[10] = i10;
            for (ll i11 = 9; i11 > 0; i11--) {
              num[11] = i11;
              for (ll i12 = 9; i12 > 0; i12--) {
                num[12] = i12;
                for (ll i13 = 9; i13 > 0; i13--)  {
                  num[13] = i13;
                  if (validate(num)) {
                    std::cout << "Solution part 1: ";
                    for (auto c : num) std::cout << c;
                    std::cout << '\n';
                    std::cout << "Check: " << exec(read_prog(argv[1]), num) << '\n';
                    goto part1done;
                  }
                }
              }
            }
          }
        }
      }
    }
  }
part1done:

  std::array<ll,14> min;
  for (ll i0 = 1; i0 < 10; i0++) {
    min[0] = i0;
    for (ll i1 = 1; i1 < 10; i1++) {
      min[1] = i1;
      for (ll i2 = 1; i2 < 3; i2++) {
        min[2] = i2;
        min[3] = i2 + 7;
        for (ll i4 = 5; i4 < 10; i4++) {
          min[4] = i4;
          min[5] = i4 - 4;
          for (ll i6 = 1; i6 < 10; i6++) {
            min[6] = i6;
            for (ll i7 = 1; i7 < 10; i7++) {
              min[7] = i7;
              for (ll i8 = 1; i8 < 9; i8++) {
                min[8] = i8;
                min[9] = i8 + 1;
                for (ll i10 = 1; i10 < 10; i10++) {
                  min[10] = i10;
                  for (ll i11 = 1; i11 < 10; i11++) {
                    min[11] = i11;
                    for (ll i12 = 1; i12 < 10; i12++) {
                      min[12] = i12;
                      for (ll i13 = 1; i13 < 10; i13++) {
                        min[13] = i13;
                        if (validate(min)) {
                          std::cout << "Solution part 2: ";
                          for (auto c : min) std::cout << c;
                          std::cout << '\n';
                          std::cout << "Check: " << exec(read_prog(argv[1]), min) << '\n';
                          return 0;
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}
