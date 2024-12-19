#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>

class Solution {
    public:
    
        Solution(const char* filename) {
            getData(filename);
        }

        int partOne() {
            int ans = 0;
            for (std::string& pattern : patterns) {
                if (isPossible(pattern)) {
                    ans++;
                }
            }
            return ans;
        }

        uint64_t partTwo() {
            uint64_t ans = 0;
            for (std::string& pattern : patterns) {
                if (isPossible(pattern)) {
                    ans += possibleWays(pattern);
                }
            }
            return ans;
        }

    
    private:
        std::vector<std::string> towels;
        std::vector<std::string> patterns;

        void getData(const char* filename) {
            std::ifstream inputFile;
            inputFile.open(filename);
            std::string line;
            getline(inputFile, line);
            while (line.find(",") != std::string::npos) {
                    size_t pos = line.find(",");
                    towels.emplace_back(line.substr(0, pos));
                    line = line.substr(pos + 2);
                }
                towels.emplace_back(line);

            getline(inputFile, line);
            while (getline(inputFile, line)) {
                patterns.emplace_back(line);
            }
        }

        bool isPossible(std::string& pattern) {
            int n = pattern.size();
            std::vector<bool> possible(n + 1, false);
            possible[0] = true;

            for (int i = 1; i <= n; i++) {
                for (std::string& towel: towels) {
                    int len = towel.size();
                    if (i >= len && pattern.substr(i - len, len) == towel) {
                        possible[i] = possible[i] || possible[i - len];
                    }
                }
            }
            return possible[n];
        }

        uint64_t possibleWays(std::string& pattern) {
            int n = pattern.size();
            std::vector<uint64_t> ways(n + 1, 0);
            ways[0] = 1;

            for (int i = 1; i <= n; i++) {
                for (std::string& towel : towels) {
                    int len = towel.size();
                    if (i >= len && pattern.substr(i - len, len) == towel) {
                        ways[i] += ways[i - len];
                    }
                }
            }
            return ways[n];
        }
};

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    Solution solution = Solution("2024/19/input.txt");
    std::cout << "Part One: " << solution.partOne() << std::endl;
    std::cout << "Part Two: " << solution.partTwo() << std::endl;

    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count() << " ms" << std::endl;
}