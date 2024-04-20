#include <vector>
#include <iostream>
#include <unordered_map>
#include <string>
#include <fstream>
#include <math.h>
#include <chrono>

using namespace std;

class Solution {
    public:
        vector<string> data;
        unordered_map<string, int> maxCubes = {
            {"red", 12},
            {"green", 13},
            {"blue", 14}
        };

        Solution(const char* filename) {
            getData(filename);
        }

        int solvePartOne() {
            int sum = 0;
            for (int i = 0; i<data.size(); i++) {
                vector<string> sets = splitSets(data[i]);
                bool possible = true;
                for (string set : sets) {
                    unordered_map<string, int> colorFrequency = splitCubes(set);
                    for (auto &pair : colorFrequency) {
                        if (pair.second > maxCubes[pair.first]) {
                            possible = false;
                            break;
                        }
                    }
                    if (!possible) {
                        break;
                    }
                }
                if (possible) {
                    sum += i + 1;
                }
            }
            return sum;
        }
    
    int solvePartTwo() {
        int sum = 0;
        for (int i = 0; i<data.size(); i++) {
            unordered_map<string, int> maxCubes = {{"red", 0}, {"green", 0}, {"blue", 0}};
            vector<string> sets = splitSets(data[i]);
            for (string set : sets) {
                unordered_map<string, int> colorFrequency = splitCubes(set);
                for (auto &pair : colorFrequency) {
                    if (pair.second > maxCubes[pair.first]) {
                        maxCubes[pair.first] = pair.second;
                    }
                }
            }
            sum += maxCubes["red"] * maxCubes["blue"] * maxCubes["green"];
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

    vector<string> splitSets(string line) {
        vector<string> sets;
        line = line.substr(line.find(": ") + 2, line.length() - 1);
        string set;
        size_t splitIndex = line.find(";");
        while (splitIndex != string::npos) {
            sets.push_back(line.substr(0, splitIndex));
            line = line.substr(splitIndex + 2);
            splitIndex = line.find(";");
        }
        sets.push_back(line.substr(splitIndex + 1));
        return sets;
    }

    unordered_map<string, int> splitCubes(string set) {
        unordered_map<string, int> colorFrequency;
        size_t splitIndex = set.find(",");
        string color;
        bool done = false;
        while (splitIndex != string::npos || !done) {
            string colorSplit = set.substr(0, splitIndex);
            int amount = 0;
            string num;
            for (char i : colorSplit) {
                if (isdigit(i)) {
                    num += i; 
                }
                else {
                    break;
                }
            }
            for (int i = 0; i<num.length(); i++) {
                amount += (num[i] - '0') * pow(10, num.length() - i - 1);
            }
            color = (colorSplit.find("blue") != string::npos) ? "blue" : color;
            color = (colorSplit.find("red") != string::npos) ? "red" : color;
            color = (colorSplit.find("green") != string::npos) ? "green" : color;
            colorFrequency[color] = amount;
            set = set.substr(splitIndex + 2);
            done = (splitIndex != string::npos) ? false : true;
            splitIndex = set.find(",");
        }
        return colorFrequency;
    }

};

int main() {
    auto start = chrono::high_resolution_clock::now();
    Solution solution = Solution("2023/02/input.txt");
    int partOne = solution.solvePartOne();
    int partTwo = solution.solvePartTwo();
    cout << "Part one: " << partOne << endl;
    cout << "Part two: " << partTwo << endl;
    cout << "Time: " << chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start).count() << " ms" << endl;
}