#include "number.h"
#include <cstring>

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
  const int kBase = 256;
  const bool is_neg = (buff[0] == '-') ? true : false;
  const char* unsigned_buff = buff;
  size_t buff_len = strlen(buff);
  if (is_neg) {
    unsigned_buff += 1;
    buff_len -= 1;
  }
  uint8_t digit_arr[buff_len];
  int i = 0;
  while (i < buff_len) {
    if ('0' <= unsigned_buff[i] && unsigned_buff[i] <= '9'){
      digit_arr[i] = static_cast<uint8_t>(unsigned_buff[i]-'0');
      ++i;
    } else {
      std::cerr << "Error while parsing string";
      break;
    }
  }

  int quotient[253] = {255};
  uint8_t remainders[253] = {0};
  for (int i = 0; i < buff_len; ++i) {
    quotient[i] = digit_arr[i];
  }

  size_t quot_len = buff_len; // Column division
  int k = 0;
  while (quotient[0] != 0) {
    uint64_t temp = 0;
    int j = 0;
    for (int i = 0; i < quot_len;) {
      int start_i = i;
      while (i < quot_len && temp < kBase) {
        temp = temp * 10 + quotient[i];
        ++i;
        if (i - start_i > 1 && start_i != 0) {
          quotient[j] = 0;
          ++j;
        }
      }
      quotient[j] = temp / kBase;
      temp %= kBase;
      ++j;
    }
    remainders[k] = temp;
    ++k;
    quot_len = j;
  }
  --k;

  int2023_t result;
  int offset = result.kSize - k - 1;
  for (int i = k; i >= 0; --i) {
    result.bytes[offset + k - i] = remainders[i];
  }
  if (is_neg) {
    return -result;
  }
  return result;
}

int2023_t operator+(const int2023_t& lhs, const int2023_t& rhs) {
  int2023_t number;
  int extra = 0;
  int i = number.kSize-1;
  while (i >= 0) {
    number.bytes[i] = lhs.bytes[i] + rhs.bytes[i] + extra;
    if (lhs.bytes[i] + rhs.bytes[i] + extra >= 256) {
      extra = 1;
    } else {
      extra = 0;
    }
    --i;
  }

  return number;
}

int2023_t& operator++(int2023_t& number) {
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

int2023_t operator-(int2023_t number) {
  for (int i = 0; i < 253; ++i) {
    number.bytes[i] = ~number.bytes[i];
  }
  return ++number;
}

int2023_t operator-(const int2023_t& lhs, const int2023_t& rhs) {
  int2023_t temp = rhs;
  return (lhs + (-temp));
}

int2023_t operator*(int2023_t lhs, int2023_t rhs) {
  const int kBase = 256;
  const uint8_t mask = 0b10000000;
  int2023_t result;

  bool is_neg = (lhs.bytes[0] & mask) ^ (rhs.bytes[0] & mask);
  if (lhs.bytes[0] & mask) {
    lhs = -lhs;
  }
  if (rhs.bytes[0] & mask) {
    rhs = -rhs;
  }
  uint8_t extra;
  for (int i = result.kSize - 1; i >= 0; --i) {
    extra = 0;
    for (int j = result.kSize - 1; j >= 0; --j) {
      int64_t temp = lhs.bytes[i] * rhs.bytes[j];
      result.bytes[i + j - result.kSize + 1] += temp % 256;
      extra = temp / 256;
    }
  }
  if (is_neg) {
    return -result;
  }
  return result;
}

int2023_t operator/(const int2023_t& lhs, const int2023_t& rhs) {
    return int2023_t();
}

bool operator==(const int2023_t& lhs, const int2023_t& rhs) {
  for (int i = 0; i < lhs.kSize; ++i) {
    if (lhs.bytes[i] != rhs.bytes[i]) {
      return false;
    }
  }
  return true;
}

bool operator!=(const int2023_t& lhs, const int2023_t& rhs) {
    return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& stream, const int2023_t& value) {
  bool has_started = false;
  bool is_neg = (value.bytes[0] >> 6) & 1;
  if (is_neg) {
      stream << '-';
  }
  for (int i = 0; i < value.kSize; ++i) {
    if ((value.bytes[i] != 0 && !is_neg) || (value.bytes[i] != 255 && is_neg)) {
      has_started = true;
    }
    
    if ((i + 1 < value.kSize) && has_started) {
      stream << static_cast<int>(value.bytes[i]) << ' ';
    } else if (has_started) {
      stream << static_cast<int>(value.bytes[i]);
    }
  }

  return stream;
}
