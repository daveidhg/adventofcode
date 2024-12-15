#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>

class Solution {
    public:
        std::vector<std::string> warehouse;
        std::string instructions;
    
        Solution(const char* filename) {
            getData(filename);
        }

        int partOne() {
            executeInstructions();	
            return calculateCoordinates();
        }

    
    private:
        std::pair<int, int> position;

        void getData(const char* filename) {
            std::ifstream inputFile;
            inputFile.open(filename);
            std::string line;
            bool warehouseDone = false;
            while (getline(inputFile, line)) {
                if (!warehouseDone) {
                    if (line == "") {
                        warehouseDone = true;
                    } else {
                        warehouse.emplace_back(line);
                        if (line.find('@') != std::string::npos) {
                            position = std::make_pair(line.find('@'), warehouse.size() - 1);
                        }
                    }
                }
                else {
                    instructions += line;
                }
            }
        }

        std::pair<int, int> getDirection(char& instruction) {
            switch (instruction) {
                case '^':
                    return std::make_pair(0, -1);
                case 'v':
                    return std::make_pair(0, 1);
                case '<': 
                    return std::make_pair(-1, 0);
                case '>':
                    return std::make_pair(1, 0);
                default:
                    throw std::invalid_argument("Invalid instruction");
            }
        }

        void moveRobot(std::pair<int, int>& position, char& instruction) {
            std::pair<int, int> direction = getDirection(instruction);
            if (int move = isLegalMove(position, direction)) {
                warehouse[position.second][position.first] = '.';
                if (warehouse[position.second + direction.second][position.first + direction.first] == 'O') {
                    warehouse[position.second + direction.second * move][position.first + direction.first * move] = 'O';
                }
                position.first += direction.first;
                position.second += direction.second;
                warehouse[position.second][position.first] = '@';
                int i = 0;
            }
        }

        int isLegalMove(std::pair<int, int>& position, std::pair<int, int>& direction) {
            int iterator = 1;
            while (true) {
                switch (warehouse[position.second + direction.second * iterator][position.first + direction.first * iterator]) {
                    case '.':
                        return iterator;
                    case '#':
                        return 0;
                    case 'O':
                        iterator++;
                        continue;
                    default:
                        throw std::invalid_argument("Invalid character in warehouse");
                }
            }
        }

        void executeInstructions() {
            for (char& instruction : instructions) {
                moveRobot(position, instruction);
            }
        }

        int calculateCoordinates() {
            int count = 0;
            for (int i = 0; i < warehouse.size(); i++) {
                for (int j = 0; j < warehouse[i].size(); j++) {
                    if (warehouse[i][j] == 'O') {
                        count += i * 100 + j;
                    }
                }
            }
            return count;
        }
};

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    Solution solution = Solution("2024/15/input.txt");
    std::cout << "Part One: " << solution.partOne() << std::endl;

    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count() << " ms" << std::endl;
}