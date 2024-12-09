#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <algorithm>

class Solution {
    public:
        std::vector<std::string> data;
        std::vector<std::string> data2;
    
        Solution(const char* filename) {
            getData(filename);
        }

        long long partOne() {
            moveBlocks();
            return countChecksum(data);
        }

        long long partTwo() {
            moveBlocks2(); 
            return countChecksum(data2);
        }

    
    private:
        void getData(const char* filename) {
            std::ifstream inputFile;
            inputFile.open(filename);
            std::string line;
            int num;
            bool isEven = true;
            while (getline(inputFile, line)) {
                for (int i = 0; i < line.size(); i++) {
                    num = line[i] - '0';
                    for (int j = 0; j < num; j++) {
                        if (isEven) {
                            data.emplace_back(std::to_string(i / 2));
                        }
                        else {
                            data.emplace_back(".");
                        }
                    }
                    isEven = !isEven;
                }
            }
            data2 = data;
        }

        void moveBlocks() {
            auto lastNonDot = std::find_if(data.rbegin(), data.rend(), [](const std::string& s) { return s != "."; }).base() - 1;
            auto firstDot = std::find(data.begin(), data.end(), ".");
            while (firstDot < lastNonDot) {
            std::iter_swap(firstDot, lastNonDot);
            lastNonDot = std::find_if(std::make_reverse_iterator(lastNonDot), data.rend(), [](const std::string& s) { return s != "."; }).base() - 1;
            firstDot = std::find(firstDot + 1, data.end(), ".");
            }
            data.erase(std::find(data.begin(), data.end(), "."), data.end());
        }

        void moveBlocks2() {
            int lastNum = data2.size() - 1;
            std::string lastNumStr;
            int blockSize;
            int lastDot;
            int dotSize;
            while (lastNum >= 0) {
                lastNumStr = data2[lastNum];
                if (lastNumStr == ".") {
                    lastNum--;
                    continue;
                }
                blockSize = 1;
                while (data2[--lastNum] == lastNumStr) {
                    blockSize++;
                }
                lastDot = 0;
                dotSize = 0;
                while (lastDot < lastNum) {
                    if (data2[lastDot] == ".") {
                        dotSize++; 
                        if (dotSize == blockSize) {
                            for (int i = 0; i < blockSize; i++) {
                                std::iter_swap(data2.begin() + lastDot - i, data2.begin() + lastNum + i + 1);
                            }
                            break;
                        }
                    }
                    else {
                        dotSize = 0;
                    }
                    lastDot++;
                }
            }
        }

        long long countChecksum(std::vector<std::string> data) {
            long long count = 0;
            for (long long i = 0; i < data.size(); i++) {
                if (data[i] == ".") continue;
                count += (std::stoll(data[i])) * i;
            }
            return count;
        }
};

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    Solution solution = Solution("2024/09/input.txt");
    std::cout << "Part One: " << solution.partOne() << std::endl;
    std::cout << "Part Two: " << solution.partTwo() << std::endl;

    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count() << " ms" << std::endl;
}