#include "codeGenerator.h"

#include <fstream>
#include <sstream>

codeGenerator::codeGenerator(const std::string& boilerPlateCodeFileName) {
    loadBoilerPlateCode(boilerPlateCodeFileName);
}

void codeGenerator::loadBoilerPlateCode(const std::string& fileName) {
    std::ifstream boilerPlateCodeFile(fileName);

    if (boilerPlateCodeFile.fail()) throw std::runtime_error("Error loading boiler plate code file");
    
    std::stringstream buffer;
    buffer << boilerPlateCodeFile.rdbuf();

    boilerPlateCode = buffer.str();

    boilerPlateCodeFile.close();
}

void codeGenerator::generateASMFile(const std::string& fileName, const std::string& asmCode) {
    const std::string::size_type codeStartPos = boilerPlateCode.find(";code");
    if (codeStartPos == std::string::npos) throw std::runtime_error("Error finding ;code tag in boiler plate code file");

    std::string outputCode;
    outputCode = boilerPlateCode;
    outputCode.insert(codeStartPos + 6, asmCode);

    std::ofstream outputFile(fileName);
    outputFile << outputCode;
    outputFile.close();
}
