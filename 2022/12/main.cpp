#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <queue>
#include <tuple>

using namespace std;

class Solution {
    public:
        Solution(const char* filename) {
            getData(filename);
        }

        int partOne() {
            return bfs(start);
        }

        int partTwo() {
            return reverseBfs();
        }

    
    private:
        vector<vector<int> > heightmap;
        vector<pair<int, int> > startPoints;
        pair<int, int> start;
        pair<int, int> end;

        void getData(const char* filename) {
            ifstream inputFile;
            inputFile.open(filename);
            string line;
            vector<int> row;
            int rowIndex = 0;
            while (getline(inputFile, line)) {
                for (int i = 0; i < line.size(); i++) {
                    if (line[i] == 'S') {
                        row.push_back(0); // Start point = 0, same height as 'a'
                        start = make_pair(rowIndex, i);
                        continue;
                    }
                    if (line[i] == 'E') {
                        row.push_back(25); // End point = 25, same height as 'z'
                        end = make_pair(rowIndex, i);
                        continue;
                    }
                    if (line[i] == 'a') {
                        startPoints.push_back(make_pair(rowIndex, i));
                    }
                    row.push_back(line[i] - 'a');
                }
                heightmap.push_back(row);
                row.clear();
                rowIndex++;
            }
        }

        int bfs(pair<int, int> customStart) {
            int rows = heightmap.size(), cols = heightmap[0].size();
            queue<tuple<int, int, int>> q;
            vector<vector<bool>> visited(rows, vector<bool>(cols, false));
            q.push(make_tuple(customStart.first, customStart.second, 0)); // (row, col, steps)
            visited[customStart.first][customStart.second] = 1;
            vector<pair<int, int> > directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

            while (!q.empty()) {
                auto [row, col, steps] = q.front();
                q.pop();
                if (make_pair(row, col) == end) {
                    return steps;
                }
                for (auto [dr, dc] : directions) {
                    int newRow = row + dr;
                    int newCol = col + dc;
                    if (newRow < 0 || newRow >= heightmap.size() || newCol < 0 || newCol >= heightmap[0].size()) {
                        continue; // Out of bounds
                    }
                    if (visited[newRow][newCol]) {
                        continue; // Already visited
                    }
                    if (heightmap[newRow][newCol] - heightmap[row][col] > 1) {
                        continue; // Height difference too large
                    }
                    visited[newRow][newCol] = true;
                    q.push(make_tuple(newRow, newCol, steps + 1));
                }
            }
            return -1; // No path found
        }

        int reverseBfs() {
            int rows = heightmap.size(), cols = heightmap[0].size();
            queue<tuple<int, int, int>> q;
            vector<vector<bool>> visited(rows, vector<bool>(cols, false));
            q.push(make_tuple(end.first, end.second, 0));
            visited[end.first][end.second] = true;
            vector<pair<int, int> > directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

            while (!q.empty()) {
                auto [row, col, steps] = q.front();
                q.pop();
                if (heightmap[row][col] == 0) {
                    return steps;
                }
                for (auto [dr, dc] : directions) {
                    int newRow = row + dr;
                    int newCol = col + dc;
                    if (newRow < 0 || newRow >= heightmap.size() || newCol < 0 || newCol >= heightmap[0].size()) {
                        continue; // Out of bounds
                    }
                    if (visited[newRow][newCol]) {
                        continue; // Already visited
                    }
                    if (heightmap[row][col] - heightmap[newRow][newCol] > 1) {
                        continue; // Height difference too large
                    }
                    visited[newRow][newCol] = true;
                    q.push(make_tuple(newRow, newCol, steps + 1));
                }
            }
            return -1; // No path found
        }
};

int main() {
    auto start = chrono::high_resolution_clock::now();
    Solution testSolution = Solution("testinput.txt");
    Solution solution = Solution("input.txt");

    cout << "Test One: " << testSolution.partOne() << endl;
    cout << "Test Two: " << testSolution.partTwo() << "\n\n";

    cout << "Part One: " << solution.partOne() << endl;
    cout << "Part Two: " << solution.partTwo() << endl;

    cout << "Time: " << chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start).count() << " ms" << endl;
}