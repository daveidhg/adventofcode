#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <unordered_map>
#include <map>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
    public:
        vector<string> data;
    
        Solution(const char* filename) {
            getData(filename);
        }

        int partOne() {
            int ans = 0;
            for (string& line : data) {
                ans += solve(line) * stoi(line);
            }
            return ans;
        }

        long long partTwo() {
            long long ans = 0;
            for (string& line : data) {
                ans += solve(line, 25) * stoi(line);
            }
            return ans;
        }

    
    private:
        vector<vector<char> > keypadGrid = {
            {'9', '8', '7'},
            {'6', '5', '4'},
            {'3', '2', '1'},
            {'n', '0', 'A'}
        };

        vector<vector<char> > dirpadGrid = {
            {'n', '^','A'},
            {'<', 'v', '>'}
        };

        unordered_map<char, pair<int, int> > keypadMap = {
            {'7', {0, 0}},
            {'8', {0, 1}},
            {'9', {0, 2}},
            {'4', {1, 0}},
            {'5', {1, 1}},
            {'6', {1, 2}},
            {'1', {2, 0}},
            {'2', {2, 1}},
            {'3', {2, 2}},
            {'0', {3, 1}},
            {'A', {3, 2}}
        };
        unordered_map<char, pair<int, int> > dirpadMap = {
            {'^', {0, 1}},
            {'A', {0, 2}},
            {'<', {1, 0}},
            {'v', {1, 1}},
            {'>', {1, 2}}
        };

        map<pair<char, char>, vector<string> > paths;
        map<pair<char, char>, long long> pathLengths;
        map<tuple<char, char, int>, long long> cache;


        void getData(const char* filename) {
            ifstream inputFile;
            inputFile.open(filename);
            string line;
            while (getline(inputFile, line)) {
                data.push_back(line);
            }
            getPaths(keypadMap, keypadGrid);
            getPaths(dirpadMap, dirpadGrid);
            for (auto path : paths) {
                pathLengths[path.first] = path.second[0].size();
            }
        }

        void getPaths(unordered_map<char, pair<int, int> >& keymap, vector<vector<char> >& grid) {
            int height = grid.size();
            int width = grid[0].size();
            for (auto pos1 : keymap) {
                for (auto pos2 : keymap) {
                    if (pos1.first == pos2.first) {
                        paths[{pos1.first, pos2.first}] = {"A"};
                        continue;
                    }
                    queue<tuple<int, int, int, int, string> > q;
                    int dx = pos2.second.second - pos1.second.second;
                    int dy = pos2.second.first - pos1.second.first;
                    q.push({pos1.second.first, pos1.second.second, dy, dx, ""});
                    while (!q.empty()) {
                        auto& [y, x, ndy, ndx, path] = q.front(); 
                        if (x < 0 || x >= width || y < 0 || y >= height || grid[y][x] == 'n') {
                            q.pop();
                            continue;
                        }
                        if (y == pos2.second.first && x == pos2.second.second) {
                            paths[{pos1.first, pos2.first}].push_back(path + "A");
                            q.pop();
                            continue;
                        }
                        if (ndx < 0 ) {
                            q.push({y, x - 1, ndy, ndx + 1, path + '<'});
                        } 
                        else if (ndx > 0) {
                            q.push({y, x + 1, ndy, ndx - 1, path + '>'});
                        }
                        if (ndy < 0) {
                            q.push({y - 1, x, ndy + 1, ndx, path + '^'});
                        }
                        else if (ndy > 0) {
                            q.push({y + 1, x, ndy - 1, ndx, path + 'v'});
                        }
                        q.pop();
                    }
                }
            }
        }

        vector<string> getStringCombinations(vector<string>& strings1, vector<string>& strings2) {
            vector<string> combinations;
            for (string& s1 : strings1) {
                for (string& s2: strings2) {
                    combinations.push_back(s1 + s2);
                }
            }
            return combinations;
        }

        vector<string> getAllPossibilities(string code) {
            code = "A" + code;
            vector<string> possibilities = paths[{code[0], code[1]}];
            for (int i = 1; i < code.size() - 1; i++) {
                possibilities = getStringCombinations(possibilities, paths[{code[i], code[i + 1]}]);
            }
            return possibilities;
        }

        long long computeLength(char start, char end, int depth = 2) {
            if (depth == 1) {
                return pathLengths[{start, end}];
            }
            if (cache.find({start, end, depth}) != cache.end()) {
                return cache[{start, end, depth}];
            }
            long long minPath = LONG_LONG_MAX;
            for (auto path : paths[{start, end}]) {
                long long length = 0;
                path = "A" + path;
                for (int i = 0; i < path.size() - 1; i++) {
                    length += computeLength(path[i], path[i + 1], depth - 1);

                }
                minPath = min(minPath, length);
            }
            cache[{start, end, depth}] = minPath;
            return minPath;
        }

        long long solve(string code, int depth = 2) {
            vector<string> possibilities = getAllPossibilities(code);
            long long minPath = LONG_LONG_MAX;
            for (string possibility : possibilities) {
                long long length = 0;
                possibility = "A" + possibility;
                for (int i = 0; i < possibility.size() - 1; i++) {
                    length += computeLength(possibility[i], possibility[i + 1], depth);
                }
                minPath = min(minPath, length);
            }
            return minPath;
        }

};

int main() {
    auto start = chrono::high_resolution_clock::now();
    Solution testSolution = Solution("2024/21/testinput.txt");
    Solution solution = Solution("2024/21/input.txt");

    cout << "Test One: " << testSolution.partOne() << endl;
    cout << "Test Two: " << testSolution.partTwo() << "\n\n";

    cout << "Part One: " << solution.partOne() << endl;
    cout << "Part Two: " << solution.partTwo() << endl;

    cout << "Time: " << chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start).count() << " ms" << endl;
}