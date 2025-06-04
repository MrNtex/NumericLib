#pragma once
#include <iostream>
#include <vector>
#include <string>

struct UnitTest
{
    std::string name;
    bool result;

    UnitTest(std::string name, bool result) {
        this->name = name;
        this->result = result;
    }
};

struct UnitGroup
{
public:
    std::vector<UnitTest> tests;
    std::string name;

    void Print() const {
        std::cout << "\033[1mUnit Group: " << name << "\033[0m\n";
        for (const auto& test : tests) {
            if (test.result) {
                std::cout << "  [\033[32mPASS\033[0m] " << test.name << '\n';
            }
            else {
                std::cout << "  [\033[31mFAIL\033[0m] " << test.name << '\n';
            }
        }
    }

    UnitGroup(std::string name, std::vector<UnitTest> tests) {
        this->name = name;
        this->tests = tests;

        Print();
    }
};

void RunTests();