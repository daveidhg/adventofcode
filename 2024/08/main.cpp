#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <unordered_map>
#include <set>

class Solution {
    public:
        Solution(const char* filename) {
            getData(filename);
        }

        int partOne() {
            std::set<std::pair<int, int> > antinodes;
            for (auto& [antenna, positions] : antennas) {
                for (int i = 0; i<positions.size(); i++) {
                    for (int j = i+1; j<positions.size(); j++) {
                        calculateAntinodes(positions[i], positions[j], antinodes);
                    }
                }
            }
            return countAntinodesInBounds(antinodes);
        }

        int partTwo() {
            std::set<std::pair<int, int> > antinodes;
            for (auto& [antenna, positions] : antennas) {
                for (int i = 0; i<positions.size(); i++) {
                    for (int j = i+1; j<positions.size(); j++) {
                        calculateHarmonics(positions[i], positions[j], antinodes);
                    }
                }
            }
            return antinodes.size();
        }

    
    private:
        std::unordered_map<char, std::vector<std::pair<int, int> > > antennas;
        int width;
        int height;
        
        void getData(const char* filename) {
            std::ifstream inputFile;
            inputFile.open(filename);
            std::string line;
            int y = 0;
            while (getline(inputFile, line)) {
                for (int x = 0; x<line.size(); x++) {
                    if (line[x] != '.') {
                        antennas[line[x]].emplace_back(x, y);
                    }
                }
                y++;
            }
            width = line.size();
            height = y;
        }

        void calculateAntinodes(std::pair<int, int>& a, std::pair<int, int>& b, std::set<std::pair<int, int> >& antinodes) {
            int dx = b.first - a.first;
            int dy = b.second - a.second;
            antinodes.insert({a.first - dx, a.second - dy});
            antinodes.insert({b.first + dx, b.second + dy});
        }

        void calculateHarmonics(std::pair<int, int>& a, std::pair<int, int>& b, std::set<std::pair<int, int> >& antinodes) {
            int dx = b.first - a.first;
            int dy = b.second - a.second; 
            int offset = 0;
            while (a.first - offset * dx >= 0 && a.first - offset * dx < width && a.second - offset * dy >= 0 && a.second - offset * dy < height) {
                antinodes.insert({a.first - offset * dx, a.second - offset * dy});
                offset++;
            }
            offset = 0;
            while (b.first + offset * dx >= 0 && b.first + offset * dx < width && b.second + offset * dy >= 0 && b.second + offset * dy < height) {
                antinodes.insert({b.first + offset * dx, b.second + offset * dy});
                offset++;
            }
        }


        int countAntinodesInBounds(std::set<std::pair<int, int> >& antinodes) {
            int count = 0;
            for (auto& antinode : antinodes) {
                if (antinode.first >= 0 && antinode.first < width && antinode.second >= 0 && antinode.second < height) {
                    count++;
                }
            }
            return count;
        }
};

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    Solution solution = Solution("2024/08/input.txt");
    std::cout << "Part One: " << solution.partOne() << std::endl;
    std::cout << "Part Two: " << solution.partTwo() << std::endl;

    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count() << " ms" << std::endl;
}