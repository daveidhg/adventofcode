#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <chrono>
using namespace std;

class Solution {
    public:
        vector<string> data;

        Solution(const char* filename) {
            getData(filename);
        }

        int solvePartOne() {
            int sum = 0;
            for (string line : data) {
                sum += sumLine(line);
            }
            return sum;
        }

        int solvePartTwo() {
            int sum = 0;
            for (string line : data) {
                line = replaceText(line);
                sum += sumLine(line);
            }
            return sum;
        }


    private:
        unordered_map<string, string> numbers = {
            {"one", "o1e"},
            {"two", "t2o"},
            {"three", "t3e"},
            {"four", "f4r"},
            {"five", "f5e"},
            {"six", "s6x"},
            {"seven", "s7n"},
            {"eight", "e8t"},
            {"nine", "n9e"}
        };

        void getData(const char* filename) {
            ifstream inputFile;
            inputFile.open(filename);
            string line;
            while (getline(inputFile, line)) {
                data.push_back(line);
            }
        }

        string replaceText(string text) {
            for (const auto &pair : numbers) {
                size_t pos = text.find(pair.first);
                while (pos != string::npos) {
                    text.replace(pos, pair.first.length(), pair.second);
                    pos = text.find(pair.first);
                }
            }
            return text;
        }

        int sumLine(string line) {
            int sum = 0;
            for (char i : line) {
                if (isdigit(i)) {
                    sum += (i - '0') * 10;
                    break;
                }
            }
            reverse(line.begin(), line.end());
            for (char i : line) {
                if (isdigit(i)) {
                    sum += i - '0';
                    break;
                }
            }
            return sum;
        }

};

int main() {
    auto start = chrono::high_resolution_clock::now();
    Solution solution = Solution("2023/01/input.txt");
    int partOne = solution.solvePartOne();
    int partTwo = solution.solvePartTwo();
    cout << "Part 1: " << partOne << endl;
    cout << "Part 2: " << partTwo << endl;
    cout << "Time: " << chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start).count() << " ms" << endl;
};