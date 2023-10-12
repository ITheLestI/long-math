#include <lib/number.h>
#include <iostream>
#include <cstring>

// void ColumnDivision(uint8_t* src_arr, size_t src_len, uint8_t* result, int divisor = 256) {
//   int offset = 252;
//   size_t digit = 0;
//   int power = 1;
//   uint64_t temp = 0;
//   while (digit < src_len) {
//     temp += src_arr[digit];
//     std::cout << "+" << static_cast<short>(src_arr[digit]) << '=';
//     std::cout << temp << ' ';
//     if (offset < 0) {
//       break;
//     }

//     if (temp >= divisor) {
      
//       // std::cout << static_cast<int>(result[offset]) << ' ';
//       temp %= divisor;
//       if (digit+1 <= src_len) {
//         temp *= 10;
//         printf("'");
//       }
//       // --offset;
//     } else if (digit+1 < src_len) {
//       temp *= 10;
//       printf("'");
//     }
//     ++digit;
//   }
//   result[offset] = temp;
  
// }

int main() {
  const size_t kSize = 253;
  // uint8_t number[kSize] = {0}; //253 bytes = 253*8 = 2024 bits, 1 bit for sign + 2022 bits for number
  int32_t value = 65535;
  const uint8_t mask = 0b11111111;

  // bool is_neg = (value >> 31) & 1;
  for (int i = 31; i >= 0; --i) {
    std::cout << ((value >> i) & 1);
  }
  std::cout << '\n';
  int2023_t number = from_int(value);

  std::cout << number << '\n';
  int2023_t n = ++number;
  const char* buff = "325343";
  const size_t len = strlen(buff);
  const bool is_neg = (buff[0] == '-') ? true : false;

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
  
  // std::cout << '\n';
  // int2023_t a = from_int(value);


  // for (int j = 0; j < 253; ++j) {
  //   std::cout << static_cast<int>(num.bytes[j]) << ' ';
  // }
  // ColumnDivision(temp, len, number);
  // std::cout << '\n';
  // for (int i = 0; i < number.kSize; ++i) {
  //   std::cout << static_cast<short>(number.bytes[i]) << ' ';
  // }
  std::cout << number << '\n';
  return 0;
}
