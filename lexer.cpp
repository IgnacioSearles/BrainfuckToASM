#include "lexer.h"
#include <fstream>
#include <regex>
#include <iostream>

lexer::lexer(const std::string& lexerDefinitionsFileName) {
    loadLexerDefinitionsFile(lexerDefinitionsFileName);
}

void lexer::loadLexerDefinitionsFile(const std::string& fileName) {
    std::ifstream lexerDefinitionsFile(fileName); 
    if (lexerDefinitionsFile.fail()) throw std::runtime_error("Error reading lexer definitions file");

    std::string lexerDefinition;
    while (std::getline(lexerDefinitionsFile, lexerDefinition)) {
        const std::string tokenRegex = applyRegexToLexerDefinitionsFileLine(lexerDefinition, std::regex(R"((.+) \|\|)"));
        const std::string tokenCorrespondingToRegexAsString = applyRegexToLexerDefinitionsFileLine(lexerDefinition, std::regex(R"(\|\| ([a-zA-Z_]+))"));

        lexerDefinitions[tokenRegex] = textToToken.at(tokenCorrespondingToRegexAsString); 
    }

    lexerDefinitionsFile.close();
}

std::string lexer::applyRegexToLexerDefinitionsFileLine(const std::string& line, const std::regex& reg) {
    std::smatch match;
    std::regex_search(line, match, reg);

    if (match.empty())
        throw std::runtime_error("Error parsing lexer definitions on line: " + line);

    return match.str(1);
}

std::vector<Token> lexer::lexFile(const std::string& fileName) {
    std::vector<Token> tokenList;

    std::ifstream inputFile(fileName);
    if (inputFile.fail()) throw std::runtime_error("Error reading compiler input file");

    std::string line;
    while (std::getline(inputFile, line)) {
        std::vector<Token> newTokens = applyLexerDefinitionsToLine(line);
        tokenList.insert(tokenList.end(), newTokens.begin(), newTokens.end());
    }

    inputFile.close();

    return tokenList;
}

std::vector<Token> lexer::applyLexerDefinitionsToLine(std::string line) {
    std::vector<Token> tokenList;

    while (line.size() > 0) {
        bool hadMatch = false;
        for (const auto& definition : lexerDefinitions) {
            std::smatch match;
            std::regex_search(line, match, std::regex(definition.first));

            if (!match.empty() && match.position() == 0) {
                tokenList.push_back(definition.second);
                line = match.suffix();
                hadMatch = true;
                break;
            }
        }

        if (!hadMatch) line.erase(0, 1);
    }

    return tokenList;
}
