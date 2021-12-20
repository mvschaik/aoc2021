#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <functional>
#include <algorithm>
#include <numeric>

typedef unsigned long long ResT;

int read_bits(const std::vector<uint8_t>& data, int offset, int size) {
  int result = 0;
  int byte_index = offset / 8;
  int bit_offset = offset - (byte_index*8);
  while (size > 0) {
    int size_in_byte = std::min(size, 8 - bit_offset);
    result <<= size_in_byte;
    uint8_t mask = 0xff >> (8 - size_in_byte);
    result |= ((data[byte_index] >> (8 - size_in_byte - bit_offset)) & mask);

    size -= size_in_byte;
    bit_offset = 0;
    byte_index++;
  }
  return result;
}

int read_and_progress(const std::vector<uint8_t>& data, int& offset, int size) {
  int result = read_bits(data, offset, size);
  offset += size;
  return result;
}

int read_version(const std::vector<uint8_t>& data, int& offset) {
  return read_and_progress(data, offset, 3);
}

enum TypeId {
  SUM = 0,
  PROD = 1,
  MIN = 2,
  MAX = 3,
  LITERAL = 4,
  GT = 5,
  LT = 6,
  EQ = 7,
};

TypeId read_typeid(const std::vector<uint8_t>& data, int& offset) {
  TypeId t = (TypeId)read_and_progress(data, offset, 3);
  return t;
}

ResT read_literal(const std::vector<uint8_t>& data, int& offset) {
  ResT result = 0;
  bool more = true;
  while (more) {
    result <<= 4;
    int chunk = read_and_progress(data, offset, 5);
    result |= chunk & 0xf;
    more = (chunk >> 4) & 1;
  }
  return result;
}

enum LengthType {
  BITS, PACKETS
};

LengthType read_length_type(const std::vector<uint8_t>& data, int& offset) {
  return read_and_progress(data, offset, 1) == 0 ? LengthType::BITS : LengthType::PACKETS;
}

int read_length_in_bits(const std::vector<uint8_t>& data, int& offset) {
  return read_and_progress(data, offset, 15);
}

int read_length_in_packets(const std::vector<uint8_t>& data, int& offset) {
  return read_and_progress(data, offset, 11);
}

ResT eval_packet(const std::vector<uint8_t>&, int&);

std::vector<ResT> read_subpackets(const std::vector<uint8_t>& data, int& offset) {
  std::vector<ResT> result;
  if (read_length_type(data, offset) == LengthType::BITS) {
    int length = read_length_in_bits(data, offset);
    int end_offset = offset + length;
    while (offset < end_offset) {
      result.push_back(eval_packet(data, offset));
    }
  } else {
    int length = read_length_in_packets(data, offset);
    for (int i = 0; i < length; i++) {
      result.push_back(eval_packet(data, offset));
    }
  }
  return result;
}

ResT eval_sum(const std::vector<ResT>& packets) {
  return std::accumulate(packets.begin(), packets.end(), 0ull);
}

ResT eval_prod(const std::vector<ResT>& packets) {
  return std::accumulate(packets.begin(), packets.end(), 1ull,
                         [](ResT a, ResT b){return a*b;});
}

ResT eval_min(const std::vector<ResT>& packets) {
  return *std::min_element(packets.begin(), packets.end()); 
}

ResT eval_max(const std::vector<ResT>& packets) {
  return *std::max_element(packets.begin(), packets.end());
}

ResT eval_gt(const std::vector<ResT>& packets) {
  assert(packets.size() == 2);
  return packets[0] > packets[1] ? 1 : 0;
}

ResT eval_lt(const std::vector<ResT>& packets) {
  assert(packets.size() == 2);
  return packets[0] < packets[1] ? 1 : 0;
}

ResT eval_eq(const std::vector<ResT>& packets) {
  assert(packets.size() == 2);
  return packets[0] == packets[1] ? 1 : 0;
}

std::vector<std::function<ResT(const std::vector<ResT>&)>> evals = {
  &eval_sum, &eval_prod, &eval_min, &eval_max, /*eval_lit*/nullptr,
  &eval_gt, &eval_lt, &eval_eq
};

ResT eval_packet(const std::vector<uint8_t>& data, int& offset) {
  read_version(data, offset);
  int op = read_typeid(data, offset);
  if (op == TypeId::LITERAL) {
    long res = read_literal(data, offset);
    return res;
  }
  std::vector<ResT> subpackets = read_subpackets(data, offset);
  return evals[op](subpackets);
}

int sum_versions(const std::vector<uint8_t>& data, int& offset) {
  int result = read_version(data, offset);
  if (read_typeid(data, offset) == TypeId::LITERAL) {
    read_literal(data, offset);
  } else {
    if (read_length_type(data, offset) == LengthType::BITS) {
      int length = read_length_in_bits(data, offset);
      int end_offset = offset + length;
      while (offset < end_offset) {
        result += sum_versions(data, offset);
      }
    } else {
      int length = read_length_in_packets(data, offset);
      for (int i = 0; i < length; i++) {
        result += sum_versions(data, offset);
      }
    }
  }
  return result;
}

void test() {
  assert(read_bits({0b10111111}, 0, 3) == 0b101);
  assert(read_bits({0b11101011}, 4, 2) == 0b10);
  assert(read_bits({0b11111101, 0b01111111}, 6, 4) == 0b0101);
  assert(read_bits({0xff, 0b11111010, 0b01111111}, 13, 4) == 0b0100);
}

int main(int argc, char* argv[]) {
  test();

  std::ifstream file{argv[1]};
  std::string line;
  file >> line;
  std::vector<uint8_t> data;
  for (int i = 0; i < line.size(); i+=2) {
    data.push_back(std::stoi(line.substr(i, 2), nullptr, 16));
  }

  int offset = 0;
  int sum = sum_versions(data, offset);
  std::cout << "Sum of all versions: " << sum << '\n';

  offset = 0;
  ResT result = eval_packet(data, offset);
  std::cout << "Result of operations: " << result << '\n';
}
