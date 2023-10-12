#include "number.h"


int2023_t from_int(int32_t value) {
  int2023_t result;
  const size_t kSize = 253;
  const uint8_t mask = 0b11111111;
  bool is_neg = (value >> 31) & 1;

  for (int i = 0; i < sizeof(int32_t); ++i) {
    result.bytes[252-i] = value & mask;
    value = value >> 8;
  }

  if (is_neg) {
    for (int i = 0; i < kSize - sizeof(int32_t); ++i) {
      result.bytes[i] = 255;
    }
  }

  return result;
}

int2023_t from_string(const char* buff) {
    return int2023_t();
}

int2023_t operator+(const int2023_t& lhs, const int2023_t& rhs) {
    return int2023_t();
}

int2023_t operator-(const int2023_t& lhs, const int2023_t& rhs) {
    return int2023_t();
}

int2023_t operator*(const int2023_t& lhs, const int2023_t& rhs) {
    return int2023_t();
}

int2023_t operator/(const int2023_t& lhs, const int2023_t& rhs) {
    return int2023_t();
}

bool operator==(const int2023_t& lhs, const int2023_t& rhs) {
    return false;
}

bool operator!=(const int2023_t& lhs, const int2023_t& rhs) {
    return false;
}

std::ostream& operator<<(std::ostream& stream, const int2023_t& value) {
    stream << "Implement me";

    return stream;
}
