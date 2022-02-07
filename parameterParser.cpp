#include "parameterParser.h"
#include <regex>
#include <stdexcept>
#include <iostream>

parameterParser::parameterParser(char** argv, int argc) {
    if (argc < 2) throw std::runtime_error("You must pass an input file to the compiler.");
    for (int i = 1; i < argc; i++) {
        passedArgs += " ";
        passedArgs += argv[i];
    }
}

std::string parameterParser::getInputFileName() {
    std::string passedInputFileName = getRequiredParameter("-i");

    if (passedInputFileName.find(".fuck") != std::string::npos) return passedInputFileName;

    return passedInputFileName + ".fuck";
}

std::string parameterParser::getOutputFileName() {
    std::string passedOutputFileName = getOptionalParameter("-o");

    if (passedOutputFileName != "") return passedOutputFileName;

    std::string inputFileName = getInputFileName();
    return inputFileName.substr(0, inputFileName.size() - 5) + ".asm";
}

std::string parameterParser::getRequiredParameter(const std::string& parameterId) {
    std::smatch match;

    std::regex_search(passedArgs, match, std::regex(parameterId + " ([^ ]+)"));

    if (match.empty()) throw std::runtime_error("Missing non optional parameter");

    return match.str(1);
}

std::string parameterParser::getOptionalParameter(const std::string& parameterId) {
    std::smatch match;

    std::regex_search(passedArgs, match, std::regex(parameterId + " ([^ ]+)"));

    if (!match.empty()) return match.str(1);

    return "";
}
