#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <bits/stdc++.h>
#include <unordered_map>

class Solution {
    public:
        std::vector<int> list1;
        std::vector<int> list2;
    
        Solution(const char* filename) {
            getData(filename);
        }

        int partOne() {
            int ans = 0;
            std::sort(list1.begin(), list1.end());
            std::sort(list2.begin(), list2.end());
            for (int i = 0; i < list1.size(); i++) {
                ans += abs(list1[i] - list2[i]);
            }

            return ans;
        }


        int partTwo() {
            int ans = 0;
            std::unordered_map<int, int> cache;
            for (int i = 0; i < list1.size(); i++) {
                if (cache.find(list1[i]) == cache.end()) {
                    int num = list1[i];
                    int count = 0;
                    // Brute force is acceptable here due to the list being 1000 elements long
                    for (int j = 0; j < list2.size(); j++) {
                        if (list2[j] == num) {
                            count++;
                        }
                    }
                    cache[num] = count * num;
                }
                ans += cache[list1[i]];
            }
            return ans;
        }
    
    private:
        void getData(const char* filename) {
            std::ifstream inputFile;
            inputFile.open(filename);
            std::string line;
            while (getline(inputFile, line)) {
                for (int i = 0; i < line.size(); i++) {
                    if (!isalnum(line[i])) {
                        list1.push_back(std::stoi(line.substr(0, i)));
                        list2.push_back(std::stoi(line.substr(i + 3, line.size() - i - 1)));
                        break;
                    }
                }
            }
        }
};

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    Solution solution = Solution("2024/01/input.txt");
    int partOne = solution.partOne();
    std::cout << "Part One: " << partOne << std::endl;
    int partTwo = solution.partTwo();
    std::cout << "Part Two: " << partTwo << std::endl;
    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count() << " ms" << std::endl;
}