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
            expandUniverse();
        }

        int solvePartOne() {
            int lenSum = 0;
            vector<pair<int, int> > galaxyCoordinates;
            for (int i = 0; i<data.size(); i++) {
                for (int j = 0; j<data[i].length(); j++) {
                    if (data[i][j] == '#') {
                        galaxyCoordinates.push_back({j, i});
                    }
                }
            }
            return calculateGalaxyDistances(galaxyCoordinates);
        }

        long long solvePartTwo() {
            long long lenSum = 0;
            vector<pair<int, int> > galaxyCoordinates;
            int extraCols = 0;
            int extraRows = 0;
            for (int i = 0; i<data.size(); i++) {
                for (int j = 0; j<data[i].length(); j++) {
                    char symbol = data[i][j];
                    if (symbol == '#') {
                        galaxyCoordinates.push_back({j + 999998*extraCols, i + 999998*extraRows}); // -2 due to me adding an extra empty space and not replacing it
                    }
                    else if (symbol == '|') {
                        extraRows++;
                        break;
                    }
                    else if (symbol == '-') {
                        extraCols++;
                    }
                }
                extraCols = 0;
            }

            return calculateGalaxyDistances(galaxyCoordinates);
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

        void expandUniverse() {
            set<int> columnsNotContainingGalaxy;
            for (int i = 0; i<data[0].length(); i++) {
                columnsNotContainingGalaxy.insert(i);
            }
            int rows = data.size();
            for (int row = 0; row<rows; row++) {
                bool galaxy = false;
                for (int i = 0; i<data[row].length(); i++) {
                    if (data[row][i] == '#') {
                        galaxy = true;
                        auto it = columnsNotContainingGalaxy.find(i);
                        if (it != columnsNotContainingGalaxy.end()) {
                            columnsNotContainingGalaxy.erase(it);
                        }
                    }
                }
                if (!galaxy) {
                    string newRow;
                    for (int j = 0; j<data[row].size(); j++) {
                        newRow += '|';
                    }
                    data.insert(data.begin() + row, newRow);
                    rows++;
                    row++;
                }
            }
            int colsAdded = 0;
            for (int col : columnsNotContainingGalaxy) {
                for (string &line : data) {
                    line.insert(line.begin() + col + colsAdded, '-');
                }
                colsAdded++;
            }
        }

        long long calculateGalaxyDistances(vector<pair<int, int> > galaxyCoordinates) {
            long long sum = 0;
            for (int i = 0; i<galaxyCoordinates.size() - 1; i++) {
                for (int j = i + 1; j<galaxyCoordinates.size(); j++) {
                    sum += abs(galaxyCoordinates[i].first - galaxyCoordinates[j].first) + abs(galaxyCoordinates[i].second - galaxyCoordinates[j].second);
                }
            }
            return sum;
        }
};

int main() {
    auto start = chrono::high_resolution_clock::now();
    Solution solution = Solution("2023/11/input.txt");
    int partOne = solution.solvePartOne();
    long long partTwo = solution.solvePartTwo();
    cout << "Part one: " << partOne << endl;
    cout << "Part two: " << partTwo << endl;

    cout << "Time: " << chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start).count() << " ms" << endl;
}