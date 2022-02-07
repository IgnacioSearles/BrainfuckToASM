#include "parser.h"
#include <regex>
#include <fstream>
#include <sstream>
#include <iostream>

parser::parser(const std::string& parserDefinitionsFileName) {
    loadParserDefinitionsFile(parserDefinitionsFileName);
}

void parser::loadParserDefinitionsFile(const std::string& fileName) {
    std::ifstream parserDefinitionsFile(fileName);

    if (parserDefinitionsFile.fail()) throw std::runtime_error("Error loading parser definitions file");

    std::string definition;
    while (std::getline(parserDefinitionsFile, definition)) {
        std::string nasm = std::regex_replace(getParserDefinitionASM(definition), std::regex(R"(\\n)"), "\n");
        std::vector<parserRule> parserRules = getParserRules(definition);

        parserDefinitions.push_back(parserDefinition(parserRules, nasm));
    }

    parserDefinitionsFile.close();
}

std::string parser::getParserDefinitionASM(const std::string& definition) {
    std::smatch match;
    std::regex_search(definition, match, std::regex(R"(\|\| (.+))"));

    if (match.empty()) throw std::runtime_error("Error parsing parser definitions file on line: " + definition);

    return match.str(1);
}

std::vector<parserRule> parser::getParserRules(const std::string& definition) {
    std::stringstream rulesDefinition(getRulesDefinition(definition));

    std::vector<parserRule> parserRules;
    std::string rule;

    while (std::getline(rulesDefinition, rule, ',')) {
        parserRule newRule = getParserRule(rule);
        parserRules.push_back(newRule);
    }

    return parserRules;
}

std::string parser::getRulesDefinition(const std::string& definition) {
    std::smatch rulesDefinitionMatch;
    std::regex_search(definition, rulesDefinitionMatch, std::regex(R"((.+) \|\|)"));

    if (rulesDefinitionMatch.empty()) throw std::runtime_error("Error parsing parser definitions file on line: " + definition);

    return rulesDefinitionMatch.str(1);
}

bool parser::hasIndicatorAndRemoveItIfTrue(std::string& string, const char& c) {
    bool out = false;
    if (string.at(0) == c) {
        out = true;
        string.erase(0, 1);
    }
    return out;
}

parserRule parser::getParserRule(std::string rule) {
    bool andTokens = hasIndicatorAndRemoveItIfTrue(rule, '&'); 

    std::stringstream ruleDefinition(rule);
    std::vector<parserToken> newParserRule;
    std::string ruleToken;

    while (std::getline(ruleDefinition, ruleToken, '|')) {
        bool tokenPositive = !hasIndicatorAndRemoveItIfTrue(ruleToken, '!');
        newParserRule.push_back(parserToken(textToToken.at(ruleToken), tokenPositive));
    }

    return parserRule(newParserRule, andTokens);
}

std::string parser::parseTokenList(const std::vector<Token> &tokenList) {
    std::string outputCode;
    currentBlockID = 0;

    for (uint32_t tokenIndex = 0; tokenIndex < tokenList.size(); tokenIndex++) {
        std::string codeToAdd;

        for (const auto& parserDefinition : parserDefinitions) {
            if (matchesParserRule(tokenList, tokenIndex, parserDefinition.rules)) codeToAdd += parserDefinition.nasm;
        }

        replaceParserVariables(tokenList.at(tokenIndex), codeToAdd);
        outputCode += codeToAdd;
    }
    return outputCode;
}

bool parser::matchesParserRule(const std::vector<Token>& tokenList, uint32_t tokenIndex, const std::vector<parserRule>& rules) {
    bool matches = true;
    int offset = 0;

    if (rules.size() > tokenList.size() - tokenIndex) return false;

    for (const auto& rule : rules) {
        bool ruleMatch = rule.andTokens;

        for (const auto& token : rule.rule) {
            if (rule.andTokens) ruleMatch &= (tokenList.at(tokenIndex + offset) == token.t) == token.b;
            else ruleMatch |= (tokenList.at(tokenIndex + offset) == token.t) == token.b;
        }

        matches &= ruleMatch;
        offset++;
    }
    return matches;
}

void parser::replaceParserVariables(Token t1, std::string& codeToAdd) {
    if (t1 == START_LOOP) {
        codeToAdd = std::regex_replace(codeToAdd, std::regex("ID"), std::to_string(currentBlockID));
        currentBlockID++;
    }
    else if (t1 == END_LOOP) {
        currentBlockID--;
        codeToAdd = std::regex_replace(codeToAdd, std::regex("ID"), std::to_string(currentBlockID));
        currentBlockID++;
    }
}
