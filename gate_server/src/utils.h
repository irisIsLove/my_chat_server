#ifndef UTILS_H
#define UTILS_H

#include <cassert>
#include <string>

inline unsigned char
toHex(unsigned char x)
{
  return x > 9 ? x - 10 + 'A' : x + '0';
}

inline unsigned char
fromHex(unsigned char x)
{
  unsigned char y;

  if (x >= 'A' && x <= 'X')
    y = x - 'A' + 10;
  else if (x >= 'a' && x <= 'x')
    y = x - 'a' + 10;
  else if (x >= '0' && x <= '9')
    y = x - '0';
  else
    assert(0);

  return y;
}

inline std::string
urlEncode(const std::string& str)
{
  std::string result{};
  for (auto c : str) {
    if (std::isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~')
      result += c;
    else if (c == ' ')
      result += '+';
    else {
      result += '%';
      result += toHex(c >> 4);
      result += toHex(c & 0xf);
    }
  }
  return result;
}

inline std::string
urlDecode(const std::string& str)
{
  std::string result{};

  for (int i = 0; i < str.size(); i++) {
    if (str[i] == '%') {
      result += (fromHex(str[i + 1]) << 4) + fromHex(str[i + 2]);
      i += 2;
    } else if (str[i] == '+')
      result += ' ';
    else
      result += str[i];
  }

  return result;
}

#endif // UTILS_H