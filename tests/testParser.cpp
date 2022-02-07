#include "../parser.h"
#include "testing.h"
#include <iostream>
#include <vector>

std::vector<Token> test1 = {ADD, ADD, ADD, PTR_LEFT, SUBTRACT, PRINT};
std::string test1Out = "inc rbx\ninc rbx\ninc rbx\nmov [rel rax], bl\ndec rax\nmov bl, byte [rel rax]\ndec rbx\nmov rdx, 0\nmov dl, bl\nmov rcx, print_byte\ncall printf\n";


std::vector<Token> test2 = {ADD, START_LOOP, ADD, PTR_RIGHT, END_LOOP, PRINT};
std::string test2Out = "inc rbx\nmov [rel rax], bl\nltag0:\ncmp rbx, 0\nje ltag0end\ninc rbx\nmov [rel rax], bl\ninc rax\nmov bl, byte [rel rax]\njmp ltag0\nltag0end:\nmov rdx, 0\nmov dl, bl\nmov rcx, print_byte\ncall printf\n";

std::vector<Token> test3 = {ADD, PTR_RIGHT, PTR_RIGHT, PTR_LEFT, SUBTRACT};
std::string test3Out = "inc rbx\nmov [rel rax], bl\ninc rax\ninc rax\ndec rax\nmov bl, byte [rel rax]\ndec rbx\n";

int main() {
    try {
        parser Parser("../parserDefinitions.psr");

        testing::assert((Parser.parseTokenList(test1) == test1Out), "Test 1");
        testing::assert((Parser.parseTokenList(test2) == test2Out), "Test 2");
        testing::assert((Parser.parseTokenList(test3) == test3Out), "Test 3");
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
