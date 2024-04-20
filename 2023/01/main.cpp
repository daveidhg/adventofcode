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

        unordered_map<string, int> numbers = {
            {"one", 1},
            {"two", 2},
            {"three", 3},
            {"four", 4},
            {"five", 5},
            {"six", 6},
            {"seven", 7},
            {"eight", 8},
            {"nine", 9}
        };
        
        Solution(const char* filename) {
            getData(filename);
        }

        int solvePartOne() {
            int sum = 0;
            for (string line : data) {
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
            }
            return sum;
        }

        int solvePartTwo() {
            int sum = 0;
            int firstOccurence;
            int firstValue;
            int lastOccurence;
            int lastValue;
            for (string line : data) {
                firstOccurence = line.length();
                lastOccurence = 0;
                for (const auto &pair : numbers) {
                    size_t foundFirst = line.find(pair.first);
                    size_t foundLast = line.rfind(pair.first);
                    if (foundFirst != string::npos)
                    {
                        if (foundFirst < firstOccurence) {
                            firstOccurence = foundFirst;
                            firstValue = numbers[pair.first] * 10;
                        }
                        if (foundLast > lastOccurence) {
                            lastOccurence = foundLast;
                            lastValue = numbers[pair.first];
                        }

                    }
                }
                for (int i = 0; i<line.length(); i++) {
                    if (isdigit(line[i])) {
                        if (i <= firstOccurence) {
                            firstOccurence = i;
                            firstValue = (line[i] - '0') * 10;
                        }
                        if (i >= lastOccurence) {
                            lastOccurence = i;
                            lastValue = line[i] - '0';
                        }
                    }
                }        
                sum += firstValue + lastValue;
            }
            return sum;
        }

    private:
        void getData(const char* filename) {
            ifstream inputFile;
            inputFile.open(filename);
            string line;
            while (getline(inputFile, line)) {
                data.push_back(line);
            }
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