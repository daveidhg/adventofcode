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
            int prioritySum = 0;
            for (std::string line : data) {
                std::string s1 = line.substr(0, line.length() / 2);
                std::string s2 = line.substr(line.length() / 2);
                for (char c : s1) {
                    if (s2.find(c) != std::string::npos) {
                        if (islower(c)) {
                            prioritySum += c - 'a' + 1;
                        } else {
                            prioritySum += c - 'A' + 27;
                        }
                        break;
                    }
                }
            }
            return prioritySum;
        }

        int partTwo() {
            int prioritySum = 0;
            for (int i = 0; i < data.size() - 1; i += 3)
            {
                std::string s1 = data[i];
                std::string s2 = data[i + 1];
                std::string s3 = data[i + 2];
                for (char c : s1) {
                    if (s2.find(c) != std::string::npos && s3.find(c) != std::string::npos) {
                        if (islower(c)) {
                            prioritySum += c - 'a' + 1;
                        } else {
                            prioritySum += c - 'A' + 27;
                        }
                        break;
                    }
                }
            }
            return prioritySum;
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
    Solution solution = Solution("2022/03/input.txt");
    int partOne = solution.partOne();
    std::cout << "Part One: " << partOne << std::endl;
    int partTwo = solution.partTwo();
    std::cout << "Part Two: " << partTwo << std::endl;
    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count() << " ms" << std::endl;
}