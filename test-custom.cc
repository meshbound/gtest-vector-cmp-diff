#include "test-custom.h"

std::string TestCustom::pad(std::string str, size_t len) {
  while(str.size() < len) {
    str += " ";
  }
  return str;
}

void TestCustom::pad_align(std::vector<std::string>& a, std::vector<std::string>& b, size_t len) {
  size_t count = std::max(a.size(), b.size());
  std::string fill = pad("", len);
  while (a.size() < count) {
    a.push_back(fill);
  }
  while (b.size() < count) {
    b.push_back(fill);
  }
}

std::string TestCustom::replace(std::string str, const std::string& from, const std::string& to) {
  while (true) {
    size_t i = str.find(from);
    if (i == std::string::npos) break;
    str.replace(i, from.size(), to);
  }
  return str;
}

std::vector<std::string> TestCustom::split(std::string str, const std::string& on ) {
  std::vector<std::string> result;
  while (true) {
    size_t i = str.find(on);
    if (i == std::string::npos) {
      break;
    }
    std::string next = str.substr(0, i);
    result.push_back(next);
    str = str.substr(i + on.size()); 
  }
  if (!str.empty()) {
    result.push_back(str);
  }
  return result;
}

int TestCustom::divvy(std::string str, size_t threshold, std::vector<std::string>& out, bool pad_last ) {
  int start_size = out.size();
  while (str.size() > threshold) {
    std::string next = str.substr(0, threshold);
    out.push_back(next);
    str = str.substr(threshold);
  }
  if (!str.empty()) {
    if (pad_last) {
      str = TestCustom::pad(str, threshold); 
    }
    out.push_back(str);
  }
  return out.size() - start_size;
}

std::vector<std::string> TestCustom::split_then_divvy(const std::string& str, size_t threshold,
    const std::string& on, bool pad_last) {
  std::vector<std::string> result;
  std::vector<std::string> split = TestCustom::split(str, on);
  for (std::string& str : split) {
    TestCustom::divvy(str, threshold, result, pad_last); 
  }
  return result;
}

