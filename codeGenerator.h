#pragma once

#include <string>

class codeGenerator {
    public:
        codeGenerator(const std::string& boilerPlateCodeFileName);
        void generateASMFile(const std::string& fileName, const std::string& asmCode);
    private:
        void loadBoilerPlateCode(const std::string& fileName);
        std::string boilerPlateCode;
};
