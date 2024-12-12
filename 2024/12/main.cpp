#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <set>
#include <queue>

class Solution {
    public:
        std::vector<std::string> data;
    
        Solution(const char* filename) {
            getData(filename);
        }

        int partOne() {
            int ans = 0;
            for (auto& region : regions) {
                ans += getArea(region) * getPerimeter(region);
            }
            return ans;
        }

        int partTwo() {
            int ans = 0;
            for (auto& region : regions) {
                int area = getArea(region);               
                int sides = getSides(region);
                ans += area * sides;
            }
            return ans;
        }

    
    private:
        std::vector<std::pair<int, int> > directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        std::vector<std::set<std::pair<int, int> > > regions;
        int width;
        int height;

        void getData(const char* filename) {
            std::ifstream inputFile;
            inputFile.open(filename);
            std::string line;
            while (getline(inputFile, line)) {
                data.push_back(line);
            }
            getRegions();
        }

        void getRegions() {
            std::set<std::pair<int, int> > visited;
            
            height = data.size();
            width = data[0].size();
            for (int y = 0; y < height; y++) {
                for (int x = 0; x < width; x++) {
                    if (visited.find({x, y}) != visited.end()) {
                        continue;
                    }
                    std::set<std::pair<int, int> > region; 
                    std::queue<std::pair<int, int> > q;
                    q.push({x, y});
                    while (!q.empty()) {
                        auto [currentX, currentY] = q.front();
                        q.pop();
                        if (region.find({currentX, currentY}) != region.end()) {
                            continue;
                        }
                        region.insert({currentX, currentY});
                        visited.insert({currentX, currentY});
                        for (auto& [dx, dy] : directions) {
                            int newX = currentX + dx;
                            int newY = currentY + dy;
                            if (newX >= 0 && newX < width && newY >= 0 && newY < height && data[newY][newX] == data[y][x]) {
                                q.push({newX, newY});
                            }
                        }
                    }
                    regions.push_back(region);
                }
            }
        }

        int getArea(std::set<std::pair<int, int> >& region) {
            return region.size();
        }

        int getPerimeter(std::set<std::pair<int, int> >& region) {
            int perimeter = 0; 
            auto& [x, y] = *region.begin();
            char plant = data[y][x];
            for (auto& [x, y] : region) {
                for (auto& [dx, dy] : directions) {
                    int newX = x + dx;
                    int newY = y + dy;
                    if (newX < 0 || newX >= width || newY < 0 || newY >= height || data[newY][newX] != plant) {
                        perimeter++;
                    }
                }
            }
            return perimeter;
        }

        int getSides(std::set<std::pair<int, int> >& region) {
            int sides = 0;
            std::set<std::pair<std::pair<int, int>, std::pair<int, int> > > edges;
            for (auto& [x, y] : region) {
                for (auto& [dx, dy] : directions) {
                    int newX = x + dx;
                    int newY = y + dy;
                    if (region.find({newX, newY}) != region.end()) {
                        continue;
                    }
                    edges.insert({{newX, newY}, {dx, dy}});
                }
            }
            for (auto& [pos, dir] : edges) {
                auto& [x, y] = pos;
                if (dir.first) {
                    int dy = 1;
                    int newY = y + dy;
                    while (edges.find({{x, newY}, {dir.first, dir.second}}) != edges.end()) {
                        edges.erase({{x, newY}, {dir.first, dir.second}});
                        newY += dy;
                    }
                    dy = -1;
                    newY = y + dy;
                    while (edges.find({{x, newY}, {dir.first, dir.second}}) != edges.end()) {
                        edges.erase({{x, newY}, {dir.first, dir.second}});
                        newY += dy;
                    }
                }
                else {
                    int dx = 1;
                    int newX = x + dx;
                    while (edges.find({{newX, y}, {dir.first, dir.second}}) != edges.end()) {
                        edges.erase({{newX, y}, {dir.first, dir.second}});
                        newX += dx;
                    }
                    dx = -1;
                    newX = x + dx;
                    while (edges.find({{newX, y}, {dir.first, dir.second}}) != edges.end()) {
                        edges.erase({{newX, y}, {dir.first, dir.second}});
                        newX += dx;
                    }
                }
                sides++;
            }
            return sides;
        }
};

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    Solution solution = Solution("2024/12/input.txt");
    std::cout << "Part One: " << solution.partOne() << std::endl;
    std::cout << "Part Two: " << solution.partTwo() << std::endl;

    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count() << " ms" << std::endl;
}