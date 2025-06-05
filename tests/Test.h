#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <cmath>

struct UnitTest {
    std::string name;
    bool result;

    UnitTest(std::string name, bool result)
        : name(std::move(name)), result(result) {}
};

class UnitGroup {
    std::vector<UnitTest> tests;
    std::string name;
    int passedCount = 0;

public:
    explicit UnitGroup(std::string name)
        : name(std::move(name)) {}

    void AddTest(std::string name, bool result) {
        tests.emplace_back(name, result);
        if (result) {
			passedCount++;
		}
    }

    void Print() const {
        std::cout << "\033[1mUnit Group: " << name << " | " << passedCount << '/' << tests.size() << "\033[0m\n";
        for (const auto& test : tests) {
            std::cout << "  [" << (test.result ? "\033[32mPASS" : "\033[31mFAIL") << "\033[0m] "
                << test.name << '\n';
        }
    }

    ~UnitGroup() {
        Print();
    }
};

template<typename Func>
bool shouldThrowException(const Func& func) {
    try {
        func();
    }
    catch (...) {
        return true;
    }
    return false;
}

void RunTests();
