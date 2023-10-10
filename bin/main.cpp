// #include <lib/number.h>
#include <iostream>
#include <limits>


int main() {
  const int kSize = 253;
  uint8_t number[kSize] = {0}; //253 bytes = 253*8 = 2024 bits, 1 bit for sign + 2022 bits for number
  int32_t value = -2;
  uint8_t mask = 0b11111111;
  bool is_neg = (value >> 31) & 1;
  // std::cout << is_neg << std::endl;
  
  for (int i = 31; i >= 0; --i) {
    std::cout << ((value >> i) & 1);
  }
  std::cout << std::endl;
  if (!is_neg) {
    for (int i = 0; i < sizeof(int32_t); ++i) {
      std::cout << (value & mask) << ' ';
      number[252-i] = value & mask;
      value = value >> 8;
    }

  } else {
    for (int i = 0; i < sizeof(int32_t); ++i) {
      std::cout << (value & mask) << ' ';
      number[252-i] = value & mask;
      value = value >> 8;
    }
    for (int i = 0; i < kSize - sizeof(int32_t); ++i) {
      number[i] = 255;
    }
  }
  std::cout << '\n';
  for (int i = 0; i < kSize; ++i) {
    // if (i < 252-4) number[i] = 0;
    std::cout << static_cast<short>(number[i]) << ' ';
  }
  // delete[] number;
  return 0;
}
