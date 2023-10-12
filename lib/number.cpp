#include "number.h"


int2023_t from_int(int32_t value) {
  int2023_t result;
  const uint8_t mask = 0b11111111;
  bool is_neg = (value >> 31) & 1;

  for (int i = 0; i < sizeof(int32_t); ++i) {
    result.bytes[252-i] = value & mask;
    value = value >> 8;
  }

  if (is_neg) {
    for (int i = 0; i < result.kSize - sizeof(int32_t); ++i) {
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

int2023_t operator++(int2023_t& number) {
  
  if (number.bytes[number.kSize-1] < 255) {
    ++number.bytes[number.kSize-1];
    return number;
  }
  bool has_extra = true;
  int i = number.kSize-1;
  while (i >= 0 && has_extra) {
    if (number.bytes[i] < 255) {
      has_extra = false;
    }
    ++number.bytes[i];
    --i;
  }

  return number;
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
  for (int i = 0; i < value.kSize; ++i) {
    if (i + 1 < value.kSize) {
      stream << static_cast<short>(value.bytes[i]) << ' ';
    } else {
      stream << static_cast<short>(value.bytes[i]);
    }
  }

  return stream;
}
