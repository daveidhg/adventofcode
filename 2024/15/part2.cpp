#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <queue>
#include <set>
#include <algorithm>

struct BoxesToBeMoved {
    std::vector<std::pair<int, int>> boxes;
    std::pair<int, int> robot;
    std::pair<int, int> direction;

    explicit operator bool() const {
        return !boxes.empty();
    }

    BoxesToBeMoved() : boxes(), robot(), direction() {}
    BoxesToBeMoved(std::vector<std::pair<int, int>> boxes, std::pair<int, int> robot, std::pair<int, int> direction) : boxes(boxes), robot(robot), direction(direction) {}
};

class Solution {
    public:
        std::vector<std::string> warehouse;
        std::string instructions;
    
        Solution(const char* filename) {
            getData(filename);
        }

        int partTwo() {
            for (char& instruction : instructions) {
                std::pair<int, int> direction = getDirection(instruction);
                if (BoxesToBeMoved boxesToBeMoved = legalMove(direction)) {
                    moveRobot(boxesToBeMoved);
                }
            }
            return calculateCoordValues();
        }

    
    private:
        std::pair<int, int> position;

        void getData(const char* filename) {
            std::ifstream inputFile;
            inputFile.open(filename);
            std::string line;
            bool warehouseDone = false;
            std::string row;
            while (getline(inputFile, line)) { 
                if (!warehouseDone) {
                    if (line == "") {
                        warehouseDone = true;
                    } else {
                        for (auto& c : line) {
                            if (c == '#') {
                                row += "##";
                            }
                            else if (c == '.') {
                                row += "..";
                            }
                            else if (c == '@') {
                                row += "@.";
                                position = std::make_pair(row.size() - 2, warehouse.size());
                            }
                            else {
                                row += "[]";
                            }
                        }
                        warehouse.emplace_back(row);
                        row = "";
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

        BoxesToBeMoved legalMove(std::pair<int, int>& direction) {
            std::vector<std::pair<int, int> > boxes;
            std::set<std::pair<int, int> > visited;
            if (direction.first == 0) {
                std::queue <std::pair<int, int> > q;
                q.push(position);
                while (!q.empty()) {
                    std::pair<int, int> current = q.front();
                    q.pop();
                    if (visited.find(current) != visited.end()) {
                        continue;
                    }
                    char currentChar = warehouse[current.second][current.first];
                    if (currentChar == '#') {
                        return BoxesToBeMoved();
                    }
                    else if (currentChar == '[') {
                        boxes.emplace_back(current);
                        q.push(std::make_pair(current.first + 1, current.second));
                        q.push(std::make_pair(current.first, current.second + direction.second));
                    }
                    else if (currentChar == ']') {
                        boxes.emplace_back(current);
                        q.push(std::make_pair(current.first - 1, current.second));
                        q.push(std::make_pair(current.first, current.second + direction.second));
                    }
                    else if (currentChar == '@') {
                        q.push(std::make_pair(current.first, current.second + direction.second));
                        boxes.emplace_back(current);
                    }
                    visited.insert(current);
                }
            }
            else {
                std::queue <std::pair<int, int> > q; 
                q.push(position);
                while (!q.empty()) {
                    std::pair<int, int> current = q.front();
                    q.pop();
                    char currentChar = warehouse[current.second][current.first];
                    if (currentChar == '#') {
                        return BoxesToBeMoved();
                    }
                    else if (currentChar == '[' || currentChar == ']') {
                        q.push(std::make_pair(current.first + direction.first, current.second));   
                        boxes.emplace_back(current);
                    }
                    else if (currentChar == '@') {
                        q.push(std::make_pair(current.first + direction.first, current.second));
                        boxes.emplace_back(current);
                    }
                }
            }
            return BoxesToBeMoved(boxes, position, direction);
        }

        void moveRobot(BoxesToBeMoved& boxesToBeMoved) {
            std::pair<int, int> direction = boxesToBeMoved.direction;
            std::sort(boxesToBeMoved.boxes.begin(), boxesToBeMoved.boxes.end(), [direction](std::pair<int, int>& a, std::pair<int, int>& b) {
                if (direction.second == 1) {
                    return a.second > b.second;
                }
                else if (direction.second == -1) {
                    return a.second < b.second;
                }
                else if (direction.first == 1) {
                    return a.first > b.first;
                }
                return a.first < b.first;
            });
            for (auto& box : boxesToBeMoved.boxes) {
                warehouse[box.second + direction.second][box.first + direction.first] = warehouse[box.second][box.first];
                warehouse[box.second][box.first] = '.';
            }
            warehouse[position.second][position.first] = '.';
            position.first += direction.first;
            position.second += direction.second;
        }

        int calculateCoordValues() {
            int sum = 0;
            for (int i = 1; i < warehouse.size() - 1; i++) {
                for (int j = 1; j < warehouse[i].size() - 1; j++) {
                    if (warehouse[i][j] == '[') {
                        sum += i * 100 + j;
                    }
                }
            }
            return sum;
        }
};

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    Solution solution = Solution("2024/15/input.txt");
    std::cout << "Part Two: " << solution.partTwo() << std::endl;

    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count() << " ms" << std::endl;
}