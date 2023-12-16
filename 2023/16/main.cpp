#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <set>
#include <map>
using namespace std;

// VERY slow runtime :(

class Solution {
    public:
        vector<string> data;
        set<pair<int, int> > energizedTiles;
        set<pair<pair<int, int>, char> > alreadyDone;
    
        Solution(const char* filename) {
            getData(filename);
        }

        int partOne() {
            energizeTiles(-1, 0, 'r');
            return energizedTiles.size();
        }

        int partTwo() {
            int ans = 0;
            for (int i = 0; i<data.size(); i++) {
                energizeTiles(-1, i, 'r');
                ans = max((int)energizedTiles.size(), ans);
                energizedTiles.clear();
                alreadyDone.clear();
                energizeTiles(data[i].length(), i, 'l');
                ans = max((int)energizedTiles.size(), ans);
                energizedTiles.clear();
                alreadyDone.clear();
            }
            for (int i = 0; i<data[0].length(); i++) {
                energizeTiles(i, -1, 'd');
                ans = max((int)energizedTiles.size(), ans);
                energizedTiles.clear();
                alreadyDone.clear();
                energizeTiles(i, data.size(), 'u');
                ans = max((int)energizedTiles.size(), ans);
                energizedTiles.clear();
                alreadyDone.clear();
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

        void energizeTiles(int x, int y, char direction) {
            if (alreadyDone.find({{x, y}, direction}) != alreadyDone.end()) {
                return;
            }
            else {
                alreadyDone.insert({{x, y}, direction});
            }
            if (x>=0 && y>=0 && x<data[0].length() && y<data.size()) {
                energizedTiles.insert({x, y});
            }
            if (direction == 'u') {
                if (y == 0) {
                    return;
                }
                for (int i = y - 1; i>=0; i--) {
                    energizedTiles.insert({x, i});
                    if (data[i][x] == '-') {
                        energizeTiles(x, i, 'l');
                        energizeTiles(x, i, 'r');
                        break;
                    }
                    else if (data[i][x] == '/') {
                        energizeTiles(x, i, 'r');
                        break;
                    }
                    else if (data[i][x] == '\\') {
                        energizeTiles(x, i, 'l');
                        break;
                    }
                }
            }
            else if (direction == 'r') {
                if (x == data[y].length() - 1) {
                    return;
                }
                for (int i = x + 1; i<data[y].length(); i++) {
                    energizedTiles.insert({i, y});
                    if (data[y][i] == '|') {
                        energizeTiles(i, y, 'u');
                        energizeTiles(i, y, 'd');
                        break;
                    }
                    else if (data[y][i] == '/') {
                        energizeTiles(i, y, 'u');
                        break;
                    }
                    else if (data[y][i] == '\\') {
                        energizeTiles(i, y, 'd');
                        break;
                    }
                }
            }
            else if (direction == 'd') {
                if (y == data.size() - 1) {
                    return;
                }
                for (int i = y + 1; i<data.size(); i++) {
                    energizedTiles.insert({x, i});
                    if (data[i][x] == '-') {
                        energizeTiles(x, i, 'l');
                        energizeTiles(x, i, 'r');
                        break;
                    }
                    else if (data[i][x] == '/') {
                        energizeTiles(x, i, 'l');
                        break;
                    }
                    else if (data[i][x] == '\\') {
                        energizeTiles(x, i, 'r');
                        break;
                    }
                }
            }
            else if (direction == 'l') {
                if (x == 0) {
                    return;
                }
                for (int i = x - 1; i>=0; i--) {
                    energizedTiles.insert({i, y});
                    if (data[y][i] == '|') {
                        energizeTiles(i, y, 'u');
                        energizeTiles(i, y, 'd');  
                        break;                      
                    }
                    else if (data[y][i] == '/') {
                        energizeTiles(i, y, 'd');
                        break;
                    }
                    else if (data[y][i] == '\\') {
                        energizeTiles(i, y, 'u');
                        break;
                    }
                }
            }
        }
};

int main() {
    auto start = chrono::high_resolution_clock::now();
    Solution solution = Solution("2023/16/input.txt");
    int partOne = solution.partOne();
    int partTwo = solution.partTwo();
    cout << "Part one: " << partOne << endl;
    cout << "Part two: " << partTwo << endl;

    cout << "Time: " << chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start).count() << " ms" << endl;
}