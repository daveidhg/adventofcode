#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <map>
using namespace std;

class Solution {
    public:
        vector<string> lines;
        vector<vector<int> > damaged;
        map<pair<string, vector<int> >, long long> cache;
    
        Solution(const char* filename) {
            getData(filename);
        }

        int solvePartOne() {
            int ans = 0;
            for (int i = 0; i<lines.size(); i++) {
                ans += countArrangements(lines[i], damaged[i]);
            }
            return ans;
        }

        long long solvePartTwo() {
            long long ans = 0;
            for (string &line : lines) {
                string original = line;
                for (int i = 0; i<4; i++) {
                    line += '?' + original;
                }
            }
            for (vector<int> &vec : damaged) {
                vector<int> original = vector<int>(vec.begin(), vec.end());
                for (int i = 0; i<4; i++) {
                    for (int j : original) {
                        vec.push_back(j);
                    }
                }
            }
            for (int i = 0; i<lines.size(); i++) {
                ans += countArrangements(lines[i], damaged[i]);
            }
            return ans;
        }
    
    private:
        void getData(const char* filename) {
            ifstream inputFile;
            inputFile.open(filename);
            string line;
            vector<int> damagedPerLine;
            string num;
            while (getline(inputFile, line)) {
                lines.push_back(line.substr(0, line.find(' ')));
                for (int i = line.find(' ') + 1; i<line.length(); i++) {
                    if (isdigit(line[i])) {
                        num += line[i];
                    }
                    else {
                        damagedPerLine.push_back(stoi(num));
                        num.clear();
                    }
                }
                damagedPerLine.push_back(stoi(num));
                num.clear();
                damaged.push_back(damagedPerLine);
                damagedPerLine.clear();
            }
        }

        long long countArrangements(string line, vector<int>& nums) {
            long long result = 0;
            if (line.empty()) {
                return nums.empty() ? 1 : 0;
            }
            if (nums.empty()) {
                return (line.find('#') != string::npos) ? 0 : 1;
            }
            if (cache.find({line, nums}) != cache.end()) {
                return cache[{line, nums}];
            }
            if (line[0] == '.' || line[0] == '?') {
                result += countArrangements(line.substr(1), nums);
            }
            if (line[0] == '#' || line[0] == '?') {
                if (nums[0] <= line.length() && line.substr(0, nums[0]).find('.') == string::npos && (nums[0] == line.length() || line[nums[0]] != '#')) {
                    vector<int> newNums = vector<int>(nums.begin() + 1, nums.end());
                    string nextString = (line.length() >= nums[0] + 1) ? line.substr(nums[0] + 1) : "";
                    result += countArrangements(nextString, newNums);
                }
            }
            cache[{line, nums}] = result;
            return result;
        }
    };

int main() {
    auto start = chrono::high_resolution_clock::now();
    Solution solution = Solution("2023/12/input.txt");
    int partOne = solution.solvePartOne();
    long long partTwo = solution.solvePartTwo();
    cout << "Part one: " << partOne << endl;
    cout << "Part two: " << partTwo << endl;

    cout << "Time: " << chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start).count() << " ms" << endl;
}