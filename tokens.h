#pragma once
#include <string>
#include <vector>
#include <unordered_map> 

enum Token {ADD, SUBTRACT, PTR_LEFT, PTR_RIGHT, START_LOOP, END_LOOP, PRINT, SCAN};
const std::unordered_map<std::string, Token> textToToken = {
    {"ADD", ADD},
    {"SUBTRACT", SUBTRACT},
    {"PTR_LEFT", PTR_LEFT},
    {"PTR_RIGHT", PTR_RIGHT},
    {"START_LOOP", START_LOOP},
    {"END_LOOP", END_LOOP},
    {"PRINT", PRINT},
    {"SCAN", SCAN}
};

struct parserToken {
    parserToken(Token tp, bool bp) {
        t = tp;
        b = bp;
    }

    Token t;
    bool b;
};

struct parserRule {
    parserRule(const std::vector<parserToken>& rulep, bool andTokensp) {
        rule = rulep;
        andTokens = andTokensp;
    }

    std::vector<parserToken> rule;
    bool andTokens;
};

struct parserDefinition {
    parserDefinition (const std::vector<parserRule>& rulesp, const std::string& nasmp) {
        rules = rulesp;
        nasm = nasmp;
    }

    std::vector<parserRule> rules;
    std::string nasm;
};
