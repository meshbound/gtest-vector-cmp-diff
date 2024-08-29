# GoogleTest Vector Comparison Diff

Compares contents of `std::vector` objects, outputs a basic diff if the comparison fails

![Screenshot from 2024-08-29 16-40-26](https://github.com/user-attachments/assets/54937fd5-f01e-4360-abc9-fef18fd91a67)

## Example

### person.h
```c++
#pragma once

class Person {
 public:
  const std::string name;
  const int age;

  Person(std::string name, int value) : name(name), age(age) {}
  std::string to_string() const;
  bool operator==(const Person& p) const;
};

std::string to_string(const Person& p);
```

### person.cc
```c++
std::string Person::to_string() const {
  return "name: " + name + ", age: " + std::to_string( age );
}

bool Person::operator==(const Person& p) const {
  return name == p.name && age == p.age;
}

std::string to_string(const Person& p) {
  return p.to_string();
}
```

### my-class-test.h
```c++
#pragma once

#include <gtest/gtest.h>

class MyTest : public testing::Test { }
```

### my-class-test.cc
```c++
#include "my-test.h"
#include "my-class.h"

#include <string>
#include <vector>

TEST_F(MyTest, TestBasic) {
  MyClass instance;

  people = instance.get_people();

  std::vector<Person> expected = {
    Person("Gregory House", 45),
    Person("Lisa Cuddy", 57),
    Person("Robert Chase", 26),
    Person("James Wilson", 46)
  }

  EXPECT_PRED_FORMAT2(TestCustom::compare_vectors<Person>, expected, people);
}
```
