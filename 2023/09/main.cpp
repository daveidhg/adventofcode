#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
using namespace std;

class Solution {
    public:
        vector<vector<int> > data;
    
        Solution(const char* filename) {
            getData(filename);
        }

        int solvePartOne() {
            int ans = 0;
            vector<vector<int> > sequences;
            for (vector<int> &row : data) {
                sequences.push_back(row);
                while (!onlyZeroes(sequences.back())){
                    sequences.push_back(findSequence(sequences.back()));
                }
                for (int i = sequences.size() - 1; i>=0; i--) {
                    ans += sequences[i].back();
                }
                sequences.clear();
            }
            return ans;
        }

        int solvePartTwo() {
            int ans = 0;
            vector<vector<int> > sequences;
            for (vector<int> &row : data) {
                sequences.push_back(row);
                while (!onlyZeroes(sequences.back())) {
                    sequences.push_back(findSequence(sequences.back()));
                }
                sequences.back().insert(sequences.back().begin(), 0);
                int sum = 0;
                for (int i = sequences.size() - 2; i>=0; i--) {
                    sum = sequences[i][0] - sum;
                    sequences[i].insert(sequences[i].begin(), sum);
                }
                ans += sequences[0][0];
                sequences.clear();
            }
            return ans;
        }
    
    private:
        void getData(const char* filename) {
            ifstream inputFile;
            inputFile.open(filename);
            string line;
            vector<int> history;
            while (getline(inputFile, line)) {
                int start = 0;
                int index = line.find(' ', start);
                while (index != string::npos) {
                    int length = index - start;
                    history.push_back(stoi(line.substr(start, length)));
                    start += length + 1;
                    index = line.find(' ', start);
                }
                history.push_back(stoi(line.substr(start)));
                data.push_back(history);
                history.clear();
            }
        }

        vector<int> findSequence(vector<int> &row) {
            vector<int> sequence;
            for (int i = 1; i<row.size(); i++) {
                sequence.push_back(row[i] - row[i - 1]);
            }
            return sequence;
        }

        bool onlyZeroes(vector<int> &nums) {
            for (int num : nums) {
                if (num != 0) {
                    return false;
                }
            }
            return true;
        }
};

int main() {
    auto start = chrono::high_resolution_clock::now();
    Solution solution = Solution("2023/09/input.txt");
    int partOne = solution.solvePartOne();
    int partTwo = solution.solvePartTwo();
    cout << "Part one: " << partOne << endl;
    cout << "Part two: " << partTwo << endl;

    cout << "Time: " << chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start).count() << " ms" << endl;
}