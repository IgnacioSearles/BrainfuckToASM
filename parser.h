#pragma once
#include "tokens.h"
#include <utility>
#include <string>
#include <vector>

class parser {
    public:
        parser(const std::string& parserDefinitionsFileName);

        std::string parseTokenList(const std::vector<Token>& tokenList);
    private:
        void loadParserDefinitionsFile(const std::string& fileName);
        std::string getParserDefinitionASM(const std::string& definition);

        std::vector<parserRule> getParserRules(const std::string& definition);
        std::string getRulesDefinition(const std::string& definition);
        bool hasIndicatorAndRemoveItIfTrue(std::string& string, const char& c);
        parserRule getParserRule(std::string rule);

        bool matchesParserRule(const std::vector<Token>& tokenList, uint32_t tokenIndex, const std::vector<parserRule>& rules);
        void replaceParserVariables(Token t1, std::string& codeToAdd);

        int currentBlockID;
        std::vector<parserDefinition> parserDefinitions;
};
