#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <algorithm>
#include <set>
using namespace std;

class Solution {
    public:
        vector<string> data;
        set<pair<int, int> > path;
    
        Solution(const char* filename) {
            getData(filename);
        }

        int solvePartOne() {
            auto[i, j] = getStartPos();
            path.insert({j, i});
            int x1, y1, x2, y2;
            int steps = 1;
            char dir1, dir2;
            if (data[i + 1][j] == 'J' || data[i + 1][j] == 'L' || data[i + 1][j] == '|') {
                x1 = j;
                y1 = i+1;
                dir1 = getDirection(data[i+1][j], 'd');
            }
            if (i > 0 && (data[i - 1][j] == '|' || data[i - 1][j] == '7' || data[i - 1][j] == 'F')) {
                if (dir1 == 0) {
                    x1 = j;
                    y1 = i-1;
                    dir1 = getDirection(data[i-1][j], 'd');
                }
                else {
                    x2 = j;
                    y2 = i-1;
                    dir2 = getDirection(data[i-1][j], 'd');
                }
            }
            if (data[i][j+1] == '-' || data[i][j+1] == 'J' || data[i][j+1] == '7') {
                if (dir1 == 0) {
                    x1 = j+1;
                    y1 = i;
                    dir1 = getDirection(data[i][j+1], 'r');
                }
                else {
                    x2 = j+1;
                    y2 = i;
                    dir2 = getDirection(data[i][j+1], 'r');
                }
            }
            if (data[i][j-1] == '-' || data[i][j-1] == 'L' || data[i][j-1] == 'F') {
                x2 = j-1;
                y2 = i;
                dir2 = getDirection(data[i][j-1], 'l');
            }
            path.insert(path.begin(), {x1, y1});
            path.insert({x2, y2});
            while ((abs(x1 - x2) + abs(y1 - y2)) >= 1) {
                stepForward(x1, y1, dir1);
                stepForward(x2, y2, dir2);
                path.insert(path.begin(), {x1, y1});
                path.insert({x2, y2});

                steps++;
            }
            return steps;
        }

        int solvePartTwo() {
            bool inside = false;
            int tiles = 0;
            char lastChar;
            for (int i = 0; i<data.size(); i++) {
                for (int j = 0; j<data[i].length(); j++) {
                    if (path.find({j, i}) != path.end()) {
                        char thisChar = data[i][j];
                        if (thisChar != '-') {
                            if ((lastChar == 'F' && thisChar == 'J') || (lastChar == 'L' && thisChar == '7') || (thisChar == '|')) {
                                inside = !inside;
                            }
                            lastChar = thisChar;
                        }
                    }
                    else if (inside) {
                        tiles++;
                    }
                }
                inside = false;
            }
            return tiles;
        }

    
    private:
        void getData(const char* filename) {
            ifstream inputFile;
            inputFile.open(filename);
            string line;
            vector<char> pipeRow;
            while (getline(inputFile, line)) {
                data.push_back(line);
            }
        }

        pair<int, int> getStartPos() {
            for (int i = 0; i<data.size(); i++) {
                for (int j = 0; j<data[i].length(); j++) {
                    if (data[i][j] == 'S') {
                        return {i, j};
                    }
                }
            }
        }

        char getDirection(char currentSpot, char lastDirection) {
            if (currentSpot == '|' || currentSpot == '-')
                return lastDirection;
            if (currentSpot == '7') {
                if (lastDirection == 'r') {
                    return 'd';
                }
                else {
                    return 'l';
                }
            }
            if (currentSpot == 'J') {
                if (lastDirection == 'r') {
                    return 'u';
                }
                else {
                    return 'l';
                }
            }
            if (currentSpot == 'L') {
                if (lastDirection == 'l') {
                    return 'u';
                }
                else {
                    return 'r';
                }
            }
            if (currentSpot == 'F') {
                if (lastDirection == 'l') {
                    return 'd';
                }
                else {
                    return 'r';
                }
            }
        }

        void stepForward(int &x, int &y, char &direction) {
            if (direction == 'u')
                y--;
            if (direction == 'd')
                y++;
            if (direction == 'r')
                x++;
            if (direction == 'l')
                x--;
            direction = getDirection(data[y][x], direction);
        }
};

int main() {
    auto start = chrono::high_resolution_clock::now();
    Solution solution = Solution("2023/10/input.txt");
    int partOne = solution.solvePartOne();
    int partTwo = solution.solvePartTwo();
    cout << "Part one: " << partOne << endl;
    cout << "Part two: " << partTwo << endl;

    cout << "Time: " << chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start).count() << " ms" << endl;
}