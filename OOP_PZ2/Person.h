#pragma once
#include <string>

class Person
{
public:
    void setFullName(const std::string& fullName) { FullName = fullName; }
    void setSex(const std::string& sex) { Sex = sex; }

    std::string getFullName() const { return FullName; }
    std::string getSex() const { return Sex; }

private:
    std::string FullName;
    std::string Sex;
};