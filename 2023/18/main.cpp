#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <unordered_map>
#include <sstream>
using namespace std;

class Solution {
    public:
        vector<pair<char, int> > digDirections;
        vector<string> colorCodes;
    
        Solution(const char* filename) {
            getData(filename);
        }

        int partOne() {
            return calculateHole();
        }

        long long partTwo() {
            return calculateHole2();
        }

    
    private:
        unordered_map<char, pair<int, int> > dirs = {{'R', {1, 0}}, {'L', {-1, 0}}, {'U', {0, -1}}, {'D', {0, 1}},
                                                     {'0', {1, 0}}, {'2', {-1, 0}}, {'3', {0, -1}}, {'1', {0, 1}}};

        void getData(const char* filename) {
            ifstream inputFile;
            inputFile.open(filename);
            string line;
            while (getline(inputFile, line)) {
                digDirections.push_back({line[0], stoi(line.substr(2, line.find(' ', 2)))});
                colorCodes.push_back(line.substr(line.find('(') + 1, line.find(')')));
            }
        }

        int calculateHole() {
            int xpos = 0;
            double ans = 1;
            for (int i = 0; i<digDirections.size(); i++) {
                int meters = digDirections[i].second; 
                xpos += dirs[digDirections[i].first].first * meters;
                ans += dirs[digDirections[i].first].second * meters * xpos + (double)meters/2;
            }
            return ans;
        }

        long long calculateHole2() {
            long long xpos = 0;
            long long ans = 1;
            double rest = 0;
            for (int i = 0; i<colorCodes.size(); i++) {
                int meters;
                stringstream ss;
                ss << hex << colorCodes[i].substr(1, 5);
                ss >> meters;
                xpos += dirs[colorCodes[i][6]].first * meters;
                ans += dirs[colorCodes[i][6]].second * meters * xpos + meters/2;
                rest += meters % 2;
            }
            ans += rest/2;
            return ans;
        }
};

int main() {
    auto start = chrono::high_resolution_clock::now();
    Solution solution = Solution("2023/18/input.txt");
    int partOne = solution.partOne();
    long long partTwo  = solution.partTwo();
    cout << "Part one: " << partOne << endl;
    cout << "Part two: " << partTwo << endl;
    cout << "Time: " << chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start).count() << " ms" << endl;
}