#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <unordered_map>

class Solution {
    public:
        std::unordered_map<long long, long long> stones;
        std::unordered_map<long long, long long> stones2;
    
        Solution(const char* filename) {
            getData(filename);
            stones2 = stones;
        }

        int partOne() {
            for (int i = 0; i < 25; i++) {
                blink(stones);
            }
            return countStones(stones);
        }

        long long partTwo() {
            for (int i = 0; i < 75; i++) {
                blink(stones2);
            }
            return countStones(stones2);
        }

    
    private:
        void getData(const char* filename) {
            std::ifstream inputFile;
            inputFile.open(filename);
            std::string line;
            while (getline(inputFile, line)) {
                size_t space = line.find(" ");
                while (space != std::string::npos) {
                    stones[std::stoll(line.substr(0, space))]++;
                    line = line.substr(space + 1);
                    space = line.find(" ");
                }
                stones[std::stoll(line.substr(0, space))]++;
            }
        }

        void blink(std::unordered_map<long long, long long>& stones) {
            std::unordered_map<long long, long long> newStones;

            for (auto& stone : stones) {
                std::string numString = std::to_string(stone.first);
                if (stone.first == 0) {
                    newStones[1] += stones[stone.first];
                }
                else if (numString.size() % 2 == 0) {
                    newStones[std::stoll(numString.substr(0, numString.size() / 2))] += stones[stone.first];
                    newStones[std::stoll(numString.substr(numString.size() / 2))] += stones[stone.first];
                }
                else {
                    newStones[stone.first * 2024] += stones[stone.first];
                }
            }
            stones = newStones;
        }

        long long countStones(std::unordered_map<long long, long long>& stones) {
            long long ans = 0;
            for (auto& stone : stones) {
                ans += stone.second;
            }
            return ans;
        }
};

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    Solution solution = Solution("2024/11/input.txt");
    std::cout << "Part One: " << solution.partOne() << std::endl;
    std::cout << "Part Two: " << solution.partTwo() << std::endl;

    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count() << " ms" << std::endl;
}