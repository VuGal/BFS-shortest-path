
#include "File.h"


// CONSTRUCTOR/DESTRUCTOR

File::File(std::string filePath) {

    ParseFile(filePath);

}

File::~File() {}


// PUBLIC METHODS

// getter for file contents saved in memory
std::vector<std::string> File::GetFileLines() const {

    return fileLines;

}


// PRIVATE METHODS

/*
    checks if the file consists only of numbers and spaces, has at least 3 lines
    and doesn't contain empty lines; after the checks it saves the file contents to memory
*/
void File::ParseFile(std::string filePath) {

    std::string currentLine;
    std::ifstream file(filePath);

    std::array<char, 12> allowedChars { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', ' ' };

    int linesCounter {0};

    if (file.is_open()) {

        while (getline (file, currentLine)) {

            bool charsOk {0};
            if (currentLine.size() == 0) {
                std::cout << "Plik zawiera co najmniej jedna pusta linie!\n";
                throw -1;
            }
            for (auto const &ch : currentLine) {
                charsOk = 0;
                for (size_t i = 0; i < allowedChars.size(); ++i) {
                    if (ch == allowedChars[i]) charsOk = 1;
                }
                if (!charsOk) {
                    std::cout << "Plik zawiera niedozwolone znaki!\n";
                    throw -1;
                }
            }

            bool emptyLine {0};
            for (auto const &ch : currentLine) {
                if (ch != ' ') {
                    emptyLine = 1;
                    break;
                }
            }
            if (!emptyLine) {
                std::cout << "Plik zawiera co najmniej jedna pusta linie!\n";
                throw -1;
            }

            ++linesCounter;
            fileLines.push_back(currentLine);

        }

        if (linesCounter >= 3) file.close();
        else {
            std::cout << "Plik zawiera mniej niz 3 linie!\n";
            throw -1;
        }

    }

    else std::cout << "Wystapil problem z otworzeniem pliku.";

}


