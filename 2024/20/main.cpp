#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <set>
#include <map>

using namespace std;

class Solution {
    public:
        vector<string> data;
    
        Solution(const char* filename) {
            getData(filename);
        }

        int partOne() {
            int count = 0;
            for (auto& [key, value] : getShourtcutCounts()) {
                count += key >= 100 ? value : 0;
            }
            return count;
        }

        int partTwo() {
            int count = 0;
            vector<vector<int> > stepsMap = generateStepsMap();
            int height = data.size();
            int width = data[0].size();
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    if (data[i][j] == '#') continue;
                    for (int radius = 2; radius <= 20; radius++) {
                        for (int dy = 0; dy <= radius; dy++) {
                            int dx = radius - dy;
                            for (auto& dir : set<pair<int, int> > {{i + dy, j + dx}, {i - dy, j + dx}, {i + dy, j - dx}, {i - dy, j - dx}}) {
                                if (dir.first < 0 || dir.first >= height || dir.second < 0 || dir.second >= width) continue;
                                if (data[dir.first][dir.second] == '#') continue;
                                if (stepsMap[i][j] - stepsMap[dir.first][dir.second] >= 100 + radius) {
                                    count++;
                                }
                            }
                        }
                    }
                }
            }
            return count;
        }

    
    private:
        vector<pair<int, int> > impactfulWalls;
        vector<pair<int, int> > dirs = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        pair<int, int> start;

        void getData(const char* filename) {
            ifstream inputFile;
            inputFile.open(filename);
            string line;
            while (getline(inputFile, line)) {
                data.push_back(line);
            }
            getImpactfulWallsAndStart();
        }

        void getImpactfulWallsAndStart() {
            for (int i = 1; i < data.size() - 1; i++) {
                for (int j = 1; j < data[i].size() - 1; j++) {
                    if (data[i][j] == '#' && isImpactful(j, i)) {
                        impactfulWalls.push_back(make_pair(i, j));
                    }
                    else if (data[i][j] == 'S') {
                        start = make_pair(i, j);
                    }
                }
            }
        }

        bool isImpactful(int x, int y) {
            int count = 0;
            for (auto& dir : dirs) {
                if (data[y + dir.second][x + dir.first] != '#') {
                    count++;
                }
            }
            return count >= 2;
        } 

        vector<vector<int> > generateStepsMap() {
            vector<vector<int> > dists(data.size(), vector<int>(data[0].size(), -1)); 
            dists[start.first][start.second] = 0;
            pair<int, int> pos = start; 
            int dist = 0;
            while (data[pos.first][pos.second] != 'E') {
                for (auto& dir : dirs) {
                    int y = pos.first + dir.first;
                    int x = pos.second + dir.second;
                    if(data[y][x] == '#' || dists[y][x] != -1) {
                        continue;
                    }
                    dists[y][x] = ++dist;
                    pos.first = y;
                    pos.second = x;
                    continue;
                }
            }
            return dists;
        }

        map<int, int> getShourtcutCounts() {
            vector<vector<int> > stepsMap = generateStepsMap();
            map<int, int> shortcutCounts;
            for (auto& wall : impactfulWalls) {
                shortcutCounts[getShortcutValue(wall, stepsMap)]++;
            }
            return shortcutCounts;
        }

        int getShortcutValue(pair<int, int>& wall, vector<vector<int> >& stepsMap) {
            int y = wall.first;
            int x = wall.second;
            vector<int> connectedTrails;
            for (auto& dir : dirs) {
                if (stepsMap[y + dir.first][x + dir.second] != -1) {
                    connectedTrails.emplace_back(stepsMap[y + dir.first][x + dir.second]);
                }
            }
            int shortCut = 0;
            for (int i = 0; i < connectedTrails.size(); i++) {
                for (int j = i + 1; j < connectedTrails.size(); j++) {
                    shortCut = max(shortCut, abs(connectedTrails[i] - connectedTrails[j]) - 2);
                }
            }
            return shortCut;
        } 

};

int main() {
    auto start = chrono::high_resolution_clock::now();
    Solution testSolution = Solution("2024/20/testinput.txt");
    Solution solution = Solution("2024/20/input.txt");

    cout << "Test One: " << testSolution.partOne() << endl;
    cout << "Test Two: " << testSolution.partTwo() << "\n\n";

    cout << "Part One: " << solution.partOne() << endl;
    cout << "Part Two: " << solution.partTwo() << endl;

    cout << "Time: " << chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start).count() << " ms" << endl;
}