#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <functional>
#include <cmath>

class Solution {
    public:
        std::vector<long long> registers;
        std::vector<int> program;
    
        Solution(const char* filename) {
            getData(filename);
            long long i = 0;
        }

        std::string partOne() {
            runProgram();
            return calculateAnswer();
        }

        long long partTwo() {
            long long ans = 0;
            return findA(program, ans);
        }

    
    private:
        int instructionPointer = 0;
        std::vector<int> output;

        std::vector<std::function<void(int)> > operations = {
            [this](int b) {long long a = registers[0]; b = pow(2, getOperandValue(b)); registers[0] = a / b; instructionPointer += 2;},
            [this](int b) {long long a = registers[1]; registers[1] = a ^ b; instructionPointer += 2;},
            [this](int b) {registers[1] = getOperandValue(b) % 8; instructionPointer += 2;},
            [this](int b) {long long a = registers[0]; if (a == 0) {instructionPointer += 2; return;} instructionPointer = b;},
            [this](int b) {long long a = registers[2]; registers[1] = a ^ registers[1]; instructionPointer += 2;},
            [this](int b) {output.push_back(getOperandValue(b) % 8); instructionPointer += 2;},
            [this](int b) {long long a = registers[0]; b = pow(2, getOperandValue(b)); registers[1] = a / b; instructionPointer += 2;},
            [this](long long b) {long long a = registers[0]; b = pow(2, getOperandValue(b)); registers[2] = a / b; instructionPointer += 2;}
        };

        void getData(const char* filename) {
            std::ifstream inputFile;
            inputFile.open(filename);
            std::string line;
            bool tmp = false;
            while (getline(inputFile, line)) {
                if (line == "") {
                    tmp = true;
                    continue;
                }
                if (!tmp) {
                    line = line.substr(line.find(": ") + 2);
                    registers.push_back(std::stoll(line));
                }
                else {
                    line = line.substr(line.find(" ") +1);
                    for (int i = 0; i < line.size(); i += 2) {
                        program.push_back(std::stoll(line.substr(i, 1)));
                    }
                }
            }
        }

        long long getOperandValue(long long operand) {
            if (operand < 4) {
                return operand;
            }
            else {
                return registers[operand - 4];
            }
        }

        void runProgram() {
            instructionPointer = 0;
            while (instructionPointer < program.size()) {
                int instruction = program[instructionPointer];
                int operand = program[instructionPointer + 1];
                operations[instruction](operand);
            }
        }

        std::string calculateAnswer() {
            std::string ans = "";
            for (int i = 0; i < output.size(); i++) {
                ans += std::to_string(output[i]) + ',';
            }
            ans.pop_back();
            return ans;
        }

        long long findA(std::vector<int> target, long long& ans) {
            if (target.size() == 0) {
                return ans;
            }
            for (int t = 0; t < 8; t++) {
                long long a = ans << 3 | t;
                registers[0] = a;
                registers[1] = 0;
                registers[2] = 0;
                output.clear();
                for (int i = 0; i < program.size(); i += 2) {
                    int instruction = program[i];
                    int operand = program[i + 1];
                    operations[instruction](operand);
                    if (!output.empty() && output[0] == target[target.size() - 1]) {
                        long long sub = findA(std::vector<int>(target.begin(), target.end() - 1), a);
                        if (sub == -1) {
                            continue;
                        }
                        return sub;
                    }
                }
            }
            return -1;
        }

};

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    Solution solution = Solution("2024/17/input.txt");
    std::cout << "Part One: " << solution.partOne() << std::endl;
    std::cout << "Part Two: " << solution.partTwo() << std::endl;

    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count() << " ms" << std::endl;
}