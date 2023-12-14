#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <set>
using namespace std;

class Solution {
    public:
        vector<string> data;
    
        Solution(const char* filename) {
            getData(filename);
        }

        int solvePartOne() {
            int ans = 0;
            tiltNorth();
            for (int i = 0; i<data.size(); i++) {
                for (char j : data[i]) {
                    if (j == 'O') {
                        ans += data.size() - i;
                    }
                }
            }
            return ans;
        }

        int solvePartTwo() {
            int ans = 0;
            tiltRest();
            set<vector<string> > earlierTilts;
            int cycleBegin;
            int cycleLen;
            bool first = true;
            bool cycleFound = false;
            for (int i = 1; i<1000000000; i++) {
                tiltNorth();
                tiltRest();
                if (earlierTilts.find(data) != earlierTilts.end() && !cycleFound) {
                    if (first) {
                        earlierTilts.clear();
                        cycleBegin = i;
                        first = false;
                    }
                    else {
                        cycleLen = i - cycleBegin;
                        i = 1000000000 - (1000000000 - cycleBegin) % cycleLen;
                        cycleFound = true;
                    }

                    
                }
                earlierTilts.insert(data);
            }
            for (int i = 0; i<data.size(); i++) {
                for (char j : data[i]) {
                    if (j == 'O') {
                        ans += data.size() - i;
                    }
                }
            }
            return ans;
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

        void tiltNorth() {
            for (int i = 1; i<data.size(); i++) {
                for (int j = 0; j<data[i].length(); j++) {
                    if (data[i][j] == 'O') {
                        for (int k = i - 1; k>=0; k--) {
                            if (data[k][j] == '.') {
                                data[k][j] = 'O';
                                data[k+1][j] = '.';
                            }
                            else {
                                break;
                            }
                        }
                    }
                }
            }
        }

        void tiltRest() {
            for (int i = 1; i<data[0].length(); i++) {
                for (int j = 0; j<data.size(); j++) {
                    char curr = data[j][i];
                    if (data[j][i] == 'O') {
                        for (int k = i - 1; k>=0; k--) {
                            if (data[j][k] == '.') {
                                data[j][k] = 'O';
                                data[j][k+1] = '.';
                            }
                            else {
                                break;
                            }
                        }
                    }
                }
            }
            for (int i = data.size() - 2; i>=0; i--) {
                for (int j = 0; j<data[i].length(); j++) {
                    if (data[i][j] == 'O') {
                        for (int k = i + 1; k<data.size(); k++) {
                            if (data[k][j] == '.') {
                                data[k][j] = 'O';
                                data[k-1][j] = '.';
                            }
                            else {
                                break;
                            }
                        }
                    }
                }
            }
            for (int i = data[0].length() - 2; i>=0; i--) {
                for (int j = 0; j<data.size(); j++) {
                    if (data[j][i] == 'O') {
                        for (int k = i + 1; k<data[0].size(); k++) {
                            if (data[j][k] == '.') {
                                data[j][k] = 'O';
                                data[j][k-1] = '.';
                            }
                            else {
                                break;
                            }
                        }
                    }
                } 
            }
        }

};

int main() {
    auto start = chrono::high_resolution_clock::now();
    Solution solution = Solution("2023/14/input.txt");
    int partOne = solution.solvePartOne();
    int partTwo = solution.solvePartTwo();
    cout << "Part one: " << partOne << endl;
    cout << "Part two: " << partTwo << endl;

    cout << "Time: " << chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start).count() << " ms" << endl;
}