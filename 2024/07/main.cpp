#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <unordered_map>
#include <functional>

class Solution {
    public:
        std::vector<std::unordered_map<long long, std::vector<long long> > > data;
    
        Solution(const char* filename) {
            getData(filename);
        }

        long long partOne() {
            long long ans = 0;
            for (auto& entry : data) {
                for (auto& [target, nums] : entry) {
                    ans += evaluate(nums, target) ? target : 0;
                }
            }
            return ans;
        }

        long long partTwo() {
            operations.push_back([](long long a, long long b) { return std::stoll(std::to_string(a) + std::to_string(b)); });
            return partOne();
        }

    
    private:
        std::vector<std::function<long long(long long, long long)> > operations = {
            [](long long a, long long b) { return a + b; },
            [](long long a, long long b) { return a * b; }
        };

        void getData(const char* filename) {
            std::ifstream inputFile;
            inputFile.open(filename);
            std::string line;
            long long num;
            std::vector<long long> nums;
            while (getline(inputFile, line)) {
                num = std::stoll(line.substr(0, line.find(":")));
                line = line.substr(line.find(":") + 2);
                while (line.find(" ") != std::string::npos) {
                    nums.push_back(std::stoll(line.substr(0, line.find(" "))));
                    line = line.substr(line.find(" ") + 1);
                }
                nums.push_back(std::stoi(line));
                data.push_back({{num, nums}});
                nums.clear();
            }
        }

        bool evaluate(std::vector<long long>& nums, long long target) {
            if (nums.size() == 1) {
                return nums[0] == target;
            }
            for (auto& operation : operations) {
                long long value = operation(nums[0], nums[1]);
                std::vector<long long> newNums = {value};
                newNums.insert(newNums.end(), nums.begin() + 2, nums.end());
                if (evaluate(newNums, target)) {
                    return true;
                }
            }
            return false;
        }
};

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    Solution solution = Solution("2024/07/input.txt");
    std::cout << "Part one: " << solution.partOne() << std::endl;
    std::cout << "Part two: " << solution.partTwo() << std::endl;

    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count() << " ms" << std::endl;
}