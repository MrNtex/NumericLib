#include <iostream>
#include "tests/test.h"
#include "examples/numeric_examples.hpp"

int main()
{
    std::cout << "Hello World!\n";

    std::cout << "Running tests...\n";
    
    RunTests();

    std::cout << "Tests completed.\n";

    std::cout << "Running examples...\n";

    RunExamples();

}