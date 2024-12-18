#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <set>
#include <queue>

class Solution {
    public:
        std::vector<std::pair<int, int> > data;
    
        Solution(const char* filename) {
            getData(filename);
        }

        int partOne() {
            simulateBytes();
            return getShortestDistance();
        }

        std::string partTwo() {
            int low = 0;
            int high = data.size() - 1;
            while (low < high) {
                corrupted.clear();
                int mid = (low + high) / 2;
                for (int i = 0; i < mid + 1; i++) {
                    corrupted.insert(data[i]);
                }
                if (getShortestDistance() == -1) {
                    high = mid;
                }
                else {
                    low = mid + 1;
                }
            }
            return std::to_string(data[low].first) + "," + std::to_string(data[low].second);
        }

    
    private:
        std::vector<std::pair<int, int> > const dmove {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
        std::set<std::pair<int, int> > corrupted;
        std::pair<int, int> end;
        int mapSize;
        void getData(const char* filename) {
            std::ifstream inputFile;
            inputFile.open(filename);
            std::string line;
            while (getline(inputFile, line)) {
                data.push_back({std::stoi(line.substr(0, line.find(","))), std::stoi(line.substr(line.find(",") + 1))});
            }
        }

        void simulateBytes(int bytes = 1024) {
            for (int i = 0; i < bytes; i++) {
                corrupted.insert(data[i]);
            }
            if (bytes == 1024) {
                mapSize = 71;
            }
            else {
                mapSize = 7;
            }
            end = {mapSize - 1, mapSize - 1};
        }

        int getShortestDistance() {
            std::set<std::pair<int, int> > visited;
            std::queue<std::vector<int> > q;
            q.push({0, 0, 0});
            while (!q.empty()) {
                std::vector<int>& current = q.front();
                if (current[0] == end.first && current[1] == end.second) {
                    return current[2];
                }
                for (int i = 0; i < 4; i++) {
                    int x = current[0] + dmove[i].first;
                    int y = current[1] + dmove[i].second;
                    if (x >= 0 && x < mapSize && y >= 0 && y < mapSize && !visited.count({x, y}) && !corrupted.count({x, y})) {
                        visited.insert({x, y});
                        q.push({x, y, current[2] + 1});
                    }
                }
                q.pop();
            }
            return -1;
        }
};

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    Solution solution = Solution("2024/18/input.txt");
    std::cout << "Part One: " << solution.partOne() << std::endl;
    std::cout << "Part Two: " << solution.partTwo() << std::endl;

    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count() << " ms" << std::endl;
}