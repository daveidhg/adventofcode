#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <map>
using namespace std;

class Solution {
    public:
        vector<pair<char, char> > strategy;
        map<pair<char, char>, int> scores1 = {
            {{'A', 'X'}, 4}, {{'A', 'Y'}, 8}, {{'A', 'Z'}, 3},
            {{'B', 'X'}, 1}, {{'B', 'Y'}, 5}, {{'B', 'Z'}, 9},
            {{'C', 'X'}, 7}, {{'C', 'Y'}, 2}, {{'C', 'Z'}, 6}
        };

        map<pair<char, char>, int> scores2 = {
            {{'A', 'X'}, 3}, {{'A', 'Y'}, 4}, {{'A', 'Z'}, 8},
            {{'B', 'X'}, 1}, {{'B', 'Y'}, 5}, {{'B', 'Z'}, 9},
            {{'C', 'X'}, 2}, {{'C', 'Y'}, 6}, {{'C', 'Z'}, 7}
        };
    
        Solution(const char* filename) {
            getData(filename);
        }

        int partOne() {
            int score = 0;
            for (auto s : strategy) {
                score += scores1[s];
            }
            return score; 
        }

        int partTwo() {
            int score = 0;
            for (auto s : strategy) {
                score += scores2[s];
            }
            return score; 
        }
    
    private:
        void getData(const char* filename) {
            ifstream inputFile;
            inputFile.open(filename);
            string line;
            while (getline(inputFile, line)) {
                strategy.push_back(make_pair(line[0], line[2]));
            }
        }
};

int main() {
    auto start = chrono::high_resolution_clock::now();
    Solution solution = Solution("2022/02/input.txt");
    int partOne = solution.partOne();
    cout << "Part One: " << partOne << endl;
    int partTwo = solution.partTwo();
    cout << "Part Two: " << partTwo << endl;

    cout << "Time: " << chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start).count() << " ms" << endl;
}