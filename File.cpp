
#include "File.h"


// constructor/destructor

File::File(std::string filePath) {

    ParseFile(filePath);

}

File::~File() {}


//  public methods

std::vector<std::string> File::GetFileLines() const {

    return fileLines;

}


// private functions

void File::ParseFile(std::string filePath) {

    std::string currentLine;
    std::ifstream file(filePath);

    std::array<char, 12> allowedChars { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', ' ' };

    if (file.is_open()) {

        while (getline (file, currentLine)) {

            bool charsOk {0};
            if (currentLine.size() == 0) {
                std::cout << "Plik zawiera co najmniej jedna pusta linie!\n";
                return;
            }
            for (auto const &ch : currentLine) {
                charsOk = 0;
                for (int i = 0; i < allowedChars.size(); ++i) {
                    if (ch == allowedChars[i]) charsOk = 1;
                }
                if (!charsOk) {
                    std::cout << "Plik zawiera niedozwolone znaki!\n";
                    return;
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
                return;
            }

            fileLines.push_back(currentLine);

        }

        file.close();

    }

    else std::cout << "Wystapil problem z otworzeniem pliku.";

}


