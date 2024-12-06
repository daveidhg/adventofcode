#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <set>

class Solution {
    public:
        std::vector<std::string> data;
        std::pair<int, int> start;
        std::set<std::pair<int, int> > visited;
    
        Solution(const char* filename) {
            getData(filename);
        }

        int partOne() {
            int dirIdx = 0;
            int maxX = data[0].size();
            int maxY = data.size();
            std::pair<int, int> pos = start;
            visited.insert(pos);
            while (true) {
                std::pair<int, int> newPos = pos;
                newPos.first += directions[dirIdx].first;
                newPos.second += directions[dirIdx].second;
                if (newPos.first < 0 || newPos.first >= maxY || newPos.second < 0 || newPos.second >= maxX) {
                    break;
                }
                else if (data[newPos.first][newPos.second] == '#') {
                    dirIdx = (dirIdx + 1) % 4;
                }
                else {
                    pos = newPos;
                    visited.insert(pos);
                }
            }
            return visited.size();
        }

        int partTwo() {
            int ans = 0;
            for (auto visitedPos : visited) {
                int dirIdx = 0;
                if (data[visitedPos.first][visitedPos.second] == '^') {
                    continue;
                }
                data[visitedPos.first][visitedPos.second] = '#';

                std::set<std::pair<std::pair<int, int>, int> > visitedWithDirection;
                std::pair<int, int> pos = start;
                std::pair<int, int>& posPointer = pos;
                std::pair<int, int> newPos;
                int maxX = data[0].size();
                int maxY = data.size();
                while (true) {
                    visitedWithDirection.insert({pos, dirIdx});
                    newPos = pos;
                    newPos.first += directions[dirIdx].first;
                    newPos.second += directions[dirIdx].second;
                    if (newPos.first < 0 || newPos.first >= maxY || newPos.second < 0 || newPos.second >= maxX) {
                        break;
                    }
                    else if (data[newPos.first][newPos.second] == '#') {
                        dirIdx = (dirIdx + 1) % 4;                       
                    }
                    else {
                        pos = newPos;
                        if (visitedWithDirection.find({posPointer, dirIdx}) != visitedWithDirection.end()) {
                            ans++;
                            break;
                        } 
                    }
                }
                data[visitedPos.first][visitedPos.second] = '.';
            }
            return ans;
        }
    
    private:
        std::vector<std::pair<int, int> > directions = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

        void getData(const char* filename) {
            std::ifstream inputFile;
            inputFile.open(filename);
            std::string line;
            bool startFound = false;
            int y = 0;
            while (getline(inputFile, line)) {
                data.push_back(line);
                if (!startFound) {
                    for (int x = 0; x < line.size(); x++) {
                        if  (line[x] == '^') {
                            start = std::make_pair(y, x);
                        }
                    }
                    y++;
                }
            }
        }
};

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    Solution solution = Solution("2024/06/input.txt");
    std::cout << "Part one: " << solution.partOne() << std::endl;
    std::cout << "Part two: " << solution.partTwo() << std::endl;

    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count() << " ms" << std::endl;
}