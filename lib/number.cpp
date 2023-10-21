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
    for (int i = 0; i < int2023_t::kSize - sizeof(int32_t); ++i) {
      result.bytes[i] = 255;
    }
  }

  return result;
}

int2023_t from_string(const char* buff) {
  int2023_t result;
  const bool is_neg = (buff[0] == '-') ? true : false;
  const char* unsigned_buff = buff;
  size_t buff_len = strlen(buff);
  if (is_neg) {
    unsigned_buff += 1;
    buff_len -= 1;
  }
  uint8_t* digit_arr = new uint8_t[buff_len];
  int i = 0;
  while (i < buff_len) {
    if ('0' <= unsigned_buff[i] && unsigned_buff[i] <= '9'){
      digit_arr[i] = static_cast<uint8_t>(unsigned_buff[i] - '0');
      ++i;
    } else {
      std::cerr << "Error while parsing string";
      delete[] digit_arr;
      return result;
    }
  }

  int quotient[253] = {255};
  uint8_t remainders[253] = {0};
  std::copy(digit_arr, digit_arr + buff_len, std::begin(quotient));

  size_t quot_len = buff_len; // Column division
  int k = 0;
  while (quotient[0] != 0) {
    uint64_t temp = 0;
    int j = 0;
    for (int i = 0; i < quot_len;) {
      int start_i = i;
      while (i < quot_len && temp < int2023_t::kBase) {
        temp = temp * 10 + quotient[i];
        ++i;
        if (i - start_i > 1 && start_i != 0) {
          quotient[j] = 0;
          ++j;
        }
      }
      quotient[j] = temp / int2023_t::kBase;
      temp %= int2023_t::kBase;
      ++j;
    }
    remainders[k] = temp;
    ++k;
    quot_len = j;
  }
  --k;

  int offset = int2023_t::kSize - k - 1;
  for (int i = k; i >= 0; --i) {
    result.bytes[offset + k - i] = remainders[i];
  }
  delete[] digit_arr;
  return is_neg ? -result : result;

}

int2023_t operator+(const int2023_t& lhs, const int2023_t& rhs) {
  int2023_t number;
  int extra = 0;
  int i = int2023_t::kSize-1;
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
  if (number.bytes[int2023_t::kSize-1] < 255) {
    ++number.bytes[int2023_t::kSize-1];
    return number;
  }
  bool has_extra = true;
  int i = int2023_t::kSize-1;
  while (i >= 0 && has_extra) {
    if (number.bytes[i] < 255) {
      has_extra = false;
    }
    ++number.bytes[i];
    --i;
  }

  return number;
}

int2023_t& operator+=(int2023_t& number, const int2023_t& number2) {
  number = number + number2;
  return number;
}

int2023_t operator-(const int2023_t& number) {
  int2023_t result;
  for (int i = 0; i < int2023_t::kSize; ++i) {
    result.bytes[i] = ~number.bytes[i];
  }

  return ++result;
}

int2023_t operator-(const int2023_t& lhs, const int2023_t& rhs) {
  int2023_t temp = rhs;
  return (lhs + (-temp));
}

int2023_t operator*(const int2023_t& lhs, const int2023_t& rhs) {
  const uint8_t mask = 0b10000000;
  int2023_t result;
  int temp_arr[int2023_t::kSize] = {0};

  bool is_neg = (lhs.bytes[0] & mask) ^ (rhs.bytes[0] & mask);
  int2023_t abs_lhs = abs(lhs);
  int2023_t abs_rhs = abs(rhs);

  for (int i = int2023_t::kSize - 1; i >= 0; --i) {
    for (int j = int2023_t::kSize - 1; j >= 0; --j) {
      int64_t temp = abs_lhs.bytes[i] * abs_rhs.bytes[j];
      temp_arr[(i + j) - int2023_t::kSize + 1] += temp;
    }
  }
  for (int i = int2023_t::kSize - 1; i >= 1; --i) {
    temp_arr[i - 1] += temp_arr[i] / int2023_t::kBase;
    result.bytes[i] = temp_arr[i] % int2023_t::kBase;
  }
  return is_neg ? -result : result;
}

void ShiftLeftOnce(int2023_t& number) {
  for (int64_t i = 1; i < int2023_t::kSize; ++i) {
    std::swap(number.bytes[i - 1], number.bytes[i]);
  }
  number.bytes[int2023_t::kSize - 1] = 0;
}

int2023_t operator/(const int2023_t& lhs, const int2023_t& rhs) {
  const uint8_t mask = 0b10000000;
  bool is_neg = (lhs.bytes[0] & mask) ^ (rhs.bytes[0] & mask);
  int2023_t abs_lhs = abs(lhs);
  int2023_t abs_rhs = abs(rhs);
  int2023_t avaliable_divisors[int2023_t::kBase]; // Includes numbers from rhs * 0 to rhs * 255
  avaliable_divisors[0] = int2023_t();
  for (int i = 1; i < int2023_t::kBase; ++i) {
    avaliable_divisors[i] = avaliable_divisors[i-1] + abs_rhs;
  }

  int2023_t result;
  int start_index = int2023_t::kSize - 1;
  for (size_t i = 0; i < int2023_t::kSize; ++i) {
    if (abs_lhs.bytes[i] != 0) {
      start_index = i;
      break;  
    }
  }
  int2023_t temp;
  for (int i = start_index; i < int2023_t::kSize; ++i) { // Single digit (one division operation)
    ShiftLeftOnce(temp);
    temp.bytes[int2023_t::kSize - 1] = abs_lhs.bytes[i];

    int quotient_digit_index = 255;
    while (temp < avaliable_divisors[quotient_digit_index]) {
      --quotient_digit_index;
    }

    ShiftLeftOnce(result);
    result.bytes[int2023_t::kSize - 1] = quotient_digit_index;
    temp = temp - avaliable_divisors[quotient_digit_index];
  }

  return is_neg ? -result : result;
} 

bool operator==(const int2023_t& lhs, const int2023_t& rhs) {
  for (int i = 0; i < int2023_t::kSize; ++i) {
    if (lhs.bytes[i] != rhs.bytes[i]) {
      return false;
    }
  }
  return true;
}

bool operator!=(const int2023_t& lhs, const int2023_t& rhs) {
  return !(lhs == rhs);
}

bool operator<(const int2023_t& lhs, const int2023_t& rhs) {
  const uint8_t mask = 0b10000000;
  if ((lhs.bytes[0] & mask) ^ (rhs.bytes[0] & mask)) { // Different signs
    return (lhs.bytes[0] & mask) > (rhs.bytes[0] & mask);
  }

  for (int i = 0; (i < int2023_t::kSize); ++i) {
    if (lhs.bytes[i] > rhs.bytes[i]) {
      return false;
    } else if (lhs.bytes[i] < rhs.bytes[i]) {
      return true;
    }
  }
  
  return false;
}

std::ostream& operator<<(std::ostream& stream, const int2023_t& value) {
  bool has_started = false;
  bool is_neg = (value.bytes[0] >> 6) & 1;
  int2023_t absolute = value;
  if (is_neg) {
    stream << '-';
    absolute = -absolute;
  }
  for (int i = 0; i < int2023_t::kSize; ++i) {
    if (absolute.bytes[i] != 0) {
      has_started = true;
    }
    
    if ((i + 1 < int2023_t::kSize) && has_started) {
      stream << static_cast<int>(absolute.bytes[i]) << ' ';
    } else if (has_started || i == int2023_t::kSize - 1) {
      stream << static_cast<int>(absolute.bytes[i]);
    }
  }

  return stream;
}

int2023_t abs(const int2023_t& value) {
  return ((value.bytes[0] >> 7) & 1 ? -value : value);
}