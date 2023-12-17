#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <set>
#include <queue>
using namespace std;

// Slow solution once again :(

class Solution {
    public:
        vector<vector<int> > graph;
    
        Solution(const char* filename) {
            getData(filename);
        }

        int partOne() {
            return dijkstra(graph, {0, 0}, {graph[0].size() - 1, graph.size() - 1}, 1, 3);
        }

        int partTwo() {
            return dijkstra(graph, {0, 0}, {graph[0].size() - 1, graph.size() - 1}, 4, 10);
        }

    private:
        vector<pair<int, int> > const dmove {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

        struct entry {
            pair<int, int> coord;
            int len;
            pair<int, int> direction;
            int sameDirection;
        };

        void getData(const char* filename) {
            ifstream inputFile;
            inputFile.open(filename);
            string line;
            vector<int> row;
            while (getline(inputFile, line)) {
                for (char i : line) {
                    row.push_back(i - '0');
                }
                graph.push_back(row);
                row.clear();
            }
        }

        struct compare
        {
            bool operator()( const entry& e1, const entry &e2)
            {
                return e1.len > e2.len;
            }
        };

    int dijkstra(vector<vector<int>> &graph, pair<int, int> source, pair<int, int> target, int min, int max)
    {

        set<vector<int> > visited;
        priority_queue<entry, vector<entry>, compare> entryList;
        entryList.push({source, 0, {0, 0}, 0});
        while(!entryList.empty())
        {
            entry current = entryList.top();
            entryList.pop();
            if (current.coord == target) {
                return current.len;
            }

            if (visited.find({current.coord.first, current.coord.second, current.sameDirection, current.direction.first, current.direction.second}) != visited.end()) {
                continue;
            }

            visited.insert({current.coord.first, current.coord.second, current.sameDirection, current.direction.first, current.direction.second});
            pair<int, int> lastDirection = current.direction;

            for (pair<int, int> dir : dmove) 
            {
                int sameDirection = current.sameDirection;
                if (dir == lastDirection) {
                    if (sameDirection == max) {
                        continue;
                    }
                    sameDirection++;
                }
                else if ((dir.first + lastDirection.first) == 0 && (dir.second + lastDirection.second) == 0) {
                    continue;
                }
                else if (sameDirection >= min || sameDirection == 0){
                    sameDirection = 1;
                }
                else {
                    continue;
                }
                int y = current.coord.second + dir.second;
                int x = current.coord.first + dir.first;
                if (x <= 0 || x >= graph[0].size() || y < 0 || y >= graph.size()) {
                    continue;
                }
                entryList.push({{x, y}, current.len + graph[y][x], dir, sameDirection});
            }
        }
        return {};
    }

};

int main() {
    auto start = chrono::high_resolution_clock::now();
    Solution solution = Solution("2023/17/input.txt");
    int partOne = solution.partOne();
    cout << "Part one: " << partOne << endl;
    int partTwo = solution.partTwo();
    cout << "Part two: " << partTwo << endl;

    cout << "Time: " << chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start).count() << " ms" << endl;
}