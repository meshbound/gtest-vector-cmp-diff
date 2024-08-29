#pragma once

#include <gtest/gtest.h>
#include <algorithm>
#include <string>

const size_t MAX_CMP_LN_CHARS = 32;
const std::string TAB_REPLACE_SEQ = "    ";

using std::to_string;

namespace TestCustom {
  std::string pad(std::string str, size_t len);
  void pad_align(std::vector<std::string>& a, std::vector<std::string>& b, size_t len);
  std::string replace(std::string str, const std::string& from, const std::string& to);
  std::vector<std::string> split(std::string str, const std::string& on = "\n");
  int divvy(std::string str, size_t threshold, std::vector<std::string>& out, bool pad_last = true);
  std::vector<std::string> split_then_divvy(const std::string& str, size_t threshold,
      const std::string& on = "\n", bool pad_last = true);

  template <typename T>
  testing::AssertionResult compare_vectors(const char* expr1, const char* expr2,
      std::vector<T> expected, std::vector<T> actual);
};

template <typename T>
testing::AssertionResult TestCustom::compare_vectors(const char* expr1, const char* expr2,
    std::vector<T> expected, std::vector<T> actual) {
  if (actual == expected) {
    return testing::AssertionSuccess();
  } else {
    std::string str = "";

    int i = std::max(expected.size(), actual.size());
    while (!expected.empty() && !actual.empty()) {

      std::vector<std::string> expected_div = split_then_divvy(
          replace(to_string(expected.back()), "\t", TAB_REPLACE_SEQ),
          MAX_CMP_LN_CHARS
      );

      std::vector<std::string> actual_div = split_then_divvy(
          replace(to_string(actual.back()), "\t", TAB_REPLACE_SEQ),
          MAX_CMP_LN_CHARS
      );

      pad_align(expected_div, actual_div, MAX_CMP_LN_CHARS);
      while (!expected_div.empty() && !actual_div.empty()) {
        str = "\t" + expected_div.back() + "\t\t" + actual_div.back() + "\n" + str;
        expected_div.pop_back();
        actual_div.pop_back();
      }

      str = std::to_string(i) + str;
      str = actual.back() != expected.back() ? "#" + str : " " + str;

      expected.pop_back();
      actual.pop_back();
      i--;
    }
 
    while (!expected.empty()) {
      std::vector<std::string> expected_div = split_then_divvy(
          replace(to_string(expected.back()), "\t", TAB_REPLACE_SEQ),
          MAX_CMP_LN_CHARS
      );

      while (!expected_div.empty()) {
        str = "\t" + expected_div.back() + "\n" + str;
        expected_div.pop_back();
      }
      
      str = "#" + std::to_string(i) + str;

      expected.pop_back();
      i--;
    }

    while (!actual.empty()) {
      std::vector<std::string> actual_div = split_then_divvy(
          replace(to_string(actual.back()), "\t", TAB_REPLACE_SEQ),
          MAX_CMP_LN_CHARS
      );

      while (!actual_div.empty()) {
        str = "\t" + pad("", MAX_CMP_LN_CHARS) + "\t\t" + actual_div.back() + "\n" + str;
        actual_div.pop_back();
      }
      
      str = "#" + std::to_string(i) + str;

      actual.pop_back();
      i--;
    }
    return testing::AssertionFailure() << "\t" << pad("expected", MAX_CMP_LN_CHARS)
      << "\t\tactual\n" << str;
  }
}
