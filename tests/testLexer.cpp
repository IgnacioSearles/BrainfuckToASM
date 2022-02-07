#include "../lexer.h"
#include "testing.h"
#include <iostream>

std::vector<Token> test1ExpectedOutput = {ADD, ADD, PTR_RIGHT, SUBTRACT, SUBTRACT};
std::vector<Token> test2ExpectedOutput = {ADD, ADD, ADD, PTR_RIGHT, START_LOOP, ADD, PTR_LEFT, SUBTRACT, PTR_RIGHT, END_LOOP, PRINT};
std::vector<Token> test3ExpectedOutput = {SCAN, ADD, ADD, ADD, ADD, SUBTRACT, ADD, START_LOOP, SUBTRACT, END_LOOP};

int main() {
    try {
        lexer lexicalAnalizer("../lexerDefinitions.lex");
        testing::assert((lexicalAnalizer.lexFile("lexInputFileTest1.fuck") == test1ExpectedOutput), "Test 1");
        testing::assert((lexicalAnalizer.lexFile("lexInputFileTest2.fuck") == test2ExpectedOutput), "Test 2");
        testing::assert((lexicalAnalizer.lexFile("lexInputFileTest3.fuck") == test3ExpectedOutput), "Test 3");
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
