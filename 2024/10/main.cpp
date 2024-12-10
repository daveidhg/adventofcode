#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <set>

class Solution {
    public:
        std::vector<std::vector<int> > map;
        std::vector<std::pair<int, int> > startPoints;
    
        Solution(const char* filename) {
            getData(filename);
        }

        int partOne() {
            return getAllTrailheadScores();
        }

        int partTwo() {
            return getAllTrailheadScores(true);
        }

    
    private:
        std::vector<std::pair<int, int> > directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        std::set<std::pair<int, int> > visited;
        int height, width;

        void getData(const char* filename) {
            std::ifstream inputFile;
            inputFile.open(filename);
            std::string line;
            std::vector<int> row;
            int y = 0;
            while (getline(inputFile, line)) {
                row.clear();
                for (int x = 0; x < line.size(); x++) {
                    row.emplace_back(line[x] - '0');
                    if (line[x] == '0') {
                        startPoints.emplace_back(std::make_pair(x, y));

                    }
                }
                y++;
                map.emplace_back(row);
            }
            height = map.size();
            width = map[0].size();
        }

        int getTrailheadScore(int x, int y, int lastNum, bool distinct = false) {
            int score = 0;
            if (lastNum == 9) {
                if (distinct) {
                    if (visited.find({x, y}) == visited.end()) {
                        visited.insert({x, y});
                        return 1;
                    }
                }
                else
                return 1;
            }
            for (auto& direction : directions) {
                int nx = x + direction.first;
                int ny = y + direction.second;
                if (nx < 0 || nx >= width || ny < 0 || ny >= height) {
                    continue;
                }
                if (map[ny][nx] == lastNum + 1) {
                    score += getTrailheadScore(nx, ny, lastNum + 1, distinct);
                }
            }
            return score;
        }

        int getAllTrailheadScores(bool partTwo = false) {
            int score = 0;
            int res;
            for (auto& startPoint : startPoints) {
                if (partTwo) {
                    res = getTrailheadScore(startPoint.first, startPoint.second, 0);
                }
                else {
                    visited.clear();
                    res = getTrailheadScore(startPoint.first, startPoint.second, 0, true);
                }
                score += res;
            }
            return score;
        }
};

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    Solution solution = Solution("2024/10/input.txt");
    std::cout << "Part One: " << solution.partOne() << std::endl;
    std::cout << "Part Two: " << solution.partTwo() << std::endl;

    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count() << " ms" << std::endl;
}