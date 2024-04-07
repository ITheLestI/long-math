#include <lib/number.h>
#include <iostream>
#include <cstring>

int main() {
  int32_t value = 5;
  int32_t value2 = 13572;

  int2023_t number = from_string("-72871897469819293737367872833326987466367646586482254424286949504560031874005");
  int2023_t number2 = from_string("65670123909401983585308549786595851694410179714945696570320001142378944542562");
  
  int2023_t number3 = from_int(3816);
  int2023_t number4 = from_string("2310");
  // std::cout << number << '\n';
  // std::cout << number2 << '\n';
  // int2023_t sub = number-number2;
  // std::cout << sub << '\n';
  // std::cout << -sub << '\n';  
  // int2023_t r = number * number2;
  // number += number2;
  // std::cout << "source1 " << number << "\nsource2 " << number2 << '\n';
  int2023_t n = number / number2;
  std::cout << '\n' << n << '\n';
  // std::cout << number << '\n' << number3 << '\n';
  // std::cout << (-number < number3) << '\n';
  // std::cout << (number2 < number3) << '\n';
  
  // std::cout << number3 << '\n';
  // std::cout << (number * number2) << '\n';
  // std::cout << ((-number) == number4) << '\n';
  return 0;
}
