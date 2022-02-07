#include "lexer.h"
#include "parser.h"
#include "codeGenerator.h"
#include "parameterParser.h"

#include <iostream>

int main(int argc, char** argv) {
    try {
        parameterParser paramParser(argv, argc);

        lexer lexicalAnalizer("./lexerDefinitions.lex");
        parser tokenParser("./parserDefinitions.psr");
        codeGenerator asmGenerator("./boilerPlate.asm");

        const std::vector<Token> tokenList = lexicalAnalizer.lexFile(paramParser.getInputFileName());
        const std::string asmCode = tokenParser.parseTokenList(tokenList);
        asmGenerator.generateASMFile(paramParser.getOutputFileName(), asmCode);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
