#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>


class Solution {
    public:
        std::vector<std::vector<int> > updates;
        std::vector<std::vector<int> > invalidUpdates;
        std::unordered_map<int, std::unordered_set<int> > rules;
    
        Solution(const char* filename) {
            getData(filename);
        }

        int partOne() {
            int ans = 0;
            for (auto update : updates) {
                bool invalid = false;
                for (int i = 0; i < update.size(); i++) {
                    if (invalid) {
                        break;
                    }
                    for (int j = i + 1; j < update.size(); j++) {
                        if (rules[update[i]].find(update[j]) != rules[update[i]].end()) {
                            invalid = true;
                            invalidUpdates.push_back(update);
                            break;
                        }
                    }
                } 
                if (!invalid)
                ans += update[update.size() / 2];              
            }
            return ans;
        }

        int partTwo() {
            int ans = 0;
            auto sorter = [this](int left, int right) { return Solution::sorter(left, right, rules); };
            for (auto update : invalidUpdates) {
                std::sort(update.begin(), update.end(), sorter);
                ans += update[update.size() / 2];
            }
            return ans;
        }

    
    private:
        void getData(const char* filename) {
            std::ifstream inputFile;
            inputFile.open(filename);
            std::string line;
            bool isRules = true;
            while (getline(inputFile, line)) {
                if (isRules) {
                    if (line == "") {
                        isRules = false;
                        continue;
                    }
                    int num1 = std::stoi(line.substr(0, line.find("|")));
                    int num2 = std::stoi(line.substr(line.find("|") + 1));
                    rules[num2].insert(num1);
                }
                else {
                    std::vector<int> update;
                    while (line.find(",") != std::string::npos) {
                        update.push_back(std::stoi(line.substr(0, line.find(","))));
                        line = line.substr(line.find(",") + 1);
                    }
                    update.push_back(std::stoi(line));
                    updates.push_back(update);
                    update.clear();
                }
            }
        }
        
        static bool sorter(int left, int right, std::unordered_map<int, std::unordered_set<int> >& rules) {
            if (rules[left].find(right) != rules[left].end()) {
                return true;
            }
            return false;
        }
};

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    Solution solution = Solution("2024/05/input.txt");
    std::cout << "Part one: " << solution.partOne() << std::endl;
    std::cout << "Part two: " << solution.partTwo() << std::endl;

    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count() << " ms" << std::endl;
}