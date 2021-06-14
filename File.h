#pragma once

#include <iostream>
#include <fstream>
#include <array>
#include <vector>


class File {

    public:
        File(std::string filePath);
        virtual ~File();

        std::vector <std::string> GetFileLines() const;

    private:
        std::vector<std::string> fileLines {};

        void ParseFile(std::string filePath);

};

