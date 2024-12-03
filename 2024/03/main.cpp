#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>

class Solution {
    public:
        std::vector<std::pair<int, int> > data;
        std::vector<std::string> lines;
        std::vector<std::string> enabledSections;
        std::vector<std::pair<int, int> > data2;
    
        Solution(const char* filename) {
            getData(filename);
        }

        int partOne() {
            int ans = 0;
            for (auto& p : data) {
                ans += p.first * p.second;
            }
            return ans;
        }

        int partTwo() {
            getData2(); 
            int ans = 0;
            for (auto& p : data2) {
                ans += p.first * p.second;
            }
            return ans;
        }

    
    private:
        void getData(const char* filename) {
            std::ifstream inputFile;
            inputFile.open(filename);
            std::string line;
            while (getline(inputFile, line)) {
                lines.push_back(line);
                collectMulExpresssions(line, data);
            }
        }

        void getData2() {
            bool enabled = true;
            for (std::string line : lines) {
                size_t pos = 0;
                while (line.find("do()", pos) != std::string::npos) {
                    if (enabled) {
                        if (line.find("don't()", pos) != std::string::npos) {
                            size_t endPos = line.find("don't()", pos);
                            enabledSections.push_back(line.substr(pos, endPos - pos));
                            pos = endPos;
                            enabled = false;
                        }
                        else {
                            enabledSections.push_back(line.substr(pos));
                            break;
                        }
                    }
                    else {
                        if (line.find("do()", pos) != std::string::npos) {
                            pos = line.find("do()", pos);
                            enabled = true;
                        }
                    }
                }
            }
            for (std::string section : enabledSections) {
                collectMulExpresssions(section, data2);
            }
        }

        void collectMulExpresssions(std::string line, std::vector<std::pair<int, int> >& dataVector) {
            size_t pos = 0;
            while (line.find("mul(", pos) != std::string::npos) {
                pos = line.find("mul(", pos);
                size_t endPos = line.find(")", pos);
                std::string temp = line.substr(pos + 4, endPos - pos - 4);
                insertIfValid(temp, dataVector);
                pos = line.find("mul(", pos + 1);
            }
            pos = 0;
        }

        void insertIfValid(std::string mulExpression, std::vector<std::pair<int, int> >& dataVector) {
            if (mulExpression.find(",") == std::string::npos) {
                return;
            }
            std::string num1 = mulExpression.substr(0, mulExpression.find(","));
            std::string num2 = mulExpression.substr(mulExpression.find(",") + 1);
            if (isValid(num1) && isValid(num2)) {
                dataVector.push_back(std::make_pair(std::stoi(num1), std::stoi(num2)));
            }
        }

        bool isValid(std::string num) {
            for (char c : num) {
                if (!std::isdigit(c)) {
                    return false;
                }
            }
            return true;
        }
};

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    Solution solution = Solution("2024/03/input.txt");
    int partOne = solution.partOne();
    std::cout << "Part One: " << partOne << std::endl;
    int partTwo = solution.partTwo();
    std::cout << "Part Two: " << partTwo << std::endl; 

    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count() << " ms" << std::endl;
}