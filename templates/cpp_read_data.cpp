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

    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count() << " ms" << std::endl;
}