#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <regex>

#include "tokens.h"

class lexer {
    public:
        lexer(const std::string& lexerDefinitionsFileName);

        std::vector<Token> lexFile(const std::string& fileName);
    private:
        void loadLexerDefinitionsFile(const std::string& fileName);
        std::string applyRegexToLexerDefinitionsFileLine(const std::string& line, const std::regex& reg);

        std::vector<Token> applyLexerDefinitionsToLine(std::string line);

        std::unordered_map<std::string, Token> lexerDefinitions;
};
