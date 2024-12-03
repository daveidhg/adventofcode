#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>


class Solution {
    public:
        std::vector<std::vector<int> > data;
    
        Solution(const char* filename) {
            getData(filename);
        }

        int partOne() {
            int ans = 0;
            for (std::vector<int> report : data) {
                if (isSafe(report)) {
                    ans++;
                }
            }
            return ans;
        }

        int partTwo() {
            int ans = 0;
            for (std::vector<int> report : data) {
                if (isSafe2(report)) {
                    ans++;
                }
            }
            return ans;
        }

    
    private:
        void getData(const char* filename) {
            std::ifstream inputFile;
            inputFile.open(filename);
            std::string line;
            while (getline(inputFile, line)) {
               std::vector<int> report;
               size_t index = 0;
               while (line.find_first_of(" ", index) != std::string::npos) {
                     size_t spaceIndex = line.find_first_of(" ", index);
                     report.push_back(std::stoi(line.substr(index, spaceIndex - index)));
                     index = spaceIndex + 1;
               }
                report.push_back(std::stoi(line.substr(index, line.size() - 1)));
                data.push_back(report);
            }
        }

        bool isSafe(std::vector<int>& report) {
            int startValue = report[0];
            bool increasing = startValue < report[1];
            for (int i = 0; i<report.size() - 1; i++) {
                if (increasing && report[i] > report[i+1]) {
                    return false;
                } else if (!increasing && report[i] < report[i+1]) {
                    return false;
                }
                else if (abs(report[i] - report[i+1]) > 3 || report[i] == report[i+1]) {
                    return false;
                }
            }
            return true;
        }
        bool isSafe2(std::vector<int>& report) {
            int startValue = report[0];
            bool increasing = startValue < report[1];
            bool remove = false;
            size_t removedIndex = 0;
            for (int i = 0; i<report.size() - 1; i++) {
                if (increasing && report[i] > report[i+1]) {
                    removedIndex = i;
                    remove = true;
                    break;
                } else if (!increasing && report[i] < report[i+1]) {
                    removedIndex = i;
                    remove = true;
                    break;
                }
                else if (abs(report[i] - report[i+1]) > 3 || report[i] == report[i+1]) {
                    removedIndex = i;
                    remove = true;
                    break;
                }
            }
            if (remove) {
                for (int i = 0; i<report.size(); i++) {
                    std::vector<int> newReport = report;
                    newReport.erase(newReport.begin() + i);
                    if (isSafe(newReport)) {
                        return true;
                    }
                }
                return false;
            }
            return true;
        }
};

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    Solution solution = Solution("2024/02/input.txt");
    int partOne = solution.partOne();
    std::cout << "Part One: " << partOne << std::endl;
    int partTwo = solution.partTwo();
    std::cout << "Part Two: " << partTwo << std::endl;

    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count() << " ms" << std::endl;
}