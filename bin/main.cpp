#include <lib/number.h>
#include <iostream>
#include <cstring>


int main() {
  const size_t kSize = 253;
  uint8_t number[kSize] = {0}; //253 bytes = 253*8 = 2024 bits, 1 bit for sign + 2022 bits for number
  int32_t value = 325343;
  int2023_t num = from_int(value);
  const char* buff = "-346";
  const size_t len = strlen(buff);
  const bool is_neg = (buff[0] == '-') ? true : false;
  std::cout << len << "\n";

  uint8_t temp[len];
  for (int i = 0; i < len; ++i) {
    if (i == 0 && is_neg) {
      continue;
    }
    if ('0' <= buff[i] && buff[i] <= '9'){
      temp[i] = static_cast<uint8_t>(buff[i]-'0');
    } else {
      std::cerr << "Error while parsing string";
      break;
    }
    // std::cout << temp[i] << ' ';
  }
  
  std::cout << '\n';
  // int2023_t a = from_int(value);
  for (int i = 31; i >= 0; --i) {
    std::cout << ((value >> i) & 1);
  }
  std::cout << '\n';


  for (int j = 0; j < 253; ++j) {
    std::cout << static_cast<int>(num.bytes[j]) << ' ';
  }

  // std::cout << '\n';
  // for (int i = 0; i < kSize; ++i) {
  //   std::cout << static_cast<short>(number[i]) << ' ';
  // }
  return 0;
}
