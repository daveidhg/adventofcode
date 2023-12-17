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
            auto [coord, len, direction, sameDirection] = entryList.top();
            entryList.pop();
            if (coord == target) {
                return len;
            }

            if (visited.find({coord.first, coord.second, sameDirection, direction.first, direction.second}) != visited.end()) {
                continue;
            }

            visited.insert({coord.first, coord.second, sameDirection, direction.first, direction.second});

            for (pair<int, int> const &dir : dmove) 
            {
                int sameDirectionCopy = sameDirection;
                if (dir == direction) {
                    if (sameDirectionCopy == max) {
                        continue;
                    }
                    sameDirectionCopy++;
                }
                else if ((dir.first + direction.first) == 0 && (dir.second + direction.second) == 0) {
                    continue;
                }
                else if (sameDirectionCopy >= min || sameDirectionCopy == 0){
                    sameDirectionCopy = 1;
                }
                else {
                    continue;
                }
                int y = coord.second + dir.second;
                int x = coord.first + dir.first;
                if (x <= 0 || x >= graph[0].size() || y < 0 || y >= graph.size()) {
                    continue;
                }
                entryList.push({{x, y}, len + graph[y][x], dir, sameDirectionCopy});
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