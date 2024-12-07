#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>

class Solution {
    public:
        std::vector<std::string> data;
    
        Solution(const char* filename) {
            getData(filename);
        }

        int partOne() {
            return 0;
        }

        int partTwo() {
            return 0;
        }

    
    private:
        void getData(const char* filename) {
            std::ifstream inputFile;
            inputFile.open(filename);
            std::string line;
            while (getline(inputFile, line)) {
                data.push_back(line);
            }
        }
};

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    Solution solution = Solution("year/day/input.txt");
    std::cout << "Part One: " << solution.partOne() << std::endl;
    std::cout << "Part Two: " << solution.partTwo() << std::endl;

    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count() << " ms" << std::endl;
}