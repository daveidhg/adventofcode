#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <queue>
#include <map>
#include <queue>
#include <set>
using namespace std;

class Solution {
    public:
        Solution(const char* filename) {
            getData(filename);
        }

        int partOne() {
            return fun(1);
        }

        int partTwo() {
            return fun(2);
        }

    private:
        vector<string> map;
        pair<int, int> start;
        pair<int, int> end;
        set<pair<int, int> > seenPoints;
        std::map<pair<int, int>, std::map<pair<int, int>, int> > graph;

        std::map<char, vector<pair<int, int> > > directions = {
            {'<', {{-1, 0}}},
            {'>', {{1, 0}}},
            {'^', {{0, -1}}},
            {'v', {{0, 1}}},
            {'.', {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}}
        };

        void getData(const char* filename) {
            ifstream inputFile;
            inputFile.open(filename);
            string line;
            while (getline(inputFile, line)) {
                map.push_back(line);
            }

            for (int i = 0; i<map[0].length(); i++) {
                if (map[0][i] == '.') {
                    start = {i, 0};
                }
            }

            for (int i = 0; i<map[map.size() - 1].length(); i++) {
                if (map[map.size() - 1][i] == '.') {
                    end = {i, map.size() - 1};
                }
            }
        }

        set<pair<int, int> > getDesicionPoints() {
            set<pair<int, int> > pointsWithChoice = {start, end};
            for (int i = 0; i<map.size(); i++) {
                for (int j = 0; j<map[i].length(); j++) {
                    if (map[i][j] == '#') {
                        continue;
                    }
                    int paths = 0;
                    for (pair<int, int> point : vector<pair<int, int> > {{j + 1, i}, {j - 1, i}, {j, i + 1}, {j, i - 1}}) {
                        if (isPathInBounds(point.first, point.second)) {
                            paths++;
                        }
                    }
                    if (paths >= 3) {
                        pointsWithChoice.insert({j, i});
                    }
                }
            }
            return pointsWithChoice;
        }

        bool isPathInBounds(int x, int y) {
            return (0 <= x && x < map[0].length()) && (0 <= y && y < map.size()) && map[y][x] != '#';
        }

        int dfs(pair<int, int> point) {
            if (point == end) {
                return 0;
            }

            int length = INT_MIN;
            seenPoints.insert(point);
            for (auto &stretch : graph[point]) {
                if (seenPoints.find(stretch.first) == seenPoints.end()) {
                    length = max(length, dfs(stretch.first) + stretch.second);
                }   
            }
            seenPoints.erase(point);
            return length;
        }

        int fun(int part) {
            set<pair<int, int> > pointsWithChoices = getDesicionPoints();
            for (auto &pair : pointsWithChoices) {
                queue<vector<int> > q;
                q.push({0, pair.first, pair.second});
                set<std::pair<int, int> > seen;
                seen.insert({pair.first, pair.second});
                while (!q.empty()) {
                    vector<int> &current = q.front();
                    int n = current[0];
                    int x = current[1];
                    int y = current[2];

                    if (n != 0 && pointsWithChoices.find({x, y}) != pointsWithChoices.end()) {
                        graph[pair][{x, y}] = n;
                        q.pop();
                        continue;
                    }

                    char directionsKey = (part == 1) ? map[y][x] : '.';
                    for (auto &dir : directions[directionsKey]) {
                        int newX = x + dir.first;
                        int newY = y + dir.second;
                        if (isPathInBounds(newX, newY) && seen.find({newX, newY}) == seen.end()) {
                            q.push({n + 1, newX, newY});
                            seen.insert({newX, newY});
                        }
                    }
                    q.pop();
                }
            }
            return dfs(start);            
        }
};

int main() {
    auto start = chrono::high_resolution_clock::now();
    Solution solution = Solution("2023/23/input.txt");
    int partOne = solution.partOne();
    cout << "Part one: " << partOne << endl;
    int partTwo = solution.partTwo();
    cout << "Part two: " << partTwo << endl;

    cout << "Time: " << chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start).count() << " ms" << endl;
}