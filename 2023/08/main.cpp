#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <unordered_map>
#include <numeric>
using namespace std;

class Solution {
    public:
        vector<char> instructions;
        unordered_map<string, vector<string> > nodes; 
        vector<string> nodePositions;
    
        Solution(const char* filename) {
            getData(filename);
        }
    
        int solvePartOne() {
            int steps = 0;
            size_t len = instructions.size();
            bool notFound = true;
            string currentNode = "AAA";
            while (notFound) {
                int direction = instructions[steps % len] == 'L' ? 0 : 1;
                currentNode = nodes[currentNode][direction];
                steps++;
                if (currentNode == "ZZZ") {
                    notFound = false;
                }
            }
            return steps;
        }

        long long solvePartTwo() {
            bool notFound = true;
            size_t len = instructions.size();
            int steps;
            vector<int> stepAmounts;
            for (string node : nodePositions) {
                string currentNode = node;
                steps = 0;
                while (notFound) {
                    int direction = instructions[steps % len] == 'L' ? 0 : 1;
                    currentNode = nodes[currentNode][direction];
                    steps++;
                    if (currentNode[2] == 'Z') {
                        notFound = false;
                        stepAmounts.push_back(steps);
                    }
                }
                notFound = true;
            }
            return vector_lcm(stepAmounts);
        }
    
    private:
        void getData(const char* filename) {
            ifstream inputFile;
            inputFile.open(filename);
            string line;
            string nodeName;
            while (getline(inputFile, line)) {
                if (instructions.empty()) {
                    for (char i : line) {
                        instructions.push_back(i);
                    }
                }
                else if (line.length() > 0){
                    nodeName = line.substr(0, 3);
                    nodes[nodeName] = {line.substr(7, 3), line.substr(12, 3)};
                    if (nodeName.find('A') != string::npos) {
                        nodePositions.push_back(nodeName);
                    }
                }
            }
        }

        long long vector_lcm(vector<int> nums) {
            long long num = nums[0];
            for (int i = 1; i<nums.size(); i++) {
                num = lcm(num, nums[i]);
            }
            return num;
        }
};

int main() {
    auto start = chrono::high_resolution_clock::now();
    Solution solution = Solution("2023/08/input.txt");
    int partOne = solution.solvePartOne();
    long long partTwo = solution.solvePartTwo();
    cout << "Part one: " << partOne << endl;
    cout << "Part two: " << partTwo << endl;
    auto time = chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start).count();
    cout << "Time: " << time << " ms" << endl;
}