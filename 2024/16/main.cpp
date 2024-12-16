#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <map>
#include <set>
#include <algorithm>
#include <queue>

class Solution {
    public:
        std::vector<std::string> maze;
        int height;
        int width;
        std::pair<int, int> start;
    
        Solution(const char* filename) {
            getData(filename);
        }

        int partOne() {
            return move();
        }

        int partTwo() {
            return bestSpots();
        }

    
    private:
        void getData(const char* filename) {
            std::ifstream inputFile;
            inputFile.open(filename);
            std::string line;
            while (getline(inputFile, line)) {
                maze.push_back(line);
            }
            height = maze.size();
            width = maze[0].size();
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    if (maze[i][j] == 'S') {
                        start = std::make_pair(j, i);
                    }
                }
            }
        }

        int move() {
            std::map<std::tuple<int, int, int, int>,  int> visited;
            std::priority_queue<std::tuple<int, int, int, int, int>,
            std::vector<std::tuple<int, int, int, int, int> >,
            std::greater<std::tuple<int, int, int, int, int> > > pq;
            pq.emplace(0, start.first, start.second, 1, 0);
            while (!pq.empty()) {
                auto& [cost, x, y, dx, dy] = pq.top();
                visited[{x, y, dx, dy}] = cost;

                if (maze[y][x] == 'E') {
                    return cost;
                }

                for (auto& [nCost, nX, nY, nDx, nDy] : std::vector<std::tuple<int, int, int, int, int> >{{cost + 1, x + dx, y + dy, dx, dy}, {cost + 1000, x, y, -dy, dx}, {cost + 1000, x, y, dy, -dx}}) {
                    if (maze[nY][nX] == '#' || (visited.find({nX, nY, nDx, nDy}) != visited.end())) {
                        continue;
                    }
                    pq.emplace(nCost, nX, nY, nDx, nDy);
                }
                pq.pop();
            }
            return 0;
        }

        int bestSpots() {
            std::map<std::tuple<int, int, int, int>,  int> visited;
            std::priority_queue<std::tuple<int, int, int, int, int>,
            std::vector<std::tuple<int, int, int, int, int> >,
            std::greater<std::tuple<int, int, int, int, int> > > pq;
            std::map<std::tuple<int, int, int, int>, std::set<std::tuple<int, int, int, int> > > backtrack;
            std::set<std::tuple<int, int, int, int> > endStates;
            int bestCost = INT_MAX;
            pq.emplace(0, start.first, start.second, 1, 0);
            while (!pq.empty()) {
                auto& [cost, x, y, dx, dy] = pq.top();
                visited[{x, y, dx, dy}] = cost;

                if (cost > visited[{x, y, dx, dy}] && visited[{x, y, dx, dy}] != 0) {
                    continue;
                }

                if (maze[y][x] == 'E') {
                    if (cost > bestCost) {
                        break;
                    }
                    bestCost = cost;
                    endStates.insert({x, y, dx, dy});
                }

                for (auto& [nCost, nX, nY, nDx, nDy] : std::vector<std::tuple<int, int, int, int, int> >{{cost + 1, x + dx, y + dy, dx, dy}, {cost + 1000, x, y, -dy, dx}, {cost + 1000, x, y, dy, -dx}}) {
                    if (maze[nY][nX] == '#' || nCost > visited[{nX, nY, nDx, nDy}] && visited[{nX, nY, nDx, nDy}] != 0) {
                        continue;
                    }
                    if (nCost < visited[{nX, nY, nDx, nDy}]) {
                        backtrack[{nX, nY, nDx, nDy}].clear();
                        visited[{nX, nY, nDx, nDy}] = nCost;
                    }
                    backtrack[{nX, nY, nDx, nDy}].insert({x, y, dx, dy});
                    pq.emplace(nCost, nX, nY, nDx, nDy);
                }
                pq.pop();
            }
            std::queue<std::tuple<int, int, int, int> > q;
            std::set<std::tuple<int, int, int, int> > seen;
            for (auto& [x, y, dx, dy] : endStates) {
                q.push({x, y, dx, dy});
                seen.insert({x, y, dx, dy});
            }
            while (!q.empty()) {
                auto& [x, y, dx, dy] = q.front();
                for (auto& last : backtrack[{x, y, dx, dy}]) {
                    if (seen.find(last) != seen.end() || std::get<0>(last) > width || std::get<1>(last) > height || std::get<0>(last) < 0 || std::get<1>(last) < 0) {
                        continue;
                    }
                    seen.insert(last);
                    q.push(last);
                }
                q.pop();
            }
            std::set<std::pair<int, int> > seenWithoutDir;
            for (auto& [x, y, dx, dy] : seen) {
                seenWithoutDir.insert({x, y});
            }
            return seenWithoutDir.size();
        }
};

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    Solution solution = Solution("2024/16/input.txt");
    std::cout << "Part One: " << solution.partOne() << std::endl;
    std::cout << "Part Two: " << solution.partTwo() << std::endl; 

    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count() << " ms" << std::endl;
}