#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <bits/stdc++.h>

class Solution {
    public:
        std::vector<std::string> rawData;
        std::vector<std::string> data;
    
        Solution(const char* filename) {
            getData(filename);
            processData();
        }

        int partOne() {
            int ans = 0;
            for (std::string line : data) {
                size_t pos = 0;
                while (line.find("XMAS", pos) != std::string::npos) {
                    ans++;
                    pos = line.find("XMAS", pos) + 1;
                }
            }
            return ans;
        }

        int partTwo() {
            int ans = 0;
            for (int i = 1; i < rawData.size() - 1; i++) {
                for (int j = 1; j < rawData[i].size() - 1; j++) {
                    if (rawData[i][j] == 'A') {
                        if (checkXMas(rawData[i - 1][j - 1], rawData[i - 1][j + 1], rawData[i + 1][j - 1], rawData[i + 1][j + 1])) {
                            ans++;
                        }
                    }
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
                rawData.push_back(line);
                data.push_back(line);
                std::reverse(line.begin(), line.end());
                data.push_back(line); 
            }
        }

        void processData() {
            // Gather all vertical lines
            for (int i = 0; i < rawData[0].size(); i++) {
                std::string line;
                for (int j = 0; j < rawData.size(); j++) {
                    line += rawData[j][i];
                }
                data.push_back(line);
                std::reverse(line.begin(), line.end());
                data.push_back(line);
            }

            // Gather all diagonal lines
            int max = std::max(rawData.size(), rawData[0].size());
            for (int i = 1; i < max; i++) {
                std::string temp1;
                std::string temp2;
                for (int j = 0; j < max - i; j++) {
                    temp1 += rawData[j][j + i];
                    temp2 += rawData[j + i][j];
                }
                data.push_back(temp1);
                data.push_back(temp2);
                std::reverse(temp1.begin(), temp1.end());
                std::reverse(temp2.begin(), temp2.end());
                data.push_back(temp1);
                data.push_back(temp2);
            } 
        
            for (int i = 0; i < max - 1; i++) {
                std::string temp1;
                std::string temp2;
                for (int j = 0; j < i + 1; j++) {
                    temp1 += rawData[i - j][j];
                    temp2 += rawData[max - 1 - j][max - 1 - i + j];
                }
                data.push_back(temp1);
                data.push_back(temp2);
                std::reverse(temp1.begin(), temp1.end());
                std::reverse(temp2.begin(), temp2.end());
                data.push_back(temp1);
                data.push_back(temp2);
            } 
            std::string temp1;
            std::string temp2;
            for (int i = 0; i<max; i++) {
                temp1 += rawData[i][i];
                temp2 += rawData[i][max - 1 - i];
            }
            data.push_back(temp1);
            data.push_back(temp2);
            std::reverse(temp1.begin(), temp1.end());
            std::reverse(temp2.begin(), temp2.end());
            data.push_back(temp1);
            data.push_back(temp2);
        }

        bool checkXMas(char ul, char ur, char dl, char dr) {
            if (ul == 'M' && dr == 'S' || ul == 'S' && dr == 'M') {
                if (ur == 'M' && dl == 'S' || ur == 'S' && dl == 'M') {
                    return true;
                }
            }
            return false;
        }
};

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    Solution solution = Solution("2024/04/input.txt");
    int partOne = solution.partOne();
    std::cout << "Part One: " << partOne << std::endl;
    int partTwo = solution.partTwo();
    std::cout << "Part Two: " << partTwo << std::endl;

    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count() << " ms" << std::endl;
}