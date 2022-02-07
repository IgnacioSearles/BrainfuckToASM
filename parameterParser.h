#pragma once
#include <string>

class parameterParser {
    public:
        parameterParser(char** argv, int argc);
        std::string getInputFileName();
        std::string getOutputFileName();
    private:
        std::string getRequiredParameter(const std::string& parameterId);
        std::string getOptionalParameter(const std::string& parameterId);

        std::string passedArgs;
};
