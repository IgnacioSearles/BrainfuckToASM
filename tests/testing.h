#pragma once
#include <string>
#include <iostream>

namespace testing {
    void assert(bool test, const std::string& testName) {
        if (test) std::cout << "\033[1;32m -" << testName << " passed.\033[0m" << std::endl;
        else std::cout << "\033[1;31m -" << testName << " failed.\033[0m" << std::endl;
    }
}
